#include "SKEncryption.h"

SKEncryption* SKEncryption::Instance()
{
    static SKEncryption* skencrypt = new SKEncryption();
    return skencrypt;
}

std::string SKEncryption::DecryptString(std::string str)
{
    uint8_t* buffer = (uint8_t*)str.c_str();
    AES_ECB_encrypt(&this->m_context, buffer);
    return std::string((char*)buffer);
}

std::string SKEncryption::EncryptString(std::string str)
{
    uint8_t* buffer = (uint8_t*)str.c_str();
    AES_ECB_decrypt(&this->m_context, buffer);
    return std::string((char*)buffer);
}

std::string SKEncryption::DecryptFileContent(std::string file)
{
    std::ifstream ifs(file);
    if (!ifs.good())
    {
        return std::string();
    }
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    ifs.close();
    return this->DecryptString(content);
}

bool SKEncryption::EncryptFileContent(std::string file, std::string content)
{
    std::ofstream  ofs(file);
    if (!ofs.good())
    {
        return false;
    }
    ofs << this->EncryptString(content);
    ofs.close();
    return true;
}

SKEncryption::SKEncryption()
{
    AES_init_ctx(&this->m_context, this->m_key);
}

SKEncryption::~SKEncryption()
{
}