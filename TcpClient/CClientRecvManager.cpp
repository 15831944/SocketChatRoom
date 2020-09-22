#include "CClientRecvManager.h"
#include "../TcpServer/define.h"
#include <iostream>
#include <list>

extern bool g_bWaitFlag;
extern int g_nReturn;
extern std::list<std::string> g_strChat;	//�����¼
extern int g_nDlgType;		//�������� 


bool CClientRecvManager::Start()
{
	while (true)
	{
		int nProtocol = 0;
		m_pSocket->Receive(&nProtocol, sizeof(nProtocol));

		switch (nProtocol)
		{
		case NWPT_Logon:
			//�������ظ���ע������Ϣ
			ServerLogonReply();
			break;
		case NWPT_Login:
			//�������ظ��ĵ�¼�����Ϣ
			ServerLoginReply();
			break;
		case NWPT_Chat:
			//�������ظ���������Ϣ
			ServerChatReply();
			break;
		default:
			break;
		}
	}
}

void CClientRecvManager::ServerLogonReply()
{
	int nRt = 0;
	m_pSocket->Receive(&nRt, sizeof(nRt));
	g_nReturn = nRt;
	g_bWaitFlag = true;
	
}

void CClientRecvManager::ServerLoginReply()
{
	int nRt = 0;
	m_pSocket->Receive(&nRt, sizeof(nRt));
	g_nReturn = nRt;
	g_bWaitFlag = true;
}

void CClientRecvManager::ServerChatReply()
{
	//�����ַ�����С
	int nSize = 0;
	m_pSocket->Receive(&nSize, sizeof(nSize));
	//�����ַ���
	char* pStr = new char[nSize + 1];
	std::memset(pStr, 0, nSize + 1);
	m_pSocket->Receive(pStr, nSize + 1);
	std::string str = pStr;
	delete[] pStr;

	//��ӵ������¼��
	g_strChat.push_back(str);

	//�������������������¼
	if (g_nDlgType == 5)
	{
		std::system("cls");
		for (auto iter = g_strChat.begin(); iter != g_strChat.end(); iter++)
		{
			std::cout << *iter << std::endl;
		}
		std::cout << std::endl;
	}
	else if (g_nDlgType == 4 || g_nDlgType == 6 || g_nDlgType ==7)
	{
		std::cout << "�յ�һ����Ϣ" << std::endl;
	}

	g_bWaitFlag = true;
}
