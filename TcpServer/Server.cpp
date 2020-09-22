#include "Server.h"
#include <iostream>
#include "../TcpClient/CJson.h"
#include <list>
#include <algorithm>
#include "CServerManager.h"
#include <map>


//ȫ��socket������key��socketָ�룬value���û�����
std::map<PhdSocket*, std::string> g_mapSocket;


bool CreateServerSocket()
{
	//����socket
	PhdSocket bossSocket;
	if (!bossSocket.Create(8080))
	{
		std::perror("socket create");
		std::exit(0);
	}
	//����
	if (!bossSocket.Listen())
	{
		std::perror("socket listen");
		std::exit(0);
	}

	std::cout << "�������ѿ���......" << std::endl;

	while (true)
	{
		//�ȴ��ͻ�������
		PhdSocket* pServerSocket = new PhdSocket;
		std::string strIP;
		UINT nPort = 0;
		//accept �������� ���û�пͻ������ӣ�һֱ�ȴ��ͻ�������
		if (!bossSocket.Accept(pServerSocket, strIP, &nPort))
		{
			std::perror("socket accept");
			continue;
		}
		std::cout << "IP��ַ��" << strIP << " �˿ںţ�" << nPort << " �Ŀͻ���¼�ˡ�" << std::endl;

		//�����߳�
		_beginthread(ServerThread, 0, pServerSocket);
	}

	return true;
}

void ServerThread(void* p)
{
	PhdSocket* pServerSocket = (PhdSocket*)p;
	//���socket��������
	g_mapSocket[pServerSocket] = "";

	//���������������߶���
	CServerManager manager(pServerSocket);
	manager.Start();
	
	//��������ɾ����socket
	auto iter = g_mapSocket.find(pServerSocket);
	if (iter != g_mapSocket.end())
		g_mapSocket.erase(iter);

	//�ͷŽӴ�socket
	delete pServerSocket;
}


