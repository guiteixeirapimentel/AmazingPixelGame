#ifndef GAME_H
#define GAME_H
#include <memory>

#include "GFX/Graphics.h"
#include "Controls/Keyboard.h"

class GameState;

class Game
{
public:
    Game(Keyboard &kbd);
    ~Game();

    void Tick();

    void SetNextGameState(std::unique_ptr<GameState>&& newGameState);

private:
    void Update();
    void Render();
    void Input();

private:
    Graphics cGraphics;
    Keyboard& cKeyboard;

    std::unique_ptr<GameState> cPtrGameState;
};

#endif