#pragma once

#include "SKGui.h"

#define SKInputKey(inp, state, x, y, text) {\
	inp = new SKInput(state, SKGui::CenterObject({ x, y, 40, 40 }, state->m_renderSize, { 1, 0 }), WHITE, BLANK, "..."); \
	inp->SetLength(1); \
	inp->SetPrefix(text); \
	inp->SetTextCenter(true); \
}

class SKInput : public SKGui
{
public:
	SKInput(SKState* state, Rectangle rect, Color fg, Color bg, std::string placeholder = "");

	bool UpdateFrame() override;

	std::string GetText();
	void SetText(std::string);
	void SetLength(int);
	void SetPrefix(std::string);
	void SetTextCenter(bool);

private:
	const int m_fontSize = 20;
	const int m_borderSize = 2;
	const int m_baseMargin = 8;

	const char m_allowed[64] = {
	   'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	   'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
	   '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
	};

	bool Allowed(char);
	void CenterText();

	Vector2 m_textPosition;
	bool m_textCenter;
	bool m_focus;
	float m_blinkfocus;
	bool m_maj;
	int m_textWidth;

	std::string m_prefix;
	Vector2 m_prefixPosition;

	int m_maxlength = 1000;
	std::string m_text;
	std::string m_placeholder;
	
	Rectangle m_rect;
	Color m_background;
	Color m_foreground;
};

