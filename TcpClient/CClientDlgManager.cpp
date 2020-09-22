#include "CClientDlgManager.h"
#include <iostream>
#include "../TcpServer/define.h"
#include "CJson.h"
#include <list>
#include <fstream>

extern bool g_bWaitFlag;
extern int g_nReturn;
extern std::list<std::string> g_strChat;	//�����¼
extern int g_nDlgType;		//�������� 

bool CClientDlgManager::Start()
{
	//�򿪽���
	DlgOpen();

	return true;
}

void CClientDlgManager::DlgOpen()
{
	while (true)
	{
		g_nDlgType = 1;
		std::system("cls");

		std::cout << "��ӭ��¼��ƶ���������" << std::endl;
		std::cout << std::endl;
		std::cout << "1����¼" << std::endl;
		std::cout << "2��ע��" << std::endl;
		std::cout << "0���˳�" << std::endl;
		std::cout << std::endl;
		int nTemp = 0;
		std::cout << "�������Ӧ��ţ�";
		std::cin >> nTemp;

		if (nTemp == 1)
		{
			//��¼����
			DlgLogin();
		}
		else if (nTemp == 2)
		{
			//ע�����
			DlgLogon();
		}
		else if (nTemp == 0)
			return;
		else
		{
			std::cout << "���������Ų��ԣ�ִ���Զ�����ģʽ������" << std::endl;
			std::getchar();
			return;
		}
	}
}

void CClientDlgManager::DlgLogon()
{
	while (true)
	{
		g_nDlgType = 2;
		std::system("cls");

		std::cout << "ע�����" << std::endl;
		std::cout << std::endl;
		std::cout << "0������" << std::endl;
		std::cout << std::endl;
		std::cout << "�����˺ţ�";
		std::string strUser, strPwd;
		std::cin >> strUser;
		std::cout << "�������룺";
		std::cin >> strPwd;
		std::cout << std::endl;
		if (strUser == "0" || strPwd == "0")
			return;
		//����Э����
		int nProtocol = NWPT_Logon;
		m_pSocket->Send(&nProtocol, sizeof(nProtocol));
		//�����json�ַ���
		std::string strJson = CJson::CreateLogonJson(strUser, strPwd);
		//����json��С
		int nJsonSize = strJson.length();
		m_pSocket->Send(&nJsonSize, sizeof(nJsonSize));
		//json�ַ������͸�������
		m_pSocket->Send(strJson.c_str(), strJson.length());

		g_bWaitFlag = false;
		while (!g_bWaitFlag);

		if (g_nReturn)
		{
			std::cout << "ע��ɹ�" << std::endl;
			std::rewind(stdin);	//������
			std::getchar();		//��ͣ
			return;
		}
		else
		{
			std::cout << "ע��ʧ��" << std::endl;
			std::rewind(stdin);	//������
			std::getchar();		//��ͣ
		}
	}
}

void CClientDlgManager::DlgLogin()
{
	while (true)
	{
		g_nDlgType = 3;
		std::system("cls");

		std::cout << "��¼����" << std::endl;
		std::cout << std::endl;
		std::cout << "0������" << std::endl;
		std::cout << std::endl;
		std::cout << "�����˺ţ�";
		std::string strUser, strPwd;
		std::cin >> strUser;
		std::cout << "�������룺";
		std::cin >> strPwd;
		std::cout << std::endl;
		if (strUser == "0" || strPwd == "0")
			return;
		//����Э����
		int nProtocol = NWPT_Login;
		m_pSocket->Send(&nProtocol, sizeof(nProtocol));
		//�����json�ַ���
		std::string strJson = CJson::CreateLoginJson(strUser, strPwd);
		//����json��С
		int nJsonSize = strJson.length();
		m_pSocket->Send(&nJsonSize, sizeof(nJsonSize));
		//json�ַ������͸�������
		m_pSocket->Send(strJson.c_str(), strJson.length());

		g_bWaitFlag = false;
		while (!g_bWaitFlag);

		if (g_nReturn)
		{//��¼�ɹ�
			std::cout << "��¼�ɹ�" << std::endl;
			std::rewind(stdin);	//������
			std::getchar();		//��ͣ
			m_strUserName = strUser;
			//�ͻ��˽���
			DlgClient();
		}
		else
		{//��¼ʧ��
			std::cout << "��¼ʧ��" << std::endl;
			std::rewind(stdin);	//������
			std::getchar();		//��ͣ
		}
	}
}

void CClientDlgManager::DlgClient()
{
	while (true)
	{
		g_nDlgType = 4;
		std::system("cls");

		std::cout << "�û�����" << std::endl;
		std::cout << std::endl;
		std::cout << "1������" << std::endl;
		std::cout << "2���ϴ��ļ�" << std::endl;
		std::cout << "3�������ļ�" << std::endl;
		std::cout << "0������" << std::endl;
		std::cout << std::endl;
		std::cout << "������ţ�";
		int nNumber = 0;
		std::cin >> nNumber;

		switch (nNumber)
		{
		case 1:
			//����
			Chat();
			break;
		case 2:
			//�ϴ��ļ�
			//UploadFile();
			break;
		case 3:
			//�����ļ�
			//DownloadFile();
			break;
		case 0:
			return;
		default:
			std::cout << "���������Ų��ԣ�ִ���Զ�����ģʽ������" << std::endl;
			std::getchar();
			return;
		}
	}
}

void CClientDlgManager::Chat()
{
	//������ˢ��������Ϣ
	std::system("cls");
	for (auto iter = g_strChat.begin(); iter != g_strChat.end(); iter++)
	{
		std::cout << *iter << std::endl;
	}
	std::cout << std::endl;

	while (true)
	{
		g_nDlgType = 5;

		std::cout << "������Ҫ˵�Ļ�[#�˳�]��";
		std::string str;
		std::cin >> str;
		if (str[0] == '#')
			break;

		//����Э����
		int nProtocol = NWPT_Chat;
		m_pSocket->Send(&nProtocol, sizeof(nProtocol));
		//�����json�ַ���
		std::string strJson = CJson::CreateChatJson(m_strUserName, str);
		//����json��С
		int nJsonSize = strJson.length();
		m_pSocket->Send(&nJsonSize, sizeof(nJsonSize));
		//json�ַ������͸�������
		m_pSocket->Send(strJson.c_str(), strJson.length());

		g_bWaitFlag = false;
		while (!g_bWaitFlag);
	}
}

// void CClientDlgManager::UploadFile()
// {
// 	while (true)
// 	{
// 		g_nDlgType = 6;
// 
// 		std::cout << "������Ҫ�ϴ����ļ�������·����[#�˳�]��";
// 		std::string strFile;
// 		std::cin >> strFile;
// 		if (strFile[0] == '#')
// 			break;
// 
// 		//�жϸ��ļ��Ƿ���ڣ������ļ���С
// 		unsigned long long size = 0;
// 		if (!FileIsExist(strFile, size))
// 		{
// 			std::cout << "���ļ������ڣ���鿴" << std::endl;
// 			continue;
// 		}
// 
// 		//����Э����
// 		int nProtocol = NWPT_UploadFile;
// 		m_pSocket->Send(&nProtocol, sizeof(nProtocol));
// 		//�����json�ַ���
// 		std::string strJson = CJson::CreateUploadFileJson(strFile, size);
// 		//����json��С
// 		int nJsonSize = strJson.length();
// 		m_pSocket->Send(&nJsonSize, sizeof(nJsonSize));
// 		//json�ַ������͸�������
// 		m_pSocket->Send(strJson.c_str(), strJson.length());
// 
// 		g_bWaitFlag = false;
// 		while (!g_bWaitFlag);
// 	}
// }

bool CClientDlgManager::FileIsExist(const std::string& strFile,unsigned long long& size) const
{
	std::ifstream fileIn;
	fileIn.open(strFile.c_str(), std::ios::binary, std::ios::_Nocreate);
	if (!fileIn.is_open())
		return false;

	fileIn.seekg(0, std::ios::end);
	size = fileIn.tellg();
	fileIn.seekg(0, std::ios::beg);

	fileIn.close();
	return true;
}
