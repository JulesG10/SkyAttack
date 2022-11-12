#include "SKLib.h"


SKLib::SKLib(std::string path)
{
	this->m_dll = LoadLibraryA(path.c_str());
}

SKLib::~SKLib()
{
	FreeLibrary(this->m_dll);
}