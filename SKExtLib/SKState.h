#pragma once
#include "pch.h"
#include "SKEnums.h"

extern class SKEXT_EXPORTS SKState {
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
