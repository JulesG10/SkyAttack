#pragma once
#include "../../stdafx.h"
#include "SKShip.h"
#include "SKBullet.h"

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
	virtual bool LoadMap(std::string);
	virtual bool ExportMap(std::string);

	void SpawnShip(SKShip*);
	bool IsAvailable();
	void SetAvailable(bool);

	std::string GetMapDir();
	int GetRenderTileCount();
	int GetMaxRenderTileCount();

protected:
	friend class SKPlayerShip;

	const Rectangle m_tileSize = { 0,0,16,16 };
	const float m_tileScale = 4.f;
	int m_maxTileInView = 0;
	float m_scaleTileW;
	float m_scaleTileH;
	int m_renderTileCount;

	bool m_available;
	SKState* m_state;
	std::string m_mapdir;

	std::vector<SKShip*>  m_ships;
	std::vector<SKBullet*> m_bullets;
	std::unordered_map<double, SKTextureId> m_tiles;

	// items
	// explosions
	// etc...
};

