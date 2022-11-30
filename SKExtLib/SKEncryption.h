#pragma once
#include "pch.h"

extern  class SKEXT_EXPORTS SKEncryption
{
public:
	static  SKEncryption* Instance();

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

