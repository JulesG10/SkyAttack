#pragma once
#include "../stdafx.h"
#include "SKMenu.h"


class SKGameCore
{
public:
	SKGameCore();
	~SKGameCore();

	int Start(int argc,char** argv);
private:
	bool Init(int argc, char** argv);
	void UploadTextures();
	void UnloadResources();
	
	RenderTexture2D m_renderTexture;
	SKState* m_state;
	SKMenu* m_menu;
	std::string m_gameKeyPath;

	friend void* LoadResources(void*);
};


void* LoadResources(void*);
