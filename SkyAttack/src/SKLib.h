#pragma once
#include "../stdafx.h"

typedef std::string(__stdcall* SKLGetName)();
typedef std::string(__stdcall* SKLGetDesc)();
typedef int(__stdcall* SKLGetVersion)();
typedef void(__stdcall* SKLUpdateFrame)();

class SKLib
{
public:
	SKLib(std::string dll);
	~SKLib();

	template<typename T>
	T GetObject(std::string name);
private:
	HINSTANCE m_dll;
};


template<typename T>
inline T SKLib::GetObject(std::string name)
{
	if (!this->m_dll)
	{
		return NULL;
	}

	T obj = (T)GetProcAddress(this->m_dll, name.c_str());
	if (!obj)
	{
		return NULL;
	}

	return obj;
}