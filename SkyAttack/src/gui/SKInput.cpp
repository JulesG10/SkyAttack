#include "SKInput.h"

SKInput::SKInput(SKState* state, Rectangle rect, Color fg, Color bg, std::string placeholder) : m_rect(rect), m_state(state), m_foreground(fg), m_background(bg), m_placeholder(placeholder)
{
    this->m_textPosition = {
        this->m_rect.x + 5,
        this->m_rect.y + this->m_fontSize/2.f
    };
}

bool SKInput::UpdateFrame()
{
    Color borderFg = this->m_foreground;
    if (CheckCollisionPointRec(this->m_state->GetMouse(), this->m_rect))
    {
        borderFg.a -= 50;
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            this->m_focus = true;
        }
    }
    else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        this->m_focus = false;
    }

    if (this->m_focus)
    {
        int qwkey = GetKeyPressed();
        char key = this->ConvertQwerty(qwkey);
        
        if (qwkey == SK_AZERTY_BACKSPACE && this->m_text.length() > 0)
        {
            this->m_text.pop_back();
        }
        else if (qwkey == SK_AZERTY_SHIFT)
        {
            this->m_maj = true;
        }else if (key && this->Allowed(key))
        {
            if (this->m_maj)
            {
                if (key >= 'a' && key <= 'z')
                {
                    key = std::toupper(key);
                }
                this->m_maj = false;
            }

            this->m_text += key;
            Vector2 size = MeasureTextEx(GetFontDefault(), this->m_text.c_str(), this->m_fontSize, 1);
            if ((size.x + 25) >= this->m_rect.width)
            {
                this->m_text.pop_back();
            }
        }
    }

    DrawRectangle(this->m_rect.x, this->m_rect.y, this->m_rect.width, this->m_rect.height, this->m_background);
    DrawRectangleLinesEx(this->m_rect, m_borderSize, borderFg);
    if (this->m_text.length())
    {
        DrawText(this->m_text.c_str(), this->m_textPosition.x, this->m_textPosition.y, this->m_fontSize, borderFg);
    }
    else {
        DrawText(this->m_placeholder.c_str(), this->m_textPosition.x, this->m_textPosition.y, this->m_fontSize, { 80, 80, 80, 100 });
    }

    return this->m_focus;
}

char SKInput::ConvertQwerty(int key)
{
    for (const std::pair<int, char>& p : this->m_azerty)
    {
        if (p.first == key)
        {
            return p.second;
        }
    }

    return key;
}

std::string SKInput::GetText()
{
    return this->m_text;
}

void SKInput::SetText(std::string text)
{
    this->m_text = "";
    for (size_t i = 0; i < text.length(); i++)
    {
        if (this->Allowed(text[i]))
        {
            this->m_text += text[i];
        }
    }
}

bool SKInput::Allowed(char c)
{
    for (int i = 0; i < (sizeof(m_allowed)/sizeof(char)); i++)
    {
        if (c == m_allowed[i])
        {
            return true;
        }
    }

    return false;
}
