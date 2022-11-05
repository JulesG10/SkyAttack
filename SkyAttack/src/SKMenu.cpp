#include "SKMenu.h"

SKMenu::SKMenu(SKState* state) : m_state(state)
{
	this->m_loadText = "Loading...";
	this->m_textSize = 30;

	Vector2 textSize = MeasureTextEx(GetFontDefault(), this->m_loadText.c_str(), this->m_textSize, 1);
	this->m_textPosition = { (this->m_state->renderSize.x - textSize.x) / 2.f, (this->m_state->renderSize.y - textSize.y) / 2.f };

	this->m_playButton = new SKButton(this->m_state, "Play Multi", { 
		(this->m_state->renderSize.x - 200) / 2,
		(this->m_state->renderSize.y - 150) / 2,
		200,
		40
		}, WHITE, BLANK);
	
	this->m_modsButton = new SKButton(this->m_state, "Mods", {
		(this->m_state->renderSize.x - 200) / 2,
		(this->m_state->renderSize.y - 50) / 2,
		200,
		40
		}, WHITE, BLANK);

	this->m_settingsButton = new SKButton(this->m_state, "Settings", {
		(this->m_state->renderSize.x - 200) / 2,
		(this->m_state->renderSize.y + 50) / 2,
		200,
		40
		}, WHITE, BLANK);

	this->m_skText = new SKLabel("Sky Attack", { this->m_state->renderSize.x/2, 60 }, 70, WHITE, {1,0});
	
	this->m_transition = new SKMenuTransition(this->m_state);
}

SKMenu::~SKMenu()
{
}


void SKMenu::UpdateFrame()
{
	static bool mode = false;

	DrawRectangle(0, 0, this->m_state->renderSize.x, this->m_state->renderSize.y, { 150, 210, 50, 255 });

	if (this->m_state->loading)
	{
		DrawText(this->m_loadText.c_str(), this->m_textPosition.x, this->m_textPosition.y, this->m_textSize, WHITE);
		return;
	}

	if (this->m_transition->m_mode == SKMenuTransitionMode::FADE_OUT)
	{
		this->m_playButton->UpdateFrame();

		this->m_modsButton->UpdateFrame();
		this->m_settingsButton->UpdateFrame();

		this->m_skText->UpdateFrame();
	}
	else 
	{
		DrawText(this->m_loadText.c_str(), this->m_textPosition.x, this->m_textPosition.y, this->m_textSize, WHITE);
	}
	this->m_transition->PageTransition(2000);
}
