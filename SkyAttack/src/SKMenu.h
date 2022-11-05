#pragma once

#include "SKState.h"

#include "menu/SKMenuTransition.h"

#include "gui/SKButton.h"
#include "gui/SKLabel.h"


class SKMenu
{
public:
	SKMenu(SKState*);
	~SKMenu();

	void UpdateFrame();
private:
	SKState* m_state;

	SKMenuTransition* m_transition;

	SKButton* m_playButton;
	SKButton* m_settingsButton;
	SKButton* m_modsButton;
	
	Vector2 m_titlePosition;
	const float m_titleScale = 5;

	std::string m_loadText;
	Vector2 m_textPosition;
	unsigned char m_textSize;
};
