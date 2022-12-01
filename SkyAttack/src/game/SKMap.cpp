#include "SKMap.h"

SKMap::SKMap(SKState* state) : m_state(state)
{
    this->m_available = false;
}

SKMap::~SKMap()
{
}

void SKMap::UpdateFrame()
{
    if (!this->m_available)
    {
        return;
    }

    for (const SKMapTile& tile : this->m_tiles)
    {
        // break if view completed (10x10 tiles)

        // is in view ?
        
        DrawTexturePro(this->m_state->m_textures[tile.texture],
            this->m_tileSize,
            {
                tile.position.x, tile.position.y,
               this->m_tileSize.width * this->m_tileScale, this->m_tileSize.height * this->m_tileScale
            }, 
            { 0,0 }, 0, WHITE);
        DrawText(std::to_string(tile.texture - (SKTextureId::NID_LAST_SHIP+1)).c_str(), tile.position.x, tile.position.y, 10, BLACK);
    }

    for (const SKShip* ship : this->m_ships)
    {
        // is in view ?
        // ship->UpdateFrame();
    }
}

void SKMap::SpawnShip(SKShip*)
{
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
            { x , y },
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

void SKMap::MapEditor()
{
    
}
