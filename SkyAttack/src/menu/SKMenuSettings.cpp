#include "SKMenuSettings.h"

SKMenuSettings::SKMenuSettings(SKState* state, SKMenuTransition* transition, SKMenuPage* page) : m_state(state), m_transition(transition), m_page(page)
{
}

void SKMenuSettings::UpdateFrame()
{
	DrawRectangle(0, 0, this->m_state->m_renderSize.x, this->m_state->m_renderSize.y, { 150, 210, 50, 255 });
	if (this->m_transition->GetMode() == SKMenuTransitionMode::FADE_OUT)
	{
	}
	this->m_transition->PageTransition(500);
}
