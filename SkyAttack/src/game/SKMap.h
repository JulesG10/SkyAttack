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
	SKMap(SKState*);
	~SKMap();

	void UpdateFrame();
	void SpawnShip(SKShip*);

	bool IsAvailable();

	void LoadMap(std::string);
	void MapEditor();
protected:
	const Rectangle m_tileSize = { 0,0,16,16 };
	const float m_tileScale = 4.f;

	bool m_available;
	SKState* m_state;

	std::vector<SKShip*>  m_ships;
	std::vector<SKMapTile> m_tiles;
	
	// bullets
	// items
	// explosions
	// etc...
};

