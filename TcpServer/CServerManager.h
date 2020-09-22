#pragma once
#include "PhdSocket.h"
#include "CDbManager.h"

//������������
class CServerManager
{
public:
	CServerManager(PhdSocket* const pSocekt):m_pSocket(pSocekt){}

	bool Start();

private:
	//�ͻ���ע������
	void ClientLogonRequest();

	//�ͻ��˵�¼����
	void ClientLoginRequest();

	//�ͻ�����������
	void ClientChatRequest();

private:
	PhdSocket* m_pSocket;
	CDbManager m_db;
};