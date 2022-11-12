#include "SKMenuSettings.h"

SKMenuSettings::SKMenuSettings(SKState* state, SKMenuTransition* transition, SKMenuPages* page) : SKMenuPage(state, transition, page)
{
	float topMargin = 220;
	this->m_title = new SKLabel("Settings", { this->m_state->m_renderSize.x / 2.f, 20 }, 60, WHITE, { 1, 0 });

	SKInputKey(this->m_left, this->m_state, 100, topMargin, "Move left");
	SKInputKey(this->m_right, this->m_state, 100, topMargin + 100, "Move right");

	SKInputKey(this->m_slowdown, this->m_state, 100, topMargin + 200, "Slow down");
	SKInputKey(this->m_speedup, this->m_state, 100, topMargin + 300, "Accelerate");

	SKInputKey(this->m_suicide, this->m_state, 100, topMargin + 440, "Capacity 1 (Suicide)");
	SKInputKey(this->m_missile, this->m_state, 100, topMargin + 540, "Capacity 2 (Missile)");
	SKInputKey(this->m_ultime, this->m_state, 100, topMargin + 640, "Ultime Capacity");

	this->m_shootInfo = new SKLabel("(Shoot with Space or left click)", { this->m_state->m_renderSize.x / 2.f, topMargin + 270 }, 20, WHITE, { 1, 0 });
	this->m_backMenu = new SKButton(this->m_state, "Save & Back to Menu",
		SKGui::CenterObject({
			0,
			topMargin + 900,
			350,
			40
			}, this->m_state->m_renderSize, { 1, 0 }), WHITE, BLANK);
}

void SKMenuSettings::DrawFrame()
{
	this->m_title->UpdateFrame();

	if (this->m_left->UpdateFrame())
	{
		this->m_state->m_gamekeys[SKGameKeys::LEFT] = (int)this->m_left->GetText()[0];
	}

	if (this->m_right->UpdateFrame())
	{
		this->m_state->m_gamekeys[SKGameKeys::RIGHT] = (int)this->m_right->GetText()[0];
	}

	if (this->m_slowdown->UpdateFrame())
	{
		this->m_state->m_gamekeys[SKGameKeys::SLOWDOWN] = (int)this->m_slowdown->GetText()[0];
	}

	if (this->m_speedup->UpdateFrame())
	{
		this->m_state->m_gamekeys[SKGameKeys::SPEEDUP] = (int)this->m_speedup->GetText()[0];
	}

	if (this->m_suicide->UpdateFrame())
	{
		this->m_state->m_gamekeys[SKGameKeys::SUICIDE] = (int)this->m_suicide->GetText()[0];

	}
	if (this->m_missile->UpdateFrame())
	{
		this->m_state->m_gamekeys[SKGameKeys::MISSILE] = (int)this->m_missile->GetText()[0];
	}
	if (this->m_ultime->UpdateFrame())
	{
		this->m_state->m_gamekeys[SKGameKeys::ULTIME] = (int)this->m_ultime->GetText()[0];
	}

	this->m_shootInfo->UpdateFrame();


	if (this->m_backMenu->UpdateFrame())
	{
		this->ChangePage(SKMenuPages::PAGE_HOME);
	}
}
