#include "SKMap.h"

SKMap::SKMap(SKState* state) : m_state(state)
{
    this->m_available = false;
    this->m_maxTileInView = ceil(this->m_state->m_renderSize.x / this->m_tileSize.width) * ceil(this->m_state->m_renderSize.y / this->m_tileSize.height);
}

SKMap::~SKMap()
{
}

void SKMap::UpdateFrame(Rectangle view)
{
    if (!this->m_available)
    {
        return;
    }

    int i = 0;
    for (const SKMapTile& tile : this->m_tiles)
    {
        if (i >= this->m_maxTileInView)
        {
            break;
        }

        if (CheckCollisionRecs(view, tile.rect))
        {
            DrawTexturePro(this->m_state->m_textures[tile.texture],
                this->m_tileSize,
                tile.rect,
                { 0,0 }, 0, WHITE);
            i++;
        }
    }

    for (SKShip* ship : this->m_ships)
    {
        if (CheckCollisionRecs(view, ship->GetView()))
        {
            ship->UpdateFrame();
        }
    }
}

void SKMap::SpawnShip(SKShip* ship)
{
    // TODO: check if is not max
    this->m_ships.push_back(ship);
}

bool SKMap::IsAvailable()
{
    return this->m_available;
}

void SKMap::LoadMap(std::string)
{
    // TODO
    this->m_available = true;

    float x = 0;
    float y = 0;
    for (size_t i = (SKTextureId::NID_LAST_SHIP + 1); i < (SKTextureId::NID_LAST_TILE - 1); i++)
    {
        this->m_tiles.push_back({
            { x , y, this->m_tileSize.width * this->m_tileScale, this->m_tileSize.height * this->m_tileScale },
            (SKTextureId)i
        });

        x += this->m_tileSize.width * this->m_tileScale;
        if ((x + (this->m_tileSize.width * this->m_tileScale)) > this->m_state->m_renderSize.x)
        {
            x = 0;
            y += this->m_tileSize.height * this->m_tileScale;
        }
    }
}