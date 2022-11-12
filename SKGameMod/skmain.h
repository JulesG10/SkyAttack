#pragma once
#include "../SkyAttack/stdafx.h"

#ifdef SKLIB_EXPORTS
#define SKLIB_EXPORTS __declspec(dllexport)
#else
#define SKLIB_EXPORTS __declspec(dllimport)
#endif

extern "C" {
	SKLIB_EXPORTS std::string SKLGetName();
	SKLIB_EXPORTS std::string SKLGetDesc();
	SKLIB_EXPORTS int SKLGetVersion();
	SKLIB_EXPORTS void SKLUpdateFrame();
	SKLIB_EXPORTS bool  SKLInit(SKState*);
}