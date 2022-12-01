#include "SKMenu.h"

SKMenu::SKMenu(SKState* state) : m_state(state), m_titlePosition({ 0,0 })
{
	this->m_loadText = "Loading...";
	this->m_textSize = 30;

	Vector2 textSize = MeasureTextEx(GetFontDefault(), this->m_loadText.c_str(), this->m_textSize, 1);
	this->m_textPosition = { (this->m_state->m_renderSize.x - textSize.x) / 2.f, (this->m_state->m_renderSize.y - textSize.y) / 2.f };

	this->m_pseudo = new SKInput(this->m_state, {
			(this->m_state->m_renderSize.x - 200) / 2,
			(this->m_state->m_renderSize.y - 150) / 2,
			200,
			40
		}, WHITE, BLANK, "Pseudo...");

	this->m_playButton = new SKButton(this->m_state, "Play Multi", {
		(this->m_state->m_renderSize.x - 200) / 2,
		(this->m_state->m_renderSize.y - 50) / 2,
		200,
		40
		}, WHITE, BLANK);

	this->m_modsButton = new SKButton(this->m_state, "Mods", {
		(this->m_state->m_renderSize.x - 200) / 2,
		(this->m_state->m_renderSize.y + 50) / 2,
		200,
		40
		}, WHITE, BLANK);
	this->m_modsButton->SetEnable(false);

	this->m_settingsButton = new SKButton(this->m_state, "Settings", {
		(this->m_state->m_renderSize.x - 200) / 2,
		(this->m_state->m_renderSize.y + 150) / 2,
		200,
		40
		}, WHITE, BLANK);

	this->m_transition = new SKMenuTransition(this->m_state);

	this->m_page = SKMenuPages::PAGE_HOME;
	this->m_nextPage = SKMenuPages::PAGE_NONE;

	this->m_settings = new SKMenuSettings(this->m_state, this->m_transition, &this->m_page);
	this->m_game = new SKMenuGame(this->m_state, this->m_transition, &this->m_page);
	this->m_mods = new SKMenuMods(this->m_state, this->m_transition, &this->m_page);
}

SKMenu::~SKMenu()
{
}

void SKMenu::DrawFrame()
{
	DrawRectangle(0, 0, this->m_state->m_renderSize.x, this->m_state->m_renderSize.y, { 150, 210, 50, 255 });
	if (this->m_state->m_loading)
	{
		DrawText(this->m_loadText.c_str(), this->m_textPosition.x, this->m_textPosition.y, this->m_textSize, WHITE);
		return;
	}

	if (this->m_transition->GetMode() == SKMenuTransitionMode::FADE_OUT || this->m_nextPage != SKMenuPages::PAGE_HOME)
	{
		this->m_transition->ShipBackground();

		if (this->m_playButton->UpdateFrame() && this->m_nextPage == SKMenuPages::PAGE_NONE)
		{
			this->m_nextPage = SKMenuPages::PAGE_GAME;
			this->m_transition->ResetPage();
		}

		if (this->m_modsButton->UpdateFrame() && this->m_nextPage == SKMenuPages::PAGE_NONE)
		{
			this->m_nextPage = SKMenuPages::PAGE_MODS;
			this->m_transition->ResetPage();
		}

		if (this->m_settingsButton->UpdateFrame() && this->m_nextPage == SKMenuPages::PAGE_NONE)
		{
			this->m_nextPage = SKMenuPages::PAGE_SETTINGS;
			this->m_transition->ResetPage();
		}

		this->m_pseudo->UpdateFrame();

		if (!this->m_titlePosition.x)
		{
			this->m_titlePosition.x = (this->m_state->m_renderSize.x - (this->m_state->m_textures[MENU_TITLE].width * this->m_titleScale)) / 2.f;
		}
		DrawTextureEx(this->m_state->m_textures[MENU_TITLE], this->m_titlePosition, 0, this->m_titleScale, WHITE);
	}
	else
	{
		DrawText(this->m_loadText.c_str(), this->m_textPosition.x, this->m_textPosition.y, this->m_textSize, WHITE);
	}
	this->m_transition->PageTransition(1500);

	if (this->m_transition->IsWaiting() && this->m_nextPage != SKMenuPages::PAGE_NONE)
	{
		this->m_page = this->m_nextPage;
		this->m_nextPage = SKMenuPages::PAGE_NONE;
	}
}

void SKMenu::UpdateFrame()
{
	switch (this->m_page)
	{
	case SKMenuPages::PAGE_SETTINGS:
		this->m_settings->UpdateFrame();
		break;
	case SKMenuPages::PAGE_MODS:
		this->m_mods->UpdateFrame();
		break;
	case SKMenuPages::PAGE_GAME:
		this->m_game->UpdateFrame();
		break;
	case SKMenuPages::PAGE_HOME:
	case SKMenuPages::PAGE_NONE:
	default:
		this->DrawFrame();
		break;
	}
}
