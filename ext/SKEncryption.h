#pragma once

#include<iostream>
#include<fstream>

extern "C"
{
#define ECB 1
#define AES128 1

#include "aes.h"
};

class SKEncryption
{
public:
	static SKEncryption* Instance();

	std::string DecryptString(std::string str);
	std::string EncryptString(std::string str);

	std::string DecryptFileContent(std::string file);
	bool EncryptFileContent(std::string file, std::string content);

private:
	AES_ctx m_context;
	const uint8_t m_key[17] = "SKYATTACK_GAME_0";

	SKEncryption();
	~SKEncryption();
};

