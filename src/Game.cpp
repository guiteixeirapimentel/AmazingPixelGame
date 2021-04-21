#include "Game.h"
#include <iostream>

Game::Game(Keyboard &kbd)
    : cKeyboard(kbd),
      cGraphics(800, 600),
      cPlayer({cGraphics.GetWidth() / 2.0f, cGraphics.GetHeight() / 2.0f}, {})
{
    const int nEnemys = 1;

    for (int i = 0; i < nEnemys; i++)
    {
        const int minRadius = (rand() % 25);
        const int maxRadius = (rand() % 25) + 25;

        const Vector2DF pos = {static_cast<float>(rand() % 500) + 100 - maxRadius, static_cast<float>(rand() % 400) + 100 - maxRadius};

        auto pEnemy = new RadiiEnemy(pos, {0.0f, 0.0f}, minRadius, maxRadius);
        cEnemysPointer.push_back(pEnemy);
    }

    auto pEnemy = new PlateEnemy({120.0f, 120.0f}, {170.0f, 150.0f}, {0.0f, 0.0f});
    cEnemysPointer.push_back(pEnemy);
}

Game::~Game()
{
    for (size_t i = 0; i < cEnemysPointer.size(); i++)
    {
        auto pEnemy = cEnemysPointer[i];
        if (pEnemy)
        {
            delete pEnemy;
            pEnemy = nullptr;
        }
    }

    cEnemysPointer.clear();
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
    for (Enemy *pEnemy : cEnemysPointer)
    {
        pEnemy->Act(cPlayer);

        pEnemy->Update();

        if (pEnemy->IsColliding(cPlayer))
        {
            cPlayer.ResetPlayer({400.0f, 400.0f});
        }
    }

    cPlayer.Update();
}

void Game::Render()
{
    cPlayer.Render(cGraphics);

    for (Enemy *pEnemy : cEnemysPointer)
    {
        pEnemy->Render(cGraphics);
    }
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
        if (cKeyboard.IsKeyPressed(SDLK_a))
        {
            cPlayer.MoveTopLeft();
        }
        else if (cKeyboard.IsKeyPressed(SDLK_d))
        {
            cPlayer.MoveTopRight();
        }
        else
        {
            cPlayer.MoveTop();
        }
    }
    else if (cKeyboard.IsKeyPressed(SDLK_s))
    {
        if (cKeyboard.IsKeyPressed(SDLK_a))
        {
            cPlayer.MoveBottomLeft();
        }
        else if (cKeyboard.IsKeyPressed(SDLK_d))
        {
            cPlayer.MoveBottomRight();
        }
        else
        {
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
