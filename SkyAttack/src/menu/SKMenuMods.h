#pragma once
#include "SKMenuPage.h"

class SKMenuMods : public SKMenuPage
{
public:
	SKMenuMods(SKState* state, SKMenuTransition* transition, SKMenuPages* page);
private:
	void DrawFrame() override;

};

