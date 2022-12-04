#pragma once
#include "../../stdafx.h"
#include "SKShip.h"
#include "SKMap.h"

class SKPlayerShip : public SKShip
{
public:
	SKPlayerShip(SKState*, SKMap*);
	~SKPlayerShip();

	void UpdateFrame() override;
private:
	void AdjustAngle();
	bool StopLimit();

	SKMap* m_map;
};

