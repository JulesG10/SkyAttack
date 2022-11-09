#pragma once

#include "../stdafx.h"

#define SK_AZERTY_BACKSPACE 259
#define SK_AZERTY_UP 265
#define SK_AZERTY_DOWN 264
#define SK_AZERTY_LEFT 263
#define SK_AZERTY_RIGHT 262
#define SK_AZERTY_SHIFT 340

class SKInputManager
{
public:
	SKInputManager();
	~SKInputManager();
	
	static SKInputManager* Instance() {
		static SKInputManager* m_instance = new SKInputManager();
		return m_instance;
	}
	
	char GetKeyAzerty();
	char ConvertQwerty(int);
private:
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
};

