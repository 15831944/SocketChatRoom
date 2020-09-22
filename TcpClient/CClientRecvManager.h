#pragma once
#include "../TcpServer/PhdSocket.h"

//�ͻ�����Ϣ���չ�����
class CClientRecvManager
{
public:
	CClientRecvManager(PhdSocket* const pSocket):m_pSocket(pSocket){}

	bool Start();

private:
	//������ע��ظ�
	void ServerLogonReply();

	//�������ظ��ĵ�¼�����Ϣ
	void ServerLoginReply();

	//�������ظ���������Ϣ
	void ServerChatReply();

private:
	PhdSocket* m_pSocket;
};


