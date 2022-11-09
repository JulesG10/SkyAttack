#pragma once

#include "../../stdafx.h"
#include "../SKState.h"
#include "../gui/SKInput.h"
#include "../gui/SKLabel.h"
#include "../gui/SKButton.h"

#include "SKMenuTransition.h"



class SKMenuSettings
{
private:
	SKMenuSettings(SKState* state, SKMenuTransition*, SKMenuPage* page);

	friend class SKMenu;

	void UpdateFrame();

	SKInput* m_left;
	SKInput* m_right;
	
	SKInput* m_slowdown;
	SKInput* m_speedup;
	SKInput* m_suicide;
	SKInput* m_missile;
	SKInput* m_ultime;

	SKLabel* m_title;
	SKLabel* m_shootInfo;
	SKButton* m_backMenu;


	SKMenuPage* m_page;
	SKState* m_state;
	SKMenuTransition* m_transition;
	
	bool m_changePage;
};

