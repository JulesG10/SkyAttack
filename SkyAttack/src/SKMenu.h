#pragma once

#include "SKState.h"

#include "menu/SKMenuTransition.h"

#include "menu/SKMenuSettings.h"
//#include "menu/SKMenuGame.h"
//#include "menu/SKMenuMods.h"

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
	void DrawHomePage();

	SKState* m_state;
	SKMenuPage m_page;

	SKMenuTransition* m_transition;
	
	SKMenuSettings* m_settings;
	//SKMenuMods* m_mods;
	//SKMenuGame* m_game;


	SKInput* m_pseudo;
	SKButton* m_playButton;
	SKButton* m_settingsButton;
	SKButton* m_modsButton;
	
	Vector2 m_titlePosition;
	const float m_titleScale = 5;

	std::string m_loadText;
	Vector2 m_textPosition;
	unsigned char m_textSize;
};
