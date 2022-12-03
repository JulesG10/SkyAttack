#include "pch.h"
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

char SKInputManager::ConvertQwerty(int key, bool* found)
{
    for (const std::pair<int, char>& p : this->m_azerty)
    {
        if (p.first == key)
        {
            found ? (*found = true) : NULL;
            return p.second;
        }
    }
    found ? (*found = false) : NULL;
    return key;
}

char SKInputManager::ConvertAzery(int key, bool* found)
{
    for (const std::pair<int, char>& p : this->m_azerty)
    {
        if ((int)p.second == key)
        {
            found ? (*found = true) : NULL;
            return (char)p.first;
        }
    }
    found ? (*found = false) : NULL;
    return key;
}
