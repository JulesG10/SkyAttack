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


std::string SKTexureIdToString(std::string prefix, SKTextureId id)
{
	std::string name = std::to_string(id);
	while (name.length() < 4)
	{
		name = "0" + name;
	}
	return prefix + name;
}

bool SKValidTextureId(SKTextureId textureId)
{
	return (textureId != SKTextureId::NID_LAST_CLOUD && textureId != SKTextureId::NID_LAST_TILE && textureId != SKTextureId::NID_LAST_SHIP);
}
