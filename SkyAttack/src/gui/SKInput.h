#pragma once

#include "../../stdafx.h"
#include "../SKState.h"

#define SK_AZERTY_BACKSPACE 259
#define SK_AZERTY_UP 265
#define SK_AZERTY_DOWN 264
#define SK_AZERTY_LEFT 263
#define SK_AZERTY_RIGHT 262
#define SK_AZERTY_SHIFT 340

class SKInput
{
public:
	SKInput(SKState* state, Rectangle rect, Color fg, Color bg, std::string placeholder = "");

	bool UpdateFrame();

	std::string GetText();
	void SetText(std::string);
private:
	const int m_fontSize = 20;
	const int m_borderSize = 2;
	const char m_allowed[64] = {
	   'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	   'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
	   '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
	};

	const std::vector<std::pair<int, char>> m_azerty = {
	{81, 'a'},
	{66, 'b'},
	{67, 'c'},
	{68, 'd'},
	{69, 'e'},
	{70, 'f'},
	{71, 'g'},
	{72, 'h'},
	{73, 'i'},
	{74, 'j'},
	{75, 'k'},
	{76, 'l'},
	{59, 'm'},
	{78, 'n'},
	{79, 'o'},
	{80, 'p'},
	{65, 'q'},
	{82, 'r'},
	{83, 's'},
	{84, 't'},
	{85, 'u'},
	{86, 'v'},
	{90, 'w'},
	{88, 'x'},
	{89, 'y'},
	{87, 'z'},
	{48, '0'},
	{49, '1'},
	{50, '2'},
	{51, '3'},
	{52, '4'},
	{53, '5'},
	{54, '6'},
	{55, '7'},
	{56, '8'},
	{57, '9'},
	};

	char ConvertQwerty(int);
	bool Allowed(char);

	Vector2 m_textPosition;
	bool m_focus;
	bool m_maj;
	std::string m_text;
	std::string m_placeholder;
	
	Rectangle m_rect;
	SKState* m_state;
	Color m_background;
	Color m_foreground;
};

