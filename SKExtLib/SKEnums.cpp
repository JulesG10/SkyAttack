#include "pch.h"
#include "SKEnums.h"

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
