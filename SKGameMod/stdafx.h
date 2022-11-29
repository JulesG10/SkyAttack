#pragma once

#ifndef STDAFX_H
#define STDAFX_H
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string>
#include<fstream>
#include<functional>

#include<map>
#include<vector>
#include<unordered_map>

#include<raylib.h>
#include<raymath.h>
#include<rlgl.h>

#include <pthread.h>
#include <box2d/box2d.h>

#if defined(_WIN32)           
#define NOGDI
#define NOUSER
#endif

#include <Windows.h>

#if defined(_WIN32)        
#undef near
#undef far
#endif

#include "../ext/SKState.h"
#include "../ext/SKInputManager.h"


#endif