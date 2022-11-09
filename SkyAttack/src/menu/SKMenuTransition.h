#pragma once
#include "../../stdafx.h"
#include "../SKState.h"

enum SKMenuTransitionMode {
	FADE_IN,
	FADE_OUT,
};

enum SKMenuPage {
	PAGE_HOME,
	PAGE_SETTINGS,
	PAGE_MODS,
	PAGE_GAME
};

class SKMenuTransition
{
public:
	SKMenuTransition(SKState* state);
	
	void PageTransition(float msdelay = 0);
	void ResetPage();

	void ShipBackground(float speed  = 20.f);

	SKMenuTransitionMode GetMode();
	bool IsWaiting();
private:
	void AnimateIn();
	void AnimateOut();

	void Draw();

	void ResetIn();
	void ResetOut();

	bool InEnd();
	bool OutEnd();

	void FormatAlpha();

	SKState* m_state;
	float m_alpha;
	float m_y;
	float m_timer = 0;
	SKMenuTransitionMode m_mode = SKMenuTransitionMode::FADE_IN;

	std::vector<std::pair<Vector2, SKTextureId>> m_ships;

	const float m_speed = 2.5;
	const float m_scale = 10;
};

