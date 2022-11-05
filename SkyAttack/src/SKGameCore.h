#pragma once
#include "SKState.h"
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
	void UnLoadResources();
	
	RenderTexture2D m_renderTexture;
	SKState* m_state;
	SKMenu* m_menu;

	friend void* LoadResources(void*);
};


void* LoadResources(void*);