#pragma once
#include <string>

//���ɺͽ���json���ݵķ�װ��
class CJson 
{
public:

	//ע��
	static std::string CreateLogonJson(const std::string& strUser,const std::string& strPwd);
	static void ParseLogonJson(const std::string& json,std::string& strUser,std::string& strPwd);

	//��¼
	static std::string CreateLoginJson(const std::string& strUser, const std::string& strPwd);
	static void ParseLoginJson(const std::string& json, std::string& strUser, std::string& strPwd);

	//����
	static std::string CreateChatJson(const std::string& strUserName,const std::string& str);

};