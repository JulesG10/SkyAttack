#include "SKLobby.h"

SKLobby::SKLobby(SKState* state) : m_state(state)
{
    this->m_active = false;

    this->m_map = SK_NEW SKMap(this->m_state);
    this->m_map->LoadMap("");
    
    this->m_errorMsg = SK_NEW SKLabel("Something went wrong during the lobby loading\nSearching for a game...",
        { this->m_state->m_renderSize.x / 2.f, this->m_state->m_renderSize.y / 2.f - 50.f },
        20, WHITE);

    this->m_quit = SK_NEW SKButton(this->m_state, "Quit Lobby",
        SKGui::CenterObject({
            0,
            50,
            200,
            40
            }, this->m_state->m_renderSize, { 1, 1 }), WHITE, BLANK);

    this->m_rotateAnimation = 0;
    this->m_shipAnimation = SKTextureId::NID_LAST_SHIP;
    this->m_shipSrc = { 0 };
    this->m_shipDst = { 0 };

    this->m_player = SK_NEW SKPlayerShip(this->m_state, this->m_map);
}

SKLobby::~SKLobby()
{
    delete this->m_quit;
    delete this->m_map;
    delete this->m_player;
    delete this->m_errorMsg;
}

void SKLobby::NewConnection()
{
    this->m_active = true;

    //TODO: load map from lobby server
    if (this->m_map->LoadMap(this->m_map->GetMapDir() + "\\lobby.sk"))
    {
        this->m_map->SetAvailable(true);
    }
    else {
        this->m_map->SetAvailable(false);
    }
}

void SKLobby::UpdateFrame()
{
    /*
    wait for (game creation)/(party found) ...
    */

    if (!this->m_map->IsAvailable())
    {
        if (this->m_shipAnimation == SKTextureId::NID_LAST_SHIP)
        {
            this->m_shipAnimation = SKTextureId::SHIP_12;

            this->m_shipSrc = {
                0,0,
                (float)this->m_state->m_textures[this->m_shipAnimation].width,  (float)this->m_state->m_textures[this->m_shipAnimation].height
            };

            float shipScale = 2.f;
            this->m_shipDst = {
                 (this->m_state->m_renderSize.x - (this->m_state->m_textures[this->m_shipAnimation].width * shipScale)) / 2.f,
                 200,
                 (float)this->m_state->m_textures[this->m_shipAnimation].width * shipScale, (float)this->m_state->m_textures[this->m_shipAnimation].height * shipScale
            };


            this->m_shipDst.x += this->m_shipDst.width / 2.f;
            this->m_shipDst.y += this->m_shipDst.height / 2.f;
        }
        
        DrawCircle(
            this->m_shipDst.x,
            this->m_shipDst.y,
            (this->m_shipDst.width * 1.5)/2.f,
            { 100, 100, 100, 100 });

        DrawTexturePro(
            this->m_state->m_textures[this->m_shipAnimation],
            this->m_shipSrc,
            this->m_shipDst,
            { this->m_shipDst.width / 2.f, this->m_shipDst.height / 2.f },
            this->m_rotateAnimation,
            WHITE
        );

        
        this->m_rotateAnimation += GetFrameTime() * 80.f;
        if (this->m_rotateAnimation >= 360)
        {
            this->m_rotateAnimation = 0;
            int nextTex = (int)(this->m_shipAnimation);
            nextTex++;
            if (nextTex > (int)SKTextureId::SHIP_1)
            {
                nextTex = (int)SKTextureId::SHIP_12;
            }
            this->m_shipAnimation = (SKTextureId)nextTex;
        }
        
        this->m_errorMsg->UpdateFrame();
        if (this->m_quit->UpdateFrame())
        {
            this->m_active = false;
        }


        return;
    }

    BeginMode2D(this->m_player->GetCamera());
    this->m_map->UpdateFrame(this->m_player->GetView());
    EndMode2D();

    this->m_player->UpdateFrame();

    std::stringstream info;
    info << "Tiles: " << this->m_map->GetRenderTileCount() << "/" << this->m_map->GetMaxRenderTileCount() << std::endl;
    DrawText(info.str().c_str(), 0, 20, 20, BLACK);
}


bool SKLobby::InLobby()
{
    return this->m_active;
}
