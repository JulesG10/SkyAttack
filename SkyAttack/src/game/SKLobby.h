#pragma once

#include "../../stdafx.h"

#include "SKMap.h"
#include "SKPlayerShip.h"

#include "../gui/SKLabel.h"
#include "../gui/SKButton.h"

 
class SKLobby
{
public:
	SKLobby(SKState* state/* SKMultiGame* multi */);
	~SKLobby();

	void NewConnection();
	void UpdateFrame();

	bool InLobby();
private:
	float m_rotateAnimation;
	SKTextureId m_shipAnimation;
	Rectangle m_shipSrc;
	Rectangle m_shipDst;

	SKPlayerShip* m_player;

	bool m_active;
	SKMap* m_map;
	SKState* m_state;

	SKLabel* m_errorMsg;
	SKButton* m_quit;
};

