#pragma once

#include "SKMap.h"
#include "../gui/SKButton.h"

class SKMapEditor : public SKMap
{
public:
	SKMapEditor(SKState*);
	~SKMapEditor();

	void UpdateFrame(Rectangle rect = {0}) override;

	void SetAvailable(bool);
	bool HasQuit();

	void Clear();

	std::string GetMapDir();
private:
	bool DrawTileSelector(Vector2 mouse);

	SKTextureId m_selected;

	SKButton* m_save;
	std::string m_mapdir;

	Camera2D m_camera;
	Vector2 m_position;
	bool m_quit;
	int m_tilePerRow;
	int m_tileSelectorWidth;
	Rectangle m_view;
};

