#include "SKMenuSettings.h"

SKMenuSettings::SKMenuSettings(SKState* state, SKMenuTransition* transition, SKMenuPage* page) : m_state(state), m_transition(transition), m_page(page)
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
			}, this->m_state->m_renderSize, {1, 0}), WHITE, BLANK);

	this->m_changePage = false;
}

void SKMenuSettings::UpdateFrame()
{
	DrawRectangle(0, 0, this->m_state->m_renderSize.x, this->m_state->m_renderSize.y, { 150, 210, 50, 255 });
	if (this->m_transition->GetMode() == SKMenuTransitionMode::FADE_OUT || this->m_changePage)
	{
		this->m_transition->ShipBackground();

		this->m_title->UpdateFrame();

		this->m_left->UpdateFrame();
		this->m_right->UpdateFrame();

		this->m_slowdown->UpdateFrame();
		this->m_speedup->UpdateFrame();

		this->m_suicide->UpdateFrame();
		this->m_missile->UpdateFrame();
		this->m_ultime->UpdateFrame();

		this->m_shootInfo->UpdateFrame();

		if (this->m_backMenu->UpdateFrame())
		{
			this->m_transition->ResetPage();
			this->m_changePage = true;
		}
	}
	this->m_transition->PageTransition(500);
	if (this->m_transition->IsWaiting() && this->m_changePage)
	{
		this->m_changePage = false;
		*(this->m_page) = SKMenuPage::PAGE_HOME;
	}
}
