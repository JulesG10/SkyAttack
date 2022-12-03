#pragma once
#include "../stdafx.h"

#include "menu/SKMenuTransition.h"

#include "menu/SKMenuSettings.h"
#include "menu/SKMenuGame.h"
#include "menu/SKMenuMods.h"
#include "menu/SKMenuMap.h"

#include "gui/SKButton.h"
#include "gui/SKLabel.h"
#include "gui/SKInput.h"

class SKMenu
{
public:
	SKMenu(SKState*);
	~SKMenu();

	void UpdateFrame();
private:
	void UpdatePageFrame();

	SKState* m_state;
	SKMenuPages m_page;
	SKMenuPages m_nextPage;

	SKMenuTransition* m_transition;
	
	SKMenuSettings* m_settings;
	SKMenuGame* m_game;
	SKMenuMods* m_mods;
	SKMenuMap* m_maps;


	SKInput* m_pseudo;
	SKButton* m_playButton;
	SKButton* m_settingsButton;
	SKButton* m_modsButton;
	SKButton* m_mapButton;
	
	Vector2 m_titlePosition;
	const float m_titleScale = 5;

	std::string m_loadText;
	Vector2 m_textPosition;
	unsigned char m_textSize;
};
