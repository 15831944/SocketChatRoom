#pragma once

//ÿ�����ݴ��͵Ĵ�С
#define DATASIZE  1024

//Э���
enum EProtocol
{
	RT_FALSE = 0,		//����ʧ��
	RT_TRUE,			//���سɹ�

	NWPT_Logon = 10,	//ע��
	NWPT_Login,			//��¼
	NWPT_Chat,			//����
	NWPT_UploadFile,	//�ϴ��ļ�
	DownloadFile		//�����ļ�
};

