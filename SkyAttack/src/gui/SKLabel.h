#pragma once
#include "../../stdafx.h"

class SKLabel
{
public:
	SKLabel(std::string text, Vector2 position, int fontsize, Color color, Vector2 center = {1,1});
	~SKLabel();

	void UpdateFrame();
private:
	int m_fontsize;
	Vector2 m_position;
	Color m_color;
	std::string m_text;
};

