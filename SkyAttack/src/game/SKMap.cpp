#include "SKMap.h"

SKMap::SKMap(SKState* state) : m_state(state)
{
    this->m_available = false;

    this->m_scaleTileW = this->m_tileSize.width * this->m_tileScale;
    this->m_scaleTileH = this->m_tileSize.height * this->m_tileScale;

    this->m_maxTileInView = 
        ceil((this->m_state->m_renderSize.x + this->m_scaleTileW * 1) / this->m_scaleTileW) 
        * ceil((this->m_state->m_renderSize.y + this->m_scaleTileH * 1) / this->m_scaleTileH);

    this->m_mapdir = std::string(GetApplicationDirectory()) + "map";
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


    this->m_renderTileCount = 0;
    for (std::pair<const double, SKTextureId>& tile : this->m_tiles)
    {
        if (this->m_renderTileCount >= this->m_maxTileInView)
        {
            break;
        }

        Vec2 vec = { tile.first };
        Rectangle rect = {
            vec.position.x,
            vec.position.y,
            this->m_scaleTileW,
            this->m_scaleTileH
        };
        if (CheckCollisionRecs(view, rect))
        {
            DrawTexturePro(this->m_state->m_textures[tile.second],
                this->m_tileSize,
                rect,
                { 0,0 }, 0, WHITE);
            this->m_renderTileCount++;
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

void SKMap::SetAvailable(bool val)
{
    this->m_available = val;
}

std::string SKMap::GetMapDir()
{
    return this->m_mapdir;
}

int SKMap::GetRenderTileCount()
{
    return this->m_renderTileCount;
}

int SKMap::GetMaxRenderTileCount()
{
    return this->m_maxTileInView;
}

bool SKMap::LoadMap(std::string path)
{
    this->m_tiles.clear();

    std::ifstream file(path);
    if (!file.good())
    {
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.length() == 0)
        {
            break;
        }

        std::string posX;
        std::string posY;
        std::string tid;
        int change = 0;

        for (size_t i = 0; i < line.length(); i++)
        {
            if (line[i] == ';')
            {
                change++;
            }
            else {
                switch (change)
                {
                case 0:
                    posX += line[i];
                    break;
                case 1:
                    posY += line[i];
                    break;
                case 2:
                    tid += line[i];
                    break;
                default:
                    break;
                }
            }
        }

        if (tid.length() == 0)
        {
            break;
        }
        SKTextureId id = (SKTextureId)std::atoi(tid.c_str());
        if ((id >= SK_MAP_TILE_START && id <= SK_MAP_TILE_END) || id == SKTextureId::ICON_BORDERLIMIT)
        {
            Vec2 vec = { 0 };
            vec.position.x = (float)std::atoi(posX.c_str());
            vec.position.y = (float)std::atoi(posY.c_str());

            this->m_tiles[vec.value] = id;
        }
    }

    file.close();
    return true;
}

bool SKMap::ExportMap(std::string path)
{
    if (!this->m_tiles.size())
    {
        return false;
    }

    std::ofstream file(path, std::ios::in | std::ios::trunc);
    if (!file.good())
    {
        return false;
    }

    for (const std::pair<const double, SKTextureId>& item : this->m_tiles)
    {
        Vec2 vec = { item.first };
        file << (int)vec.position.x << ";" << (int)vec.position.y << ";" << item.second << std::endl;
    }
    file.close();

    return true;
}
