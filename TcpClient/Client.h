#pragma once
#include "../TcpServer/PhdSocket.h"

//�����ͻ���socket
bool CreateClientSocket();

//����������Ϣ�Ľ���
void ReceiveThread(void* p);


