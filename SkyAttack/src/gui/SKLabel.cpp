#include "SKLabel.h"

SKLabel::SKLabel(std::string text, Vector2 position,int fontsize, Color color, Vector2 center) : SKGui(nullptr), m_text(text), m_color(color), m_fontsize(fontsize)
{
	Vector2 size = MeasureTextEx(GetFontDefault(), this->m_text.c_str(), this->m_fontsize, 1);
	this->m_position = {
			position.x - (size.x/2) * center.x,
			position.y - (size.y/2) * center.y
	};
}

SKLabel::~SKLabel()
{
}

bool SKLabel::UpdateFrame()
{
	DrawText(this->m_text.c_str(), this->m_position.x, this->m_position.y, this->m_fontsize, this->m_color);
	return false;
}
