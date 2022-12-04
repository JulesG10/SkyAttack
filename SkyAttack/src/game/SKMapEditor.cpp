#include "SKMapEditor.h"

SKMapEditor::SKMapEditor(SKState* state) : SKMap(state)
{
	this->m_available = true;
	this->m_camera = { 0 };
	this->m_camera.zoom = 1.f;

	this->m_tilePerRow = ceil((this->m_state->m_renderSize.x + (this->m_scaleTileW * 2)) / this->m_scaleTileW);
	this->m_maxTileInView = this->m_tilePerRow * ceil((this->m_state->m_renderSize.y + (this->m_scaleTileH * 2)) / this->m_scaleTileH);

	this->m_view = {
		this->m_camera.target.x,
		this->m_camera.target.y,
		this->m_state->m_renderSize.x,
		this->m_state->m_renderSize.y
	};

	this->m_selected = SKTextureId::NONE;
	this->m_tileSelectorWidth = 250;

	this->m_save = SK_NEW SKButton(this->m_state, "Save & Quit", { 25, this->m_state->m_renderSize.y - 50, 200, 40 }, WHITE, BLANK);
}

SKMapEditor::~SKMapEditor()
{
	delete this->m_save;
}

void SKMapEditor::UpdateFrame(Rectangle)
{
	DrawRectangle(0, 0, this->m_state->m_renderSize.x, this->m_state->m_renderSize.y, { 30,30,30,255 });
	float speed = 500.f;

	if (IsKeyDown(this->m_state->m_gamekeys[SKGameKeys::LEFT]))
	{
		this->m_position.x -= GetFrameTime() * speed;
	}
	else if (IsKeyDown(this->m_state->m_gamekeys[SKGameKeys::RIGHT]))
	{
		this->m_position.x += GetFrameTime() * speed;
	}
	
	if (IsKeyDown(this->m_state->m_gamekeys[SKGameKeys::SPEEDUP]))
	{
		this->m_position.y -= GetFrameTime() * speed;
	}
	else if (IsKeyDown(this->m_state->m_gamekeys[SKGameKeys::SLOWDOWN]))
	{
		this->m_position.y += GetFrameTime() * speed;
	}
	
	this->m_camera.target.x = ((int)(this->m_position.x / this->m_scaleTileW) * this->m_scaleTileW);
	this->m_camera.target.y = ((int)(this->m_position.y / this->m_scaleTileH) * this->m_scaleTileH);

	if (this->m_view.x != this->m_camera.target.x || this->m_view.y != this->m_camera.target.y)
	{
		this->m_view = {
			this->m_camera.target.x,
			this->m_camera.target.y,
			this->m_state->m_renderSize.x,
			this->m_state->m_renderSize.y
		};
	}

	Vector2 mouse = this->m_state->GetMouse();
	Vector2 tileMouse = {
		((int)(mouse.x / this->m_scaleTileW) * this->m_scaleTileW) + this->m_camera.target.x,
		((int)(mouse.y / this->m_scaleTileH) * this->m_scaleTileH) + this->m_camera.target.y
	};

	BeginMode2D(this->m_camera);
	SKMap::UpdateFrame(this->m_view);

	if (mouse.x > this->m_tileSelectorWidth)
	{
		
		DrawRectangleLinesEx({ tileMouse.x, tileMouse.y, this->m_scaleTileW, this->m_scaleTileH }, 2, WHITE);
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			Vec2 vec = { 0 };
			vec.position = tileMouse;

			if (this->m_selected == SKTextureId::NONE)
			{
				this->m_tiles.erase(vec.value);
			}
			else {
				this->m_tiles[vec.value] = this->m_selected;
			}
		}
	}

	EndMode2D();
	this->DrawTileSelector(mouse);

	std::stringstream sinfo;
	sinfo << "Tiles: " << this->m_tiles.size() << std::endl
		<< "Position: " << tileMouse.x <<";"<<tileMouse.y << std::endl;
	DrawText(sinfo.str().c_str(), 10, 10, 15, WHITE);

	if (this->m_save->UpdateFrame())
	{
		std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		if (!DirectoryExists(this->m_mapdir.c_str()))
		{
			if (!CreateDirectoryA(this->m_mapdir.c_str(), NULL))
			{
				return;
			}
		}

		if (this->m_loadpath.length() != 0)
		{
			this->ExportMap(this->m_loadpath);
		}
		else {
			this->ExportMap(this->m_mapdir + "\\map_" + std::to_string(ms.count()) + ".sk");
		}

		this->m_quit = true;
		this->m_available = false;
		this->m_loadpath = "";
	}
}

bool SKMapEditor::LoadMap(std::string path)
{
	this->m_loadpath = path;
	return SKMap::LoadMap(path);
}

bool SKMapEditor::DrawTileSelector(Vector2 mouse)
{
	
	float y = 2;
	float x = 0;
	float scale = 2.f;

	bool hover = false;

	DrawRectangle(0, 0, this->m_tileSelectorWidth, this->m_state->m_renderSize.y, { 80, 80, 80, 255 });

	for (size_t i = SK_MAP_TILE_START; i < (SK_MAP_TILE_END + 2); i++)
	{
		Rectangle item = { (x + 1) * this->m_tileSize.width * scale, y * this->m_tileSize.height * scale, this->m_tileSize.width * scale, this->m_tileSize.height * scale };
		
		Color color = WHITE;
		if (CheckCollisionPointRec(mouse, item))
		{
			color = BLACK;
			hover = true;

			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			{
				if (i < SK_MAP_TILE_END)
				{
					this->m_selected = (SKTextureId)i;
				}else if (i == SK_MAP_TILE_END) 
				{
					this->m_selected = SKTextureId::ICON_BORDERLIMIT;
				}
				else {
					this->m_selected = SKTextureId::NONE;
				}
			}
		}

		if (this->m_selected == i)
		{
			color = RED;
		}

		if (i < SK_MAP_TILE_END)
		{
			DrawTexturePro(this->m_state->m_textures[(SKTextureId)i],
				this->m_tileSize,
				item,
				{ 0,0 }, 0, WHITE);
		}
		else if (i == SK_MAP_TILE_END)
		{
			DrawTexturePro(this->m_state->m_textures[SKTextureId::ICON_BORDERLIMIT],
				this->m_tileSize,
				item,
				{ 0,0 }, 0, WHITE);
		}
		else {
			DrawTexturePro(this->m_state->m_textures[SKTextureId::ICON_DELETEITEM],
				this->m_tileSize,
				item,
				{ 0,0 }, 0, WHITE);
		}
		
		DrawRectangleLinesEx(item, 1, color);

		x++;
		if (x >= 5)
		{
			x = 0;
			y++;
		}
	}



	DrawLineEx({ (float)this->m_tileSelectorWidth, 0 }, { (float)this->m_tileSelectorWidth, this->m_state->m_renderSize.y }, 2, WHITE);



	return hover;
}



bool SKMapEditor::HasQuit()
{
	return this->m_quit;
}

void SKMapEditor::Clear()
{
	this->m_tiles.clear();
	this->m_position = { 0,0 };
	this->m_camera.target = { 0,0 };
	this->m_loadpath = "";

	this->m_view = {
		this->m_camera.target.x,
		this->m_camera.target.y,
		this->m_state->m_renderSize.x,
		this->m_state->m_renderSize.y
	};
}


