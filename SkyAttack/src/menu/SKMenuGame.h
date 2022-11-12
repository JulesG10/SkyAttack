#pragma once
#include "SKMenuPage.h"

#include "../gui/SKButton.h"
#include "../gui/SKScrollList.h"

class SKMenuGame : public SKMenuPage {
public:
	SKMenuGame(SKState* state, SKMenuTransition* transition, SKMenuPages* page);
private:
	void DrawFrame() override;

	SKScrollList* m_serverlist;
	SKButton* m_createSrv;
	SKButton* m_joinSrv;
	SKButton* m_backHome;
};