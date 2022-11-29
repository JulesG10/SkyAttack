#pragma once

#include<iostream>
#include<vector>
#include<fstream>

#include <CkCrypt2.h>
#include <CkFileAccess.h>
#include <CkBinData.h>
#include <CkStringBuilder.h>

class SKEncryption
{
public:
	static SKEncryption* Instance();

	std::string DecryptString(std::string str);
	std::string EncryptString(std::string str);

	bool DecryptFileContent(std::string file);
	bool EncryptFileContent(std::string file);

	void SetKeys(const char*,const char*);
private:
	CkCrypt2 m_crypt;

	SKEncryption();
	~SKEncryption();
};

