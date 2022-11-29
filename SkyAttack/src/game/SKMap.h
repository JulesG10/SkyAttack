#pragma once
#include "../../stdafx.h"
#include "SKShip.h"

typedef struct SKMapTile {
	Vector2 position;
	SKTextureId texture;
}SKMapTile;

class SKMap
{
public:
	SKMap();
	~SKMap();

	void UpdateFrame();
	void SpawnShip(SKShip*);

	bool IsAvailable();

	void LoadMap(std::string);
	void GenerateMap();
protected:
	bool m_available;
	std::vector<SKShip*> ships;
	std::vector<SKMapTile> tiles;
};

