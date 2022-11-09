#include "SKInputManager.h"

SKInputManager::SKInputManager()
{
}

SKInputManager::~SKInputManager()
{
}

char SKInputManager::GetKeyAzerty()
{
    return this->ConvertQwerty(GetKeyPressed());
}

char SKInputManager::ConvertQwerty(int key)
{
    for (const std::pair<int, char>& p : this->m_azerty)
    {
        if (p.first == key)
        {
            return p.second;
        }
    }

    return key;
}
