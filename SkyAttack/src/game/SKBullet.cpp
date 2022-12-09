#include "SKBullet.h"

SKBullet::SKBullet(SKState* state, SKBulletOptions options)
{
    this->m_options = options;
    this->m_state = state;
}

void SKBullet::SetOptions(SKBulletOptions options)
{
    this->m_options = options;
}

SKBulletOptions SKBullet::GetOptions()
{
    return this->m_options;
}

Rectangle SKBullet::GetView()
{
    Vector2 position = Vector2Subtract(this->m_options.position, this->m_options.origin);
    return {
        position.x,
        position.y,
        this->m_state->m_renderSize.x,
        this->m_state->m_renderSize.y,
    };
}

bool SKBullet::UpdateFrame()
{
    DrawTexturePro(
        this->m_state->m_textures[this->m_options.texture],
        { 0, 0, this->m_options.size.x, this->m_options.size.y },
        { this->m_options.position.x, this->m_options.position.y,  this->m_options.size.x * this->m_options.scale, this->m_options.size.y * this->m_options.scale },
        this->m_options.origin, this->m_options.angle, WHITE
    );

    
    this->Reduce(&this->m_options.velocity.x);
    this->Reduce(&this->m_options.velocity.y);

    this->m_options.position.x += this->m_options.velocity.x * GetFrameTime();
    this->m_options.position.y += this->m_options.velocity.y * GetFrameTime();

    return !this->m_options.velocity.x && !this->m_options.velocity.y;
}

void SKBullet::Reduce(float* val)
{
    *val *= this->m_options.reducingFactor;
    if (abs(*val) < 1)
    {
        *val = 0;
    }
}
