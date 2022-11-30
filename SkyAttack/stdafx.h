#pragma once

#ifndef STDAFX_H
#define STDAFX_H

#define _CRT_SECURE_NO_WARNINGS
//#define _WIN32_WINDOWS

#include<iostream>
#include<string>
#include<fstream>
#include<functional>

#include<map>
#include<vector>
#include<unordered_map>

// third-party library
#include<raylib.h>
#include<raymath.h>
#include<rlgl.h>
#include<pthread.h>
#include<box2d/box2d.h>

// collision with raylib.h and windows.h
#if defined(_WIN32)           
#define NOGDI
#define NOUSER
#endif

// asio before windows.h -> https://stackoverflow.com/questions/9750344/boostasio-winsock-and-winsock-2-compatibility-issue
#include<SDKDDKVer.h>
#include<asio.hpp>
#include<Windows.h>

// collision with raylib.h and windows.h
#if defined(_WIN32)        
#undef near
#undef far
#endif

// SK extensions
//#include "../ext/SKState.h"
//#include "../ext/SKEncryption.h"
//#include "../ext/SKInputManager.h"

#include <SKState.h>
#include <SKEncryption.h>
#include <SKInputManager.h>


#endif