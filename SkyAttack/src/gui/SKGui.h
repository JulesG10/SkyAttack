#pragma once
#include "../SKState.h"

class SKGui
{
public:
	SKGui(SKState* state);

	static Rectangle CenterObject(Rectangle rect, Vector2 renderSize, Vector2 center);

	virtual bool UpdateFrame();
protected:
	SKState* m_state;
};

