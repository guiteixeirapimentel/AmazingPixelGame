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

        cRadiiEnemys.emplace_back(RadiiEnemy(pos, {0.0f, 0.0f}, minRadius, maxRadius));
    }
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
    for (RadiiEnemy& enemy : cRadiiEnemys)
    {
        enemy.AddAcceleration((cPlayer.GetPosition() - enemy.GetPosition()) * 30.0f);

        enemy.Update();

        if (enemy.IsColliding(cPlayer))
        {
            //std::cout << "COLIDINDO" << std::endl;
        }
    }

    cPlayer.Update();
}

void Game::Render()
{
    cPlayer.Render(cGraphics);
    for (RadiiEnemy& enemy : cRadiiEnemys)
    {
        enemy.Render(cGraphics);
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
