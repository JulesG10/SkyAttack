#pragma once
#include "../../stdafx.h"
#include "SKShip.h"
#include "SKPlayerShip.h"

typedef union Vec2 {
	double value;
	Vector2 position;
}Vec2;


class SKMap
{
public:
	SKMap(SKState*);
	~SKMap();

	virtual void UpdateFrame(Rectangle);
	virtual void LoadMap(std::string);
	virtual bool ExportMap(std::string);

	void SpawnShip(SKShip*);
	bool IsAvailable();

protected:
	const Rectangle m_tileSize = { 0,0,16,16 };
	const float m_tileScale = 4.f;
	int m_maxTileInView = 0;
	float m_scaleTileW;
	float m_scaleTileH;

	bool m_available;
	SKState* m_state;

	std::vector<SKShip*>  m_ships;
	std::unordered_map<double, SKTextureId> m_tiles;

	// bullets
	// items
	// explosions
	// etc...
};

