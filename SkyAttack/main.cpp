#include "stdafx.h"
#include "src/SKGameCore.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ char* pCmdLine, _In_ int nCmdShow)
{
    SKGameCore* game = new SKGameCore();
    if (!game)
    {
        return EXIT_FAILURE;
    }
    return game->Start(__argc,__argv);
}


