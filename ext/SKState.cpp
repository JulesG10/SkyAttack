#include "SKState.h"

SKState::SKState() : m_loading(true), m_cpuloading(true), m_textures({}), m_images({})
{
}

SKState::~SKState()
{
}

Vector2 SKState::GetMouse()
{
	Vector2 pos = {
		(this->m_renderSize.x * GetMousePosition().x) / GetRenderWidth(),
		(this->m_renderSize.y * GetMousePosition().y) / GetRenderHeight()
	};
	return pos;
}