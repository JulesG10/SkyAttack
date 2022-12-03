#pragma once

#ifndef STDAFX_H
#define STDAFX_H

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
//#define _WIN32_WINDOWS

#include<iostream>
#include<string>
#include<fstream>
#include<functional>
#include<map>
#include<vector>
#include <chrono>
#include<unordered_map>

#include<raylib.h>
#include<raymath.h>
#include<rlgl.h>
#include<pthread.h>
#include<box2d/box2d.h>

#if defined(_WIN32)           
#define NOGDI
#define NOUSER
#endif

// https://stackoverflow.com/questions/9750344/boostasio-winsock-and-winsock-2-compatibility-issue
#include<SDKDDKVer.h>
#include<asio.hpp>
#include<Windows.h>

#if defined(_WIN32)        
#undef near
#undef far
#endif

#include <SKState.h>
#include <SKEncryption.h>
#include <SKInputManager.h>

#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
    #define SK_NEW new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
    #define SK_NEW new
#endif


inline std::vector<std::string> GetDirFiles(const std::string& directory, bool fullpath = true)
{
    WIN32_FIND_DATAA findData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    std::string full_path = directory + "\\*";
    std::vector<std::string> dir_list;

    hFind = FindFirstFileA(full_path.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        return dir_list;
    }

    while (FindNextFileA(hFind, &findData) != 0)
    {
        if (std::string(findData.cFileName) != std::string(".."))
        {
            dir_list.push_back(fullpath ? directory + "\\" + std::string(findData.cFileName) : std::string(findData.cFileName));
        }
    }

    FindClose(hFind);
    return dir_list;
}

#endif