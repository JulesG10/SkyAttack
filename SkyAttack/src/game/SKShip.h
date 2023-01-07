#pragma once

#include "../../stdafx.h"

class SKShip
{
public:
	SKShip(SKState* state);
	~SKShip();

	virtual void UpdateFrame();
	virtual Rectangle GetView();
	virtual Camera2D GetCamera();
	virtual Rectangle GetBounds();
	virtual void ApplyDamage(float);
protected:
	void UpdateCameraTarget();

	SKState* m_state;
	Camera2D m_camera = { 0 };
	Rectangle m_srcRect = { 0 };
	Rectangle m_desRect = { 0 };
	Vector2 m_origin = { 0 };

	Vector2 m_position = { 0 };
	Vector2 m_velocity = { 0 };
	float m_angle = 0.f;

	SKTextureId m_textureId = SKTextureId::SHIP_1;
	
	float m_shootRange = 0.f;
	float m_life = 0.f;

	float m_textureScale = 4.f;


	//std::vector<Item> m_items;
};

