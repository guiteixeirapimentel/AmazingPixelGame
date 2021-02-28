#include "Game.h"

Game::Game(Keyboard &kbd)
    : cKeyboard(kbd),
      cGraphics(800, 600),
      cPlayer({cGraphics.GetWidth()/2.0f, cGraphics.GetHeight()/2.0f}, {})
{
}

Game::~Game()
{
}

void Game::Tick()
{
    Input();
    Update();

    cGraphics.Init();
    Render();
    cGraphics.Present();
}

void Game::Update()
{
    cPlayer.Update();
}

void Game::Render()
{   
   cPlayer.Render(cGraphics);
}

void Game::Input()
{
    Keyboard::KeyEvent ev;
    while ((ev = cKeyboard.PeekAndPopEvent()))
    {
        // do events
    }

    if (cKeyboard.IsKeyPressed(SDLK_w))
    {
        if(cKeyboard.IsKeyPressed(SDLK_a))
        {
            cPlayer.MoveTopLeft();
        }
        else if(cKeyboard.IsKeyPressed(SDLK_d))
        {
            cPlayer.MoveTopRight();
        }
        else{
            cPlayer.MoveTop();
        }        
    }
    else if (cKeyboard.IsKeyPressed(SDLK_s))
    {
        if(cKeyboard.IsKeyPressed(SDLK_a))
        {
            cPlayer.MoveBottomLeft();
        }
        else if(cKeyboard.IsKeyPressed(SDLK_d))
        {
            cPlayer.MoveBottomRight();
        }
        else{
            cPlayer.MoveDown();
        }        
    }
    else if (cKeyboard.IsKeyPressed(SDLK_a))
    {
        cPlayer.MoveLeft();
    }
    else if (cKeyboard.IsKeyPressed(SDLK_d))
    {
        cPlayer.MoveRight();
    }
}
