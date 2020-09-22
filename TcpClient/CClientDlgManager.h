#pragma once
#include "../TcpServer/PhdSocket.h"

//�ͻ��˽��������
class CClientDlgManager
{
public:
	CClientDlgManager(PhdSocket* const pSocket):m_pSocket(pSocket){}

	bool Start();

private:
	//�򿪽���(1)
	void DlgOpen();

	//ע�����(2)
	void DlgLogon();

	//��¼����(3)
	void DlgLogin();

	//�ͻ��˽���(4)
	void DlgClient();

	//����(5)
	void Chat();
	//�ϴ��ļ�(6)
	void UploadFile();
	//�����ļ�(7)
	void DownloadFile();

private:
	//�жϸ��ļ��Ƿ���ڣ������ļ���С
	bool FileIsExist(const std::string& strFile, unsigned long long& size) const;

private:
	PhdSocket* m_pSocket;
	std::string m_strUserName;
};