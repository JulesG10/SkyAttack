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

    this->m_renderTexture = LoadRenderTexture(this->m_state->renderSize.x, this->m_state->renderSize.y);
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
        DrawTexturePro(this->m_renderTexture.texture, { 0, 0, this->m_state->renderSize.x, -this->m_state->renderSize.y }, { 0,0, (float)GetRenderWidth(), (float)GetRenderHeight() }, { 0,0 }, 0, WHITE);

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
    if (!this->m_state->cpuloading && this->m_state->loading)
    {
        for (size_t i = SK_TEXTURE_START; i <= SK_TEXTURE_END; i++)
        {
            SKTextureId id = (SKTextureId)i;
            if (this->m_state->images[id].data)
            {
                this->m_state->textures[id] = LoadTextureFromImage(this->m_state->images[id]);
                UnloadImage(this->m_state->images[id]);
                this->m_state->images.erase(id);
            }
        }

        if (this->m_state->images.size() != 0)
        {
            this->m_state->images.clear();
        }
        this->m_state->loading = false;
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
            UnloadTexture(this->m_state->textures[id]);
        }
    }

}

void* LoadResources(void* data)
{
    SKGameCore* self = static_cast<SKGameCore*>(data);
    if (self)
    {
        self->m_state->loading = true;
        self->m_state->cpuloading = true;
        
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
                    self->m_state->images[id] = LoadImage(path.c_str());

                }
            }
        }


        // TODO: load sounds

        self->m_state->cpuloading = false;
        
        return EXIT_SUCCESS;
    }
    return (void*)EXIT_FAILURE;
}
