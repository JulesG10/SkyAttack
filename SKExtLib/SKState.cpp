#include "pch.h"
#include "SKState.h"

SKState::SKState() : m_loading(true), m_cpuloading(true), m_textures({}), m_images({})
{
}

SKState::~SKState()
{
}

Vector2 SKState::GetMouse()
{
	Vector2 pos = {
		(this->m_renderSize.x * GetMousePosition().x) / GetRenderWidth(),
		(this->m_renderSize.y * GetMousePosition().y) / GetRenderHeight()
	};
	return pos;
}

bool SKState::SaveGameKeys(std::string path)
{
	std::ofstream file(path);
	if (!file.good())
	{
		return false;
	}

	for (size_t i = SKGameKeys::LEFT; i < (SKGameKeys::ULTIME+1); i++)
	{
		file << i << "|" << this->m_gamekeys[(SKGameKeys)i] << std::endl;
	}
	file.close();
	return true;
}

bool SKState::LoadGameKeys(std::string path)
{
	std::ifstream file(path);
	if (!file.good())
	{
		return false;
	}

	std::string line;
	while (std::getline(file, line))
	{
		if (line.length() >= 3)
		{
			std::string digit0;
			std::string digit1;
			bool split = false;

			for (size_t i = 0; i < line.length(); i++)
			{
				if (std::isdigit(line[i]))
				{
					split ? (digit0 += line[i]) : (digit1 += line[i]);
				}
				else if (line[i] == '|')
				{
					split = true;
				}
				else
				{
					file.close();
					return false;
				}
			}

			unsigned int key = std::atoi(digit0.c_str());
			unsigned int id = std::atoi(digit1.c_str());

			if (id < SKGameKeys::LEFT && id > SKGameKeys::ULTIME)
			{
				file.close();
				return false;
			}

			this->m_gamekeys[(SKGameKeys)id] = key;
		}
	}

	file.close();
	return true;
}
