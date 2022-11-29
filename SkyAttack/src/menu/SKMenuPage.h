#pragma once
#include "../../stdafx.h"
#include "SKMenuTransition.h"

class SKMenuPage
{
public:
	SKMenuPage(SKState* state, SKMenuTransition* transition, SKMenuPages* page);
	virtual void UpdateFrame() = 0;
protected:
	virtual void DrawFrame();
	void ChangePage(SKMenuPages page);
	SKState* m_state;

private:
	SKMenuTransition* m_transition; 
	SKMenuPages* m_page;
	SKMenuPages m_nextPage;
};

