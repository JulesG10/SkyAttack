#pragma once

#include "SKState.h"
#include "SKMenuTransition.h"

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
	SKLabel* m_skText;

	std::string m_loadText;
	Vector2 m_textPosition;
	unsigned char m_textSize;
};
