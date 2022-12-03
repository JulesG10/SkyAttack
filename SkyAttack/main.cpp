#include "stdafx.h"
#include "src/SKGameCore.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ char* pCmdLine, _In_ int nCmdShow)
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
#endif
    
    SKGameCore* game = SK_NEW SKGameCore();
    if (!game)
    {
        return EXIT_FAILURE;
    }
    int exitCode = game->Start(__argc, __argv);
    delete game;

#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif

    return exitCode;
}


