#pragma once

#ifndef STDAFX_H
#define STDAFX_H
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<functional>
#include<unordered_map>

#include<raylib.h>
#include<raymath.h>
#include<rlgl.h>


#if defined(_WIN32)           
#define NOGDI
#define NOUSER
#endif

#include <Windows.h>

#if defined(_WIN32)        
#undef near
#undef far
#endif


#include <pthread.h>
#include <box2d/b2_api.h>
#include <openssl/aes.h>


#endif