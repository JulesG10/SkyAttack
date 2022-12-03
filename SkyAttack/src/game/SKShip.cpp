#include "SKShip.h"

SKShip::SKShip(SKState* state) : m_state(state)
{
	this->m_camera.zoom = 1.f;
}

SKShip::~SKShip()
{
}

void SKShip::UpdateFrame()
{
	if (!this->m_srcRect.width)
	{
		this->m_srcRect = {
			0,0,
			(float)this->m_state->m_textures[this->m_textureId].width, (float)this->m_state->m_textures[this->m_textureId].height
		};
	}

	if (!this->m_desRect.width)
	{
		this->m_desRect = {
			(this->m_state->m_renderSize.x - this->m_srcRect.width * this->m_textureScale) / 2.f,
			(this->m_state->m_renderSize.y - this->m_srcRect.height * this->m_textureScale) / 2.f,

			(float)this->m_state->m_textures[this->m_textureId].width * this->m_textureScale,
			(float)this->m_state->m_textures[this->m_textureId].height * this->m_textureScale
		};

		this->m_origin = {
			this->m_desRect.width / 2.f,
			this->m_desRect.height / 2.f
		};

		this->m_desRect.x += this->m_origin.x;
		this->m_desRect.y += this->m_origin.y;
	}

	DrawTexturePro(this->m_state->m_textures[this->m_textureId],
		this->m_srcRect,
		{
			this->m_desRect.x,
			this->m_desRect.y,
			this->m_desRect.width,
			this->m_desRect.height
		},
		this->m_origin,
		this->m_angle,
		WHITE
	);
}

Rectangle SKShip::GetView()
{
    return  {
		this->m_position.x,
		this->m_position.y,
		this->m_state->m_renderSize.x,
		this->m_state->m_renderSize.y,
	};
}

Camera2D SKShip::GetCamera()
{
    return this->m_camera;
}

void SKShip::UpdateCameraTarget()
{
	this->m_camera.target.x = this->m_position.x;
	this->m_camera.target.y = this->m_position.y;
}
