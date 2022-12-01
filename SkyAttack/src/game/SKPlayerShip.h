#pragma once
#include "../../stdafx.h"
#include "SKShip.h"

class SKPlayerShip : public SKShip
{
public:
	SKPlayerShip(SKState*);
	~SKPlayerShip();

	void UpdateFrame() override;
private:
};

