#include "PlayingState.h"
#include "GFX/Graphics.h"
#include "Controls/Keyboard.h"

PlayingState::PlayingState(Game& game, Graphics &gfx, Keyboard &keyboard)
    : GameState(game, gfx, keyboard),
      cPlayer({0.0f, 0.0f}, {}),
      cCam({0.0f, 0.0f}, cGraphics),
      cFont("assets/Consolas13x24.bmp", 13, 24),
      cScore(0),
      cStartTime(std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::system_clock::now().time_since_epoch())
                     .count())
{
    const int nEnemys = 10;

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

PlayingState::~PlayingState()
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

void PlayingState::Update()
{
    cScore = std::chrono::duration_cast<std::chrono::milliseconds>(
                 std::chrono::system_clock::now().time_since_epoch())
                 .count() -
             cStartTime;

    for (Enemy *pEnemy : cEnemysPointer)
    {
        pEnemy->Act(cPlayer);

        pEnemy->Update();

        if (pEnemy->IsColliding(cPlayer))
        {
            // cPlayer.ResetPlayer({0.0f, 0.0f});
            cStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                             std::chrono::system_clock::now().time_since_epoch())
                             .count();
        }
    }

    cPlayer.Update();

    cCam.SetPosition(cPlayer.GetPosition());

    cMapBackground.Update(cPlayer, cCam);
}

void PlayingState::Render()
{
    cMapBackground.Render(cCam);

    cCam.Render(cPlayer);

    for (Enemy *pEnemy : cEnemysPointer)
    {
        cCam.Render(*pEnemy);
    }

    cFont.DrawString({0, 0}, "Score: " + std::to_string(cScore), {255, 255, 255, 255}, cGraphics);
}

void PlayingState::Input()
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
