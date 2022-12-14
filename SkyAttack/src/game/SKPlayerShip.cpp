#include "SKPlayerShip.h"

SKPlayerShip::SKPlayerShip(SKState* state, SKMap* map) : SKShip(state)
{
	this->m_map = map;
}

SKPlayerShip::~SKPlayerShip()
{
}

void SKPlayerShip::UpdateFrame()
{

	this->m_velocity.x *= 0.9;
	this->m_velocity.y *= 0.9;

	float speed = 100.f;
	bool downLR = false;

	if (IsKeyDown(this->m_state->m_gamekeys[SKGameKeys::LEFT]))
	{
		this->m_velocity.x -= speed;

		this->m_angle -= GetFrameTime() * 80.f;
		this->m_angle = std::max(this->m_angle, -60.f);
		downLR = true;
	}
	else if (IsKeyDown(this->m_state->m_gamekeys[SKGameKeys::RIGHT]))
	{
		this->m_velocity.x += speed;

		this->m_angle += GetFrameTime() * 80.f;
		this->m_angle = std::min(this->m_angle, 60.f);
		downLR = true;
	}

	if (IsKeyDown(this->m_state->m_gamekeys[SKGameKeys::SPEEDUP]))
	{
		this->m_velocity.y -= speed;
		this->m_velocity.y = std::min(this->m_velocity.y, 300.f);
 
		if (!downLR)
		{
			this->AdjustAngle();
		}
	}
	else if (IsKeyDown(this->m_state->m_gamekeys[SKGameKeys::SLOWDOWN]))
	{
		this->m_velocity.y += speed;
		this->m_velocity.y = std::max(this->m_velocity.y, -150.f);

		if (!downLR)
		{
			this->AdjustAngle();
		}
	}
	
	if (IsKeyPressed(SK_AZERTY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{

		SKBulletOptions options = { 0 };
		options.angle = this->m_angle;
		options.damage = 10;
		options.scale = 3;
		options.size = { 16, 16 };
		options.origin = { this->m_origin.x - (options.size.x * options.scale) + options.size.x/2.f, this->m_origin.y };
		options.position = Vector2Add(this->m_position, Vector2Divide(this->m_state->m_renderSize, { 2, 2 }));
		options.maxDistance = 3000;
		options.texture = SKTextureId::BULLET;
		options.velocity = SKBullet::CalculateVelocity(1600.f, this->m_angle - 90);
		this->m_map->m_bullets.push_back(new SKBullet(this->m_state, options));
	}

	this->m_position.x += this->m_velocity.x * GetFrameTime();
	if (this->StopLimit() != 0)
	{
		DrawText("Zone", 0, 40, 20, RED);
		// TODO damage if in zone
	}

	this->m_position.y += this->m_velocity.y * GetFrameTime();


	this->UpdateCameraTarget();


	SKShip::UpdateFrame();
}

Rectangle SKPlayerShip::GetBounds()
{
	return this->m_desRect;
}

void SKPlayerShip::AdjustAngle()
{
	if (this->m_angle != 0)
	{
		if ((this->m_angle > 0 && this->m_angle - 2.f < 0) || (this->m_angle < 0 && this->m_angle + 2.f > 0))
		{
			this->m_angle = 0;
		}
		else {

			if (this->m_angle < 0)
			{
				this->m_angle += GetFrameTime() * 80.f;
			}
			else {
				this->m_angle -= GetFrameTime() * 80.f;

			}
		}
	}
}

int SKPlayerShip::StopLimit()
{
	Vector2 format = {
		(int)((this->m_position.x + this->m_desRect.x) / this->m_map->m_scaleTileW)* this->m_map->m_scaleTileW,
		(int)((this->m_position.y + this->m_desRect.y) / this->m_map->m_scaleTileH)* this->m_map->m_scaleTileH,
	};

	int midTilesCount = (int)(this->m_desRect.x / this->m_map->m_scaleTileW) + 2;
	
	for (int i = -midTilesCount; i < midTilesCount; i++)
	{
		Vec2 vec = { 0 };
		vec.position.x = format.x - i * this->m_map->m_scaleTileW;
		vec.position.y = format.y;

		SKTextureId id = this->m_map->m_tiles[vec.value];
		if (id == SKTextureId::ICON_BORDERLIMIT)
		{
			return i;
		}
	}


	return 0;
}
