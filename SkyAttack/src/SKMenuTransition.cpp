#include "SKMenuTransition.h"

SKMenuTransition::SKMenuTransition(SKState* state) : m_state(state), m_y(-100), m_alpha(255), m_timer(-1)
{
	this->ResetPage();
}

void  SKMenuTransition::Draw()
{
	Color tint = { 255, 255, 255, this->m_alpha };
	bool change = true;
	for (int i = -300; i < (int)this->m_state->renderSize.y; i++)
	{
		Texture cloud = this->m_state->textures[SKTextureId::CLOUDS_1];
		if (change)
		{
			cloud = this->m_state->textures[SKTextureId::CLOUDS_2];
		}
		change = !change;

		DrawTextureEx(cloud, { this->m_y, (float)i }, 0, this->m_scale, tint);
		DrawTextureEx(cloud, { this->m_y + cloud.width * (this->m_scale / 2.f), (float)i }, 0, this->m_scale, tint);

		DrawTextureEx(cloud, { (this->m_state->renderSize.x - (cloud.width * this->m_scale)) - this->m_y , (float)i }, 0, this->m_scale, tint);
		DrawTextureEx(cloud, { (this->m_state->renderSize.x - (cloud.width * this->m_scale)) - (this->m_y + cloud.width * (this->m_scale / 2.f)), (float)i }, 0, this->m_scale, tint);


		i += cloud.height * (this->m_scale / 2.f);
	}

	DrawRectangleGradientH(0, 0, 1000 - this->m_y, this->m_state->renderSize.y, tint, BLANK);
	DrawRectangleGradientH(this->m_state->renderSize.x - 1000, 0,1000 - this->m_y, this->m_state->renderSize.y, BLANK, tint);
}

void SKMenuTransition::AnimateOut()
{
	if (this->OutEnd())
	{
		this->Draw();
		return;
	}

	this->m_y -= this->m_speed * 200 * GetFrameTime();
	this->m_alpha -= this->m_speed * 180 * GetFrameTime();

	this->Draw();
}


void SKMenuTransition::AnimateIn()
{
	if (this->m_alpha >= 255)
	{
		this->m_alpha = 255;
	}

	if (this->InEnd())
	{
		this->Draw();
		return;
	}

	this->m_y += this->m_speed * 200 * GetFrameTime();
	this->m_alpha += this->m_speed * 180 * GetFrameTime();
	this->Draw();
}

void SKMenuTransition::PageTransition(float delay)
{
	if (!this->m_mode)
	{
		this->AnimateIn();
		if (this->InEnd())
		{
			if (this->m_timer == -1)
			{
				this->m_timer = delay;
			}
			this->m_timer -= 1000 * GetFrameTime();
			
			if (this->m_timer <= 0)
			{
				this->m_mode = SKMenuTransitionMode::FADE_OUT;
				this->m_timer = -1;
			}
		}
		return;
	}

	this->AnimateOut();
}

void SKMenuTransition::ResetPage()
{
	this->m_mode = SKMenuTransitionMode::FADE_IN;
	this->m_timer = -1;
	this->ResetIn();
}

void SKMenuTransition::ResetIn()
{
	this->m_y = -800;
	this->m_alpha = 0;
}

void SKMenuTransition::ResetOut()
{
	this->m_y = -50;
	this->m_alpha = 255;
}

bool SKMenuTransition::InEnd()
{
	return this->m_y >= -100;
}

bool SKMenuTransition::OutEnd()
{
	return this->m_alpha <= 0;
}