#include "SKMenuSettings.h"

SKMenuSettings::SKMenuSettings(SKState* state, SKMenuTransition* transition, SKMenuPages* page) : SKMenuPage(state, transition, page)
{
	float topMargin = 220;
	this->m_title = SK_NEW SKLabel("Settings", { this->m_state->m_renderSize.x / 2.f, 20 }, 60, WHITE, { 1, 0 });

	SKInputKey(this->m_left, this->m_state, 100, topMargin, "Move left");
	SKInputKey(this->m_right, this->m_state, 100, topMargin + 100, "Move right");
	SKInputKey(this->m_slowdown, this->m_state, 100, topMargin + 200, "Slow down");
	SKInputKey(this->m_speedup, this->m_state, 100, topMargin + 300, "Accelerate");
	SKInputKey(this->m_suicide, this->m_state, 100, topMargin + 440, "Capacity 1 (Suicide)");
	SKInputKey(this->m_missile, this->m_state, 100, topMargin + 540, "Capacity 2 (Missile)");
	SKInputKey(this->m_ultime, this->m_state, 100, topMargin + 640, "Ultime Capacity");

	this->m_shootInfo = SK_NEW SKLabel("(Shoot with Space or left click)", { this->m_state->m_renderSize.x / 2.f, topMargin + 270 }, 20, WHITE, { 1, 0 });
	this->m_backMenu = SK_NEW SKButton(this->m_state, "Save & Back to Menu",
		SKGui::CenterObject({
			0,
			topMargin + 900,
			350,
			40
			}, this->m_state->m_renderSize, { 1, 0 }), WHITE, BLANK);
}

SKMenuSettings::~SKMenuSettings()
{
	delete this->m_left;
	delete this->m_right;

	delete this->m_slowdown;
	delete this->m_speedup;
	delete this->m_suicide;
	delete this->m_missile;
	delete this->m_ultime;

	delete this->m_title;
	delete 	this->m_shootInfo;
	delete 	this->m_backMenu;
}

void SKMenuSettings::UpdateFrame()
{
	SKMenuPage::UpdateFrame();
	return;
}


void SKMenuSettings::UpdatePageFrame()
{
	if (!this->m_setDefaultKey)
	{
		
		PRESET_TEXT(left,LEFT);
		PRESET_TEXT(right, RIGHT);
		PRESET_TEXT(slowdown, SLOWDOWN);
		PRESET_TEXT(speedup, SPEEDUP);
		PRESET_TEXT(suicide, SUICIDE);
		PRESET_TEXT(missile, MISSILE);
		PRESET_TEXT(ultime, ULTIME);

		this->m_setDefaultKey = true;
	}

	this->m_title->UpdateFrame();

	if (this->m_left->UpdateFrame())
	{
		this->m_state->m_gamekeys[SKGameKeys::LEFT] =  SKInputManager::Instance()->ConvertAzery(this->m_left->GetText()[0]);
	}

	if (this->m_right->UpdateFrame())
	{
		this->m_state->m_gamekeys[SKGameKeys::RIGHT] = SKInputManager::Instance()->ConvertAzery(this->m_right->GetText()[0]);
	}

	if (this->m_slowdown->UpdateFrame())
	{
		this->m_state->m_gamekeys[SKGameKeys::SLOWDOWN] = SKInputManager::Instance()->ConvertAzery(this->m_slowdown->GetText()[0]);
	}

	if (this->m_speedup->UpdateFrame())
	{
		this->m_state->m_gamekeys[SKGameKeys::SPEEDUP] = SKInputManager::Instance()->ConvertAzery(this->m_speedup->GetText()[0]);
	}

	if (this->m_suicide->UpdateFrame())
	{
		this->m_state->m_gamekeys[SKGameKeys::SUICIDE] = SKInputManager::Instance()->ConvertAzery(this->m_suicide->GetText()[0]);

	}
	if (this->m_missile->UpdateFrame())
	{
		this->m_state->m_gamekeys[SKGameKeys::MISSILE] = SKInputManager::Instance()->ConvertAzery(this->m_missile->GetText()[0]);
	}
	if (this->m_ultime->UpdateFrame())
	{
		this->m_state->m_gamekeys[SKGameKeys::ULTIME] = SKInputManager::Instance()->ConvertAzery(this->m_ultime->GetText()[0]);
	}

	this->m_shootInfo->UpdateFrame();


	if (this->m_backMenu->UpdateFrame())
	{
		this->ChangePage(SKMenuPages::PAGE_HOME);
	}
}
