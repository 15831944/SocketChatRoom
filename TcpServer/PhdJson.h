#pragma once
#include <string>
#include "json.h"

class PhdJson
{
	//************************************
	// Summary:   ���ڵ������ֵ
	// Update Time: 2020-9-8 10:44:33
	//************************************
	void RootKeySetValue(const std::string& strKey,const std::string& strValue);

	//************************************
	// Summary:  ���ڵ�����ֵ
	// Update Time: 2020-9-8 11:01:11
	//************************************
	void RootKeyAppendValue(const std::string& strKey,const std::string& strValue);

	//************************************
	// Summary:  ���ڵ�������ӽڵ�
	// Update Time: 2020-9-8 11:01:56
	//************************************
	void RootKeySetChildNode(const std::string& strKey,const Json::Value& childNode);

	//************************************
	// Summary:  ���ڵ�����д��json�ļ�
	// Update Time: 2020-9-8 11:06:28
	//************************************
	bool WriteFileJson(LPCTSTR szFilePath);

	//////////////////////////////////////////////////////////////////////////

	//************************************
	// Summary:  json�ļ����ݶ�ȡ�����ڵ�
	// Update Time: 2020-9-8 11:11:06
	//************************************
	bool ReadFileJson(LPCTSTR szFilePath);

	//************************************
	// Summary:  ��ȡ���ڵ����ֵ
	// Update Time: 2020-9-8 11:22:42
	//************************************
	bool GetValueOfRootKey(const std::string& strKey,std::string& strValue) const;

	//************************************
	// Summary:  ��ȡ���ڵ��������
	// Update Time: 2020-9-8 11:23:30
	//************************************
	bool GetValueArrayOfRootKey(const std::string& strKey,std::vector<std::string>& vecStr) const;

	


#pragma region ���ú���
	//************************************
	// Summary:  �õ�ֱ���ַ���
	// Update Time: 2020-9-7 18:06:50
	//************************************
	std::string GetFastString(const Json::Value& value);

	//************************************
	// Summary:  �õ������ַ���
	// Update Time: 2020-9-7 18:07:52
	//************************************
	std::string GetStyledString(const Json::Value& value);

	//************************************
	// Summary:  �õ�Json�ļ��ַ���
	// Update Time: 2020-9-7 18:17:23
	//************************************
	bool ReadFileJson(LPCTSTR szFilePath, std::string& strDocument);

	//************************************
	// Summary:  Json�ַ���д���ļ���
	// Update Time: 2020-9-8 10:27:14
	//************************************
	bool WriteFileJson(const Json::Value& value, LPCTSTR szFilePath);

#pragma endregion

private:
	Json::FastWriter m_fw;
	Json::StyledWriter m_sw;
	Json::Reader m_reader;

	Json::Value m_valueRoot;
	Json::Value m_valueTemp;
	
};


