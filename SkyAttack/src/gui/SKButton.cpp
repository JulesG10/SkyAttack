#include "SKButton.h"

SKButton::SKButton(SKState* state, std::string text, Rectangle rect, Color fg, Color bg) : SKGui(state)
{
    this->m_text = text;
    this->m_background = bg;
    this->m_foreground = fg;
    this->m_rect = rect;

    Vector2 textSize = MeasureTextEx(GetFontDefault(), this->m_text.c_str(), this->m_fontSize, 1);
    this->m_textPosition = {
        this->m_rect.x + (m_rect.width - textSize.x) / 2,
        this->m_rect.y + (m_rect.height - textSize.y) / 2
    };
}

SKButton::~SKButton()
{
}

bool SKButton::UpdateFrame()
{
    Color borderFg = this->m_foreground;
    Color back = this->m_background;

    bool colide = false;
    if (CheckCollisionPointRec(this->m_state->GetMouse(), this->m_rect))
    {
        borderFg.a -= 50;
        back.a -= 50;
        colide = true;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        { 
            DrawRectangle(this->m_rect.x, this->m_rect.y, this->m_rect.width, this->m_rect.height, back);
            DrawRectangleLinesEx(this->m_rect, m_borderSize, this->m_foreground);
            DrawText(this->m_text.c_str(), this->m_textPosition.x, this->m_textPosition.y, this->m_fontSize, this->m_foreground);
        }
    }

    DrawRectangle(this->m_rect.x, this->m_rect.y, this->m_rect.width, this->m_rect.height, back);
    DrawRectangleLinesEx(this->m_rect, m_borderSize, borderFg);
    DrawText(this->m_text.c_str(), this->m_textPosition.x, this->m_textPosition.y, this->m_fontSize, borderFg);

    
    return IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && colide;
}
