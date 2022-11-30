#include "SKGameCore.h"

SKGameCore::SKGameCore() : m_state()
{
}

SKGameCore::~SKGameCore()
{
}

int SKGameCore::Start(int argc, char** argv)

{
    if (!this->Init(argc, argv))
    {
        return EXIT_FAILURE;
    }

    // TODO: init game state
    // create map

    this->m_state = new SKState();
    SKEncryption::Instance()->SetKeys("SKYATTACK_GAME_0", "SKYATTACK_GAME_0");
    


    this->m_renderTexture = LoadRenderTexture(this->m_state->m_renderSize.x, this->m_state->m_renderSize.y);
    this->m_menu = new SKMenu(this->m_state);

    pthread_t resThread;
    pthread_create(&resThread, NULL, &LoadResources, this);

    while (!WindowShouldClose())
    {
        this->UploadTextures();

        BeginTextureMode(m_renderTexture);
        ClearBackground(BLANK);
        this->m_menu->UpdateFrame();
        EndTextureMode();

        BeginDrawing();
        DrawTexturePro(this->m_renderTexture.texture, { 0, 0, this->m_state->m_renderSize.x, -this->m_state->m_renderSize.y }, { 0,0, (float)GetRenderWidth(), (float)GetRenderHeight() }, { 0,0 }, 0, WHITE);

#ifdef _DEBUG
        DrawFPS(0, 0);
#endif // _DEBUG

        EndDrawing();
    }

    this->UnLoadResources();
    delete this->m_menu;
    delete this->m_state;
    CloseWindow();
    return EXIT_SUCCESS;
}

bool SKGameCore::Init(int argc, char** argv)
{
#ifdef _DEBUG
    if (AllocConsole())
    {
        FILE* fDummy;
        freopen_s(&fDummy, "CONOUT$", "w", stdout);
        freopen_s(&fDummy, "CONOUT$", "w", stderr);
        freopen_s(&fDummy, "CONIN$", "r", stdin);
        std::cout.clear();
        std::clog.clear();
        std::cerr.clear();
        std::cin.clear();

        SetTraceLogLevel(LOG_WARNING | LOG_ERROR | LOG_FATAL);
    }
#else
    SetTraceLogLevel(LOG_NONE);
#endif

    // TODO: parser args + load settings
    // if args --fullscreen or settings == fullscreen

    bool fullscreen = false;
    bool vsync = false;
    SYSTEM_POWER_STATUS status;
    bool charging = GetSystemPowerStatus(&status) && status.ACLineStatus == AC_LINE_ONLINE;
    int width = 1920;
    int height = 1080;

    unsigned int flags = 0;
    if (fullscreen)
    {
        flags |= FLAG_FULLSCREEN_MODE;
    }
    if (vsync)
    {
        flags |= FLAG_VSYNC_HINT;
    }
    if (charging)
    {
        flags |= FLAG_MSAA_4X_HINT;
    }

    SetConfigFlags(flags);
    InitWindow(width, height, "Sky Attack");
    SetTargetFPS(0);
    // TODO: windows icon + resource icon

    return true;
}

void SKGameCore::UploadTextures()
{
    if (!this->m_state->m_cpuloading && this->m_state->m_loading)
    {
        for (size_t i = SK_TEXTURE_START; i <= SK_TEXTURE_END; i++)
        {
            SKTextureId id = (SKTextureId)i;
            if (this->m_state->m_images[id].data)
            {
                this->m_state->m_textures[id] = LoadTextureFromImage(this->m_state->m_images[id]);
                // SetTextureWrap(this->m_state->m_textures[id], TEXTURE_WRAP_CLAMP);

                UnloadImage(this->m_state->m_images[id]);
                this->m_state->m_images.erase(id);
            }
        }

        if (this->m_state->m_images.size() != 0)
        {
            this->m_state->m_images.clear();
        }
        this->m_state->m_loading = false;
    }
}

void SKGameCore::UnLoadResources()
{
    UnloadRenderTexture(this->m_renderTexture);
    for (size_t i = SK_TEXTURE_START; i <= SK_TEXTURE_END; i++)
    {
        SKTextureId id = (SKTextureId)i;
        if (SKValidTextureId(id))
        {
            UnloadTexture(this->m_state->m_textures[id]);
        }
    }

}

void* LoadResources(void* data)
{
    SKGameCore* self = static_cast<SKGameCore*>(data);
    if (self)
    {
        self->m_state->m_loading = true;
        self->m_state->m_cpuloading = true;
        
#ifdef _DEBUG
        std::string appdir(GetWorkingDirectory());
        appdir += "\\";
#else
        std::string appdir(GetApplicationDirectory());
#endif // _DEBUG
        
        for (size_t i = SK_TEXTURE_START; i <= SK_TEXTURE_END; i++)
        {
            if (i != (int)SKTextureId::NID_LAST_SHIP)
            {
                SKTextureId id = (SKTextureId)i;
                SKTextureId textureId = id;

                std::string shortpath = "assets\\textures\\ships\\";
                std::string prefix = "ship_";

                if (i > (int)SKTextureId::NID_LAST_SHIP && i < (int)SKTextureId::NID_LAST_TILE)
                {
                    textureId = (SKTextureId)((int)textureId - (int)(SKTextureId::NID_LAST_SHIP + 1));
                    prefix = "tile_";
                    shortpath = "assets\\textures\\tiles\\";
                }
                else if (i > (int)SKTextureId::NID_LAST_TILE && i < (int)SKTextureId::NID_LAST_CLOUD)
                {
                    textureId = (SKTextureId)((int)textureId - (int)(SKTextureId::NID_LAST_TILE + 1));
                    prefix = "cloud_";
                    shortpath = "assets\\textures\\clouds\\";
                }

                if (SKValidTextureId(textureId))
                {
                    std::string path(appdir + shortpath + SKTexureIdToString(prefix, textureId) + ".png");
                    self->m_state->m_images[id] = LoadImage(path.c_str());
                }
            }
        }

#ifdef _DEBUG
        std::string modsdir = std::string(GetApplicationDirectory()) + "mods\\";
#else
        std::string modsdir = appdir + "mods\\";
#endif 

        if (GetFileAttributesA(modsdir.c_str()) == INVALID_FILE_ATTRIBUTES)
        {
            CreateDirectoryA(modsdir.c_str(), NULL);
        }

        WIN32_FIND_DATAA ffd;
        HANDLE hFind = INVALID_HANDLE_VALUE;
        ZeroMemory(&ffd, sizeof(WIN32_FIND_DATAA));

        hFind = FindFirstFileA((modsdir+"*").c_str(), &ffd);
        if (hFind != INVALID_HANDLE_VALUE)
        {
            while (FindNextFileA(hFind, &ffd) != 0)
            {
                if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                {
                    std::string fname(ffd.cFileName);
                    size_t ld = fname.find_last_of(".");
                    if (ld != std::string::npos && fname.substr(ld) == ".dll")
                    {
                        self->m_state->m_mods.push_back(modsdir+fname);
                    }
                }
            }
        }
        FindClose(hFind);

        // TODO: load sounds

        self->m_state->m_cpuloading = false;
        
        return EXIT_SUCCESS;
    }
    return (void*)EXIT_FAILURE;
}
