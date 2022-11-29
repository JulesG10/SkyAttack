#include "SKMap.h"

SKMap::SKMap()
{
    this->m_available = false;
}

SKMap::~SKMap()
{
}

void SKMap::UpdateFrame()
{
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
    //this->m_available = true;
}

void SKMap::GenerateMap()
{
}
