#include "SKMenuPage.h"

SKMenuPage::SKMenuPage(SKState* state, SKMenuTransition* transition, SKMenuPages* page) : m_state(state), m_transition(transition), m_page(page), m_nextPage(SKMenuPages::PAGE_NONE)
{
}

void SKMenuPage::UpdatePageFrame()
{

}

void SKMenuPage::ChangePage(SKMenuPages page)
{
	if (this->m_nextPage == SKMenuPages::PAGE_NONE)
	{
		this->m_transition->ResetPage();
		this->m_nextPage = page;
	}
}

void SKMenuPage::UpdateFrame()
{
	DrawRectangle(0, 0, this->m_state->m_renderSize.x, this->m_state->m_renderSize.y, { 150, 210, 50, 255 });
	if (this->m_transition->GetMode() == SKMenuTransitionMode::FADE_OUT || this->m_nextPage != SKMenuPages::PAGE_NONE)
	{
		this->m_transition->ShipBackground();
		this->UpdatePageFrame();
	}
	this->m_transition->PageTransition(100);
	if (this->m_transition->IsWaiting() && this->m_nextPage != SKMenuPages::PAGE_NONE)
	{
		*(this->m_page) = this->m_nextPage;
		this->m_nextPage = SKMenuPages::PAGE_NONE;
	}
}
