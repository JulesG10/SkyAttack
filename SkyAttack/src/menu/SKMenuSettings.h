#pragma once

#include "../../stdafx.h"
#include "../SKState.h"
#include "SKMenuTransition.h"


class SKMenuSettings
{
private:
	SKMenuSettings(SKState* state, SKMenuTransition*, SKMenuPage* page);

	friend class SKMenu;

	void UpdateFrame();



	SKMenuPage* m_page;
	SKState* m_state;
	SKMenuTransition* m_transition;
};

