#pragma once

#include "SKMenuPage.h"

#include "../gui/SKInput.h"
#include "../gui/SKLabel.h"
#include "../gui/SKButton.h"


class SKMenuSettings : public SKMenuPage
{
public:
	SKMenuSettings(SKState* state, SKMenuTransition*, SKMenuPages* page);
private:
	void DrawFrame() override;

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
};

