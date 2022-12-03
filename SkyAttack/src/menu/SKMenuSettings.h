#pragma once

#include "SKMenuPage.h"

#include "../gui/SKInput.h"
#include "../gui/SKLabel.h"
#include "../gui/SKButton.h"


#define PRESET_TEXT(name,upName)\
if(this->m_state->m_gamekeys[SKGameKeys::##upName] != 0)\
{\
this->m_ ## name->SetText(std::string({ SKInputManager::Instance()->ConvertQwerty(this->m_state->m_gamekeys[SKGameKeys::##upName]) }));\
}\


class SKMenuSettings : public SKMenuPage
{
public:
	SKMenuSettings(SKState* state, SKMenuTransition*, SKMenuPages* page);
	~SKMenuSettings();

	void UpdateFrame() override;
private:
	void UpdatePageFrame() override;
	bool m_setDefaultKey = false;

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

