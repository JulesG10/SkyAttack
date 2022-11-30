#pragma once

#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<unordered_map>

#include <raylib.h>
#include <CkCrypt2.h>
#include <CkFileAccess.h>
#include <CkBinData.h>
#include <CkStringBuilder.h>

#ifdef SKEXT_EXPORTS
#define SKEXT_EXPORTS __declspec(dllexport)
#else
#define SKEXT_EXPORTS __declspec(dllexport)
#endif