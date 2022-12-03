#include "SKInput.h"

SKInput::SKInput(SKState* state, Rectangle rect, Color fg, Color bg, std::string placeholder) : SKGui(state), m_rect(rect), m_foreground(fg), m_background(bg), m_placeholder(placeholder)
{
    this->m_textPosition = {
        this->m_rect.x + this->m_baseMargin,
        this->m_rect.y + this->m_fontSize/2.f
    };

    this->m_blinkfocus = 100.f;
    this->m_textCenter = false;
    this->m_textWidth = 0;
}

bool SKInput::UpdateFrame()
{
    Color borderFg = this->m_foreground;
    if (this->m_blinkfocus <= -20 || !this->m_focus)
    {
        this->m_blinkfocus = 100;
    }

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
        bool keyFound = false;
        char key = SKInputManager::Instance()->ConvertQwerty(qwkey, &keyFound);
        
        if (qwkey == SK_AZERTY_BACKSPACE && this->m_text.length() > 0)
        {
            this->m_text.pop_back();
            this->m_textWidth = MeasureText(this->m_text.c_str(), this->m_fontSize);
            this->CenterText();
        }
        else if (qwkey == SK_AZERTY_SHIFT)
        {
            this->m_maj = true;
        }else if (key && keyFound && this->Allowed(key) && this->m_text.length() < this->m_maxlength)
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
            int textWidth = MeasureText(this->m_text.c_str(), this->m_fontSize);
            if ((textWidth + 25) >= this->m_rect.width)
            {
                this->m_text.pop_back();
            }
            else {
                this->m_textWidth = textWidth;
            }

            this->CenterText();
        }
        
        
        this->m_blinkfocus -= GetFrameTime() * 200;
    }

    DrawRectangle(this->m_rect.x, this->m_rect.y, this->m_rect.width, this->m_rect.height, this->m_background);
    DrawRectangleLinesEx(this->m_rect, m_borderSize, borderFg);

    if (this->m_prefix.length())
    {
        DrawText(this->m_prefix.c_str(), this->m_prefixPosition.x, this->m_prefixPosition.y, this->m_fontSize, borderFg);
    }
    
    if (this->m_text.length())
    {
        DrawText(this->m_text.c_str(), this->m_textPosition.x, this->m_textPosition.y, this->m_fontSize, borderFg);

        if (this->m_focus && this->m_blinkfocus > 0)
        {
            DrawRectangle(this->m_textPosition.x + this->m_textWidth + 2, this->m_textPosition.y, 2, this->m_fontSize, WHITE);
        }
    }
    else {
        DrawText(this->m_placeholder.c_str(), this->m_rect.x + this->m_baseMargin, this->m_rect.y + this->m_fontSize/2.f, this->m_fontSize, { 80, 80, 80,  (unsigned char)(borderFg.a-40) });
    }

    return this->m_focus;
}

void SKInput::SetLength(int length)
{
    this->m_maxlength = length;
}

void SKInput::SetPrefix(std::string prefix)
{
    this->m_prefix = prefix;
    this->m_prefixPosition = {
        this->m_rect.x - (MeasureText(this->m_prefix.c_str(), this->m_fontSize) + this->m_baseMargin),
        this->m_rect.y + this->m_fontSize / 2.f
    };
}

void SKInput::CenterText()
{
    if (this->m_textCenter)
    {
        this->m_textPosition.x = this->m_rect.x + (this->m_rect.width - MeasureText(this->m_text.c_str(), this->m_fontSize)) / 2.f;
    }
}

void SKInput::SetTextCenter(bool center)
{
    this->m_textCenter = center;
}

std::string SKInput::GetText()
{
    if (this->m_text.length())
    {
        return this->m_text;
    }
    return "\0";
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

    this->m_textWidth = MeasureText(this->m_text.c_str(), this->m_fontSize);
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
