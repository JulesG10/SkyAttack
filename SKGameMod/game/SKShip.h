#pragma once

#include "../pch.h"

class SKShip
{
public:
	SKShip(SKState* state);
	~SKShip();

	virtual void UpdateFrame();
protected:
	SKState* m_state;
	
	Vector2 m_position;
	Vector2 m_velocity;
	float m_angle;

	SKTextureId m_textureId;
	std::string m_textureName;
	
	float m_range;
	float m_life;

	//std::vector<Item> m_items;
};

