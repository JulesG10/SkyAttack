#include "SKMenuGame.h"

SKMenuGame::SKMenuGame(SKState* state, SKMenuTransition* transition, SKMenuPages* page) : SKMenuPage(state, transition, page)
{
	this->m_serverlist = SK_NEW SKScrollList(state,
		SKGui::CenterObject({ 0, 200, 400, 500 }, state->m_renderSize, { 1, 0 }),
		WHITE, { 0,0,0,100 });
	this->m_serverlist->SetList({
		"** Join Free PvP **",
		"dez__237T3 -> www.dez.srv ",
		"125.762.143",
		"!! Official Server !!",
		});

	this->m_lobby = SK_NEW SKLobby(this->m_state);

	this->m_backHome = SK_NEW SKButton(state, "Go Back",
		SKGui::CenterObject({ 0, 500, 200, 40 }, state->m_renderSize, { 1, 1 }),
		WHITE, BLANK);


	this->m_joinSrv = SK_NEW SKButton(state, "Join",
		SKGui::CenterObject({ -300, 80, 100, 40 }, state->m_renderSize, { 1, 0 }),
		WHITE, BLANK);
	this->m_joinSrv->SetEnable(false);

	this->m_createSrv = SK_NEW SKButton(state, "Create New",
		SKGui::CenterObject({ 200, 80, 200, 40 }, state->m_renderSize, { 1, 0 }),
		WHITE, BLANK);
}

SKMenuGame::~SKMenuGame()
{

	delete this->m_lobby;

	delete this->m_serverlist;
	delete this->m_createSrv;
	delete this->m_joinSrv;
	delete this->m_backHome;
}


void SKMenuGame::UpdateFrame()
{
	/*
	if (this->multiGame->InGame())
	{
		this->multiGame->UpdateFrame();
		return;
	}
	*/
	SKMenuPage::UpdateFrame();
	return;
}

void SKMenuGame::UpdatePageFrame()
{
	if (this->m_lobby->InLobby())
	{
		this->m_lobby->UpdateFrame();
		return;
	}

	
	

	if(this->m_createSrv->UpdateFrame())
	{
		// TODO: menu with creation options:

		// TODO (Release):
		// check if upnp is enable
		// if true
		// open port -> create server thread/process
		// create the loby
		// else
		// open a browser page using cmd for a tuto
		// or enable it automaticly ?
	
		this->m_lobby->NewConnection(/* mode, ip */);
	}
	

	if (this->m_joinSrv->UpdateFrame())
	{
		// TODO: server -> loby -> game , etc...
		this->m_lobby->NewConnection(/* mode, ip */);
	}

	this->m_serverlist->UpdateFrame();
	if (this->m_serverlist->GetSelected().first != -1)
	{
		this->m_joinSrv->SetEnable(true);
	}
	else {
		this->m_joinSrv->SetEnable(false);
	}


	if (this->m_backHome->UpdateFrame())
	{
		this->ChangePage(SKMenuPages::PAGE_HOME);
	}
}
