#include "SKMenu.h"

SKMenu::SKMenu(SKState* state) : m_state(state), m_titlePosition({0,0})
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
		this->m_transition->ResetIn();
		DrawText(this->m_loadText.c_str(), this->m_textPosition.x, this->m_textPosition.y, this->m_textSize, WHITE);
		return;
	}

	if (this->m_transition->m_mode == SKMenuTransitionMode::FADE_OUT)
	{
		this->m_playButton->UpdateFrame();

		this->m_modsButton->UpdateFrame();
		this->m_settingsButton->UpdateFrame();

		if (!this->m_titlePosition.x)
		{
			this->m_titlePosition.x = (this->m_state->renderSize.x - (this->m_state->textures[MENU_TITLE].width * this->m_titleScale)) / 2.f;
		}
		DrawTextureEx(this->m_state->textures[MENU_TITLE], this->m_titlePosition, 0, this->m_titleScale, WHITE);
	}
	else 
	{
		DrawText(this->m_loadText.c_str(), this->m_textPosition.x, this->m_textPosition.y, this->m_textSize, WHITE);
	}
	this->m_transition->PageTransition(2000);
}
