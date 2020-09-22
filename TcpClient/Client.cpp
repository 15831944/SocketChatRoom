#include "Client.h"
#include <iostream>
#include "../TcpServer/define.h"
#include "CClientDlgManager.h"
#include "CClientRecvManager.h"
#include <list>

//���������̵߳�ȫ�ֱ���
bool g_bWaitFlag;
int g_nReturn;

std::list<std::string> g_strChat;	//�����¼
int g_nDlgType;		//�������� 

bool CreateClientSocket()
{
	//����socket
	PhdSocket* pClientSocket = new PhdSocket;
	if (!pClientSocket->Create())
	{
		std::perror("socket create");
		std::exit(0);
	}

	if (!pClientSocket->Connect("192.168.1.100", 8080))
	{
		std::perror("socket connect");
		std::exit(0);
	}

	char strData[DATASIZE] = { 0 };
	//���շ�������������Ϣ
	int n = pClientSocket->Receive(strData, DATASIZE);
	std::cout << strData << std::endl;

 	//���������߳�
 	_beginthread(ReceiveThread, 0, pClientSocket);

	//�ͻ��˽��������
	CClientDlgManager dlg(pClientSocket);
	dlg.Start();

	delete pClientSocket;
	return true;
}

void ReceiveThread(void* p)
{
	PhdSocket* pClientSocket = (PhdSocket*)p;

	//�ͻ��˽�����Ϣ������
	CClientRecvManager recv(pClientSocket);
	recv.Start();
	
}


