#pragma once
#include "../../stdafx.h"
#include "SKShip.h"
#include "SKPlayerShip.h"

typedef struct SKMapTile {
	Rectangle rect;
	SKTextureId texture;
}SKMapTile;

class SKMap
{
public:
	SKMap(SKState*);
	~SKMap();

	void UpdateFrame(Rectangle);
	void SpawnShip(SKShip*);

	bool IsAvailable();

	void LoadMap(std::string);
protected:
	const Rectangle m_tileSize = { 0,0,16,16 };
	const float m_tileScale = 4.f;
	int m_maxTileInView = 0;

	bool m_available;
	SKState* m_state;

	std::vector<SKShip*>  m_ships;
	std::vector<SKMapTile> m_tiles;
	
	// bullets
	// items
	// explosions
	// etc...
};

