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
	DrawTexturePro(this->m_state->m_textures[this->m_textureId],
		{ 
			0,0,
			(float)this->m_state->m_textures[this->m_textureId].width, (float)this->m_state->m_textures[this->m_textureId].height
		},
		{
			this->m_camera.offset.x + (this->m_state->m_renderSize.x - (float)this->m_state->m_textures[this->m_textureId].width * this->m_textureScale)/2.f,
			this->m_camera.offset.y + (this->m_state->m_renderSize.y - (float)this->m_state->m_textures[this->m_textureId].height * this->m_textureScale)/2.f,
			(float)this->m_state->m_textures[this->m_textureId].width * this->m_textureScale,
			(float)this->m_state->m_textures[this->m_textureId].height * this->m_textureScale
		},
		{ 0,0 },// TODO
		this->m_angle,
		WHITE
	);
}

Rectangle SKShip::GetView()
{
    return  {
		this->m_camera.offset.x,
		this->m_camera.offset.y,
		this->m_state->m_renderSize.x,
		this->m_state->m_renderSize.y
	};
}

Camera2D SKShip::GetCamera()
{
    return this->m_camera;
}
