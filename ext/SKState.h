#pragma once

#include<iostream>
#include<vector>
#include<unordered_map>

#include<raylib.h>

#include "SKEnums.h"


class SKState {
public:
	SKState();
	~SKState();

	Vector2 GetMouse();

	const Vector2 m_renderSize = { 1366, 768 };

	bool m_cpuloading;
	bool m_loading;
	std::unordered_map<SKTextureId, Image> m_images = {};
	std::unordered_map<SKTextureId, Texture2D> m_textures = {};

	std::unordered_map<SKGameKeys, int> m_gamekeys = {};
	std::vector<std::string> m_mods = {};
};
