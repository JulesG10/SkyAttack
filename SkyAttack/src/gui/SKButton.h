#pragma once
#include "SKGui.h"

class SKButton : public SKGui
{
public:
	SKButton(SKState* state, std::string text, Rectangle rect, Color fg, Color bg);
	~SKButton();

	bool UpdateFrame() override;

	void SetEnable(bool active);
private:
	const int m_fontSize = 20;
	const int m_borderSize = 2;

	bool m_enable;
	Vector2 m_textPosition;
	Rectangle m_rect;

	std::string m_text;

	Color m_background;
	Color m_foreground;
};

