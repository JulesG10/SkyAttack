#pragma once
#include "SKMenuPage.h"

#include "../gui/SKButton.h"
#include "../gui/SKScrollList.h"

#include "../game/SKLobby.h"

class SKMenuGame : public SKMenuPage {
public:
	SKMenuGame(SKState* state, SKMenuTransition* transition, SKMenuPages* page);

	void UpdateFrame() override;
private:
	void UpdatePageFrame() override;

	SKLobby* m_lobby;

	SKScrollList* m_serverlist;
	SKButton* m_createSrv;
	SKButton* m_joinSrv;
	SKButton* m_backHome;
};