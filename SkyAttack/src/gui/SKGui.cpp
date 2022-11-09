#include "SKGui.h"

SKGui::SKGui(SKState* state)
{
	this->m_state = state;
}

Rectangle SKGui::CenterObject(Rectangle rect, Vector2 renderSize, Vector2 center)
{
	return  {
		((renderSize.x - rect.width) / 2) * center.x + (rect.x / 2.f),
		((renderSize.y - rect.height) / 2) * center.y + (rect.y / 2.f),
		rect.width,
		rect.height
	};
}

bool SKGui::UpdateFrame()
{
	return false;
}
