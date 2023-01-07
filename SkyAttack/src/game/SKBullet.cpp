#include "SKBullet.h"

SKBullet::SKBullet(SKState* state, SKBulletOptions options)
{
    this->m_options = options;
    this->m_state = state;
    this->m_distance = 0;
}

Vector2 SKBullet::CalculateVelocity(float force, float angle)
{
    return  {
            (force * std::cos(angle * DEG2RAD)),
            (force * std::sin(angle * DEG2RAD))
    };
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
        position.x - this->m_state->m_renderSize.x/2.f,
        position.y - this->m_state->m_renderSize.y/2.f,
        this->m_state->m_renderSize.x,
        this->m_state->m_renderSize.y,
    };
}

Rectangle SKBullet::GetBounds()
{
    return  { this->m_options.position.x, this->m_options.position.y,  this->m_options.size.x * this->m_options.scale, this->m_options.size.y * this->m_options.scale };
}

bool SKBullet::UpdateFrame(bool isInView)
{
    if (isInView)
    {
        DrawTexturePro(
            this->m_state->m_textures[this->m_options.texture],
            { 0, 0, this->m_options.size.x, this->m_options.size.y },
            { this->m_options.position.x, this->m_options.position.y,  this->m_options.size.x * this->m_options.scale, this->m_options.size.y * this->m_options.scale },
            this->m_options.origin, this->m_options.angle, WHITE
        );
        //DrawText(std::to_string(this->m_distance).c_str(), this->m_options.position.x, this->m_options.position.y, 20, BLACK);
    }

    float x = this->m_options.position.x;
    float y = this->m_options.position.y;
    this->m_options.position.x += this->m_options.velocity.x * GetFrameTime();
    this->m_options.position.y += this->m_options.velocity.y * GetFrameTime();

    this->m_distance += std::abs(Vector2Distance({ x,y }, this->m_options.position));
    if (this->m_distance >= this->m_options.maxDistance)
    {
        this->m_options.velocity = { 0,0 };
    }
    return !this->m_options.velocity.x && !this->m_options.velocity.y;
}
