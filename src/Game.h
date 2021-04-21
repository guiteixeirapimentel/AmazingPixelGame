#ifndef GAME_H
#define GAME_H
#include "GFX/Graphics.h"
#include "Controls/Keyboard.h"

#include "GameMechanics/Player.h"
#include "GameMechanics/Enemy.h"
#include "GameMechanics/RadiiEnemy.h"
#include "GameMechanics/PlateEnemy.h"

#include "GameMechanics/Camera/Camera.h"

#include <vector>

class Game
{
public:
    Game(Keyboard &kbd);
    ~Game();

    void Tick();

private:
    void Update();
    void Render();
    void Input();

private:
    Graphics cGraphics;
    Keyboard& cKeyboard;
    Camera cCam;

    Player cPlayer;
    std::vector<Enemy*> cEnemysPointer;
};

#endif