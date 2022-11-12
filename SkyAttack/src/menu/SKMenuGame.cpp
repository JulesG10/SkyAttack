#include "SKMenuGame.h"

SKMenuGame::SKMenuGame(SKState* state, SKMenuTransition* transition, SKMenuPages* page) : SKMenuPage(state, transition, page)
{
	this->m_serverlist = new SKScrollList(state,
		SKGui::CenterObject({ 0, 100, 400, 500 }, state->m_renderSize, { 1, 0}),
		WHITE, {0,0,0,100});
	this->m_serverlist->SetList({
		"** Join Free PvP **",
		"dez__237T3 -> www.dez.srv ",
		"125.762.143",
		"!! Official Server !!",
		});



	this->m_backHome = new SKButton(state, "Go Back", 
		SKGui::CenterObject({ 0, 500, 200, 40 }, state->m_renderSize, { 1, 1 }),
		WHITE, BLANK);
}

void SKMenuGame::DrawFrame()
{
	this->m_serverlist->UpdateFrame();

	if (this->m_backHome->UpdateFrame())
	{
		this->ChangePage(SKMenuPages::PAGE_HOME);
	}
}
