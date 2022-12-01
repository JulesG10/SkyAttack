#include "SKPlayerShip.h"

SKPlayerShip::SKPlayerShip(SKState* state) : SKShip(state)
{
}

SKPlayerShip::~SKPlayerShip()
{
}

void SKPlayerShip::UpdateFrame()
{
	float speed = 100.f;
	if (IsKeyDown(this->m_state->m_gamekeys[SKGameKeys::LEFT]))
	{
		this->m_velocity.x -= speed;
		this->m_angle -= GetFrameTime() * 30.f;
		if (this->m_angle <= 0)
		{
			this->m_angle = 0;
		}
	}
	
	if (IsKeyDown(this->m_state->m_gamekeys[SKGameKeys::RIGHT]))
	{
		this->m_velocity.x += speed;
		this->m_angle += GetFrameTime() * 30.f;
		if (this->m_angle >= 180)
		{
			this->m_angle = 180;
		}
	}

	if (IsKeyDown(this->m_state->m_gamekeys[SKGameKeys::SPEEDUP]) && this->m_velocity.y < 300.f)
	{
		this->m_velocity.y += speed;
	}

	if (IsKeyDown(this->m_state->m_gamekeys[SKGameKeys::SLOWDOWN]))
	{
		this->m_velocity.y -= speed;
		if (this->m_velocity.y <= 0)
		{
			this->m_velocity.y = 0;
		}
	}

	


	SKShip::UpdateFrame();
}
