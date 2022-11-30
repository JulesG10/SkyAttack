#include "pch.h"
#include "SKEncryption.h"

SKEncryption* SKEncryption::Instance()
{
    static SKEncryption* skencrypt = new SKEncryption();
    return skencrypt;
}

std::string SKEncryption::DecryptString(std::string str)
{
    CkStringBuilder sb;
    CkBinData bd;
    bd.AppendEncoded(str.c_str(), "Base64");
    this->m_crypt.DecryptSb(bd, sb);
    return std::string(sb.getAsString());
}

std::string SKEncryption::EncryptString(std::string str)
{
    CkStringBuilder sb;
    CkBinData bd;
    sb.Append(str.c_str());
    this->m_crypt.EncryptSb(sb, bd);

    CkString out;
    bd.GetEncoded("Base64", out);
    return std::string(out);
}

bool SKEncryption::DecryptFileContent(std::string file)
{
   
    CkFileAccess fac;
    std::string newpath(file + ".tmp");

    if (!this->m_crypt.CkDecryptFile(file.c_str(), newpath.c_str()))
    {
        return false;
    }
    if (!fac.FileDelete(file.c_str()))
    {
        return false;
    }
    if (!fac.FileRename(newpath.c_str(), file.c_str()))
    {
        return false;
    }
    return true;
}

bool SKEncryption::EncryptFileContent(std::string file)
{
    CkFileAccess fac;
    std::string newpath(file + ".tmp");
    
    if (!this->m_crypt.CkEncryptFile(file.c_str(), newpath.c_str()))
    {
        return false;
    }
    if (!fac.FileDelete(file.c_str()))
    {
        return false;
    }
    if (!fac.FileRename(newpath.c_str(), file.c_str()))
    {
        return false;
    }
    return true;
}

void SKEncryption::SetKeys(const char* key, const char* iv)
{
    this->m_crypt.SetEncodedKey(key, "ascii");
    this->m_crypt.SetEncodedIV(iv, "ascii");
}

SKEncryption::SKEncryption()
{
    this->m_crypt.put_CryptAlgorithm("aes");
    this->m_crypt.put_CipherMode("cbc");
    this->m_crypt.put_KeyLength(128);

    this->m_crypt.SetEncodedKey("0000000000000000", "ascii");
    this->m_crypt.SetEncodedIV("0000000000000000", "ascii");
}

SKEncryption::~SKEncryption()
{
}