#pragma once
#include <string>

//���ݿ������
class CDbManager
{
public:

	//����û�
	bool AddUser(const std::string& strUser,const std::string& Pwd) const;

	//�û��˺������Ƿ���ȷ
	bool InfoIsCorrect(const std::string& strUser, const std::string& Pwd) const;

};