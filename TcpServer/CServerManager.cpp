#include "CServerManager.h"
#include <iostream>
#include "../TcpClient/CJson.h"
#include "CDbManager.h"
#include "define.h"
#include <map>

//ÿ�����ݴ��͵Ĵ�С
#define DATASIZE  1024

extern std::map<PhdSocket*, std::string> g_mapSocket;

bool CServerManager::Start()
{
	//��ͻ��˷�����Ϣ
	const char* pStr = "����������ӳɹ���";
	m_pSocket->Send(pStr, std::strlen(pStr));

	//����ѭ��������Ϣ
	while (true)
	{
		//����Э����
		int nProtocol = 0;
		int nCount = m_pSocket->Receive(&nProtocol, sizeof(nProtocol));
		if (nCount <= 0)
		{
			if (GetLastError() == 10054)
				std::cout << "�ͻ��� " << *m_pSocket << " �˳���" << std::endl;
			break;
		}

		switch (nProtocol)
		{
		case NWPT_Logon:
			//�ͻ���ע������
			ClientLogonRequest();
			break;
		case NWPT_Login:
			//�ͻ��˵�¼����
			ClientLoginRequest();
			break;
		case NWPT_Chat:
			//�ͻ�����������
			ClientChatRequest();
			break;
		default:
			break;
		}
	}

	return true;
}

void CServerManager::ClientLogonRequest()
{
	//����json�ַ�����С
	int nJsonSize = 0;
	m_pSocket->Receive(&nJsonSize, sizeof(nJsonSize));
	//����json�ַ���
	char* pJson = new char[nJsonSize+1];
	std::memset(pJson,0,nJsonSize+1);
	m_pSocket->Receive(pJson, nJsonSize + 1);
	std::string strJson = pJson;
	delete[] pJson;
	//����json�ַ���
	std::string strUser, strPwd;
	CJson::ParseLogonJson(strJson, strUser, strPwd);

	//����û�
	if (m_db.AddUser(strUser, strPwd))
	{//ע��ɹ�
		//����Э����
		int Protocol = NWPT_Logon;
		m_pSocket->Send(&Protocol, sizeof(Protocol));
		//����ע��ɹ���Ϣ
		int nTrue = RT_TRUE;
		m_pSocket->Send(&nTrue, sizeof(nTrue));
	}
	else
	{//ע��ʧ��
		//����Э����
		int Protocol = NWPT_Logon;
		m_pSocket->Send(&Protocol, sizeof(Protocol));
		//����ע��ʧ����Ϣ
		int nFalse = RT_FALSE;
		m_pSocket->Send(&nFalse, sizeof(nFalse));
	}
}

void CServerManager::ClientLoginRequest()
{
	//����json�ַ�����С
	int nJsonSize = 0;
	m_pSocket->Receive(&nJsonSize, sizeof(nJsonSize));
	//����json�ַ���
	char* pJson = new char[nJsonSize + 1];
	std::memset(pJson, 0, nJsonSize + 1);
	m_pSocket->Receive(pJson, nJsonSize + 1);
	std::string strJson = pJson;
	delete[] pJson;
	//����json�ַ���
	std::string strUser, strPwd;
	CJson::ParseLoginJson(strJson, strUser, strPwd);

	//�û��Ƿ����
	if (m_db.InfoIsCorrect(strUser, strPwd))
	{//����
		g_mapSocket[m_pSocket] = strUser;//��socket��ֵ�û���
		//����Э����
		int Protocol = NWPT_Login;
		m_pSocket->Send(&Protocol, sizeof(Protocol));
		//���͵�¼�ɹ���Ϣ
		int nTrue = RT_TRUE;
		m_pSocket->Send(&nTrue, sizeof(nTrue));
	}
	else
	{//������
		//����Э����
		int Protocol = NWPT_Login;
		m_pSocket->Send(&Protocol, sizeof(Protocol));
		//���͵�¼ʧ����Ϣ
		int nFalse = RT_FALSE;
		m_pSocket->Send(&nFalse, sizeof(nFalse));
	}
}

void CServerManager::ClientChatRequest()
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

	//���͸��������߿ͻ���
	for (auto iter = g_mapSocket.begin(); iter != g_mapSocket.end(); iter++)
	{
		if (iter->second != "")
		{
			//����Э����
			int Protocol = NWPT_Chat;
			iter->first->Send(&Protocol, sizeof(Protocol));
			//�����ַ�����С
			int nStrSize = str.length();
			iter->first->Send(&nStrSize, sizeof(nStrSize));
			//�����ַ���
			iter->first->Send(str.c_str(), str.length());
		}
	}
}
