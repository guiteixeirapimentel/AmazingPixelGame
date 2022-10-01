#ifndef PLAYING_STATE_H
#define PLAYING_STATE_H

#include <vector>

#include "GameState.h"

#include "GameMechanics/Player.h"
#include "GameMechanics/Enemy.h"
#include "GameMechanics/RadiiEnemy.h"
#include "GameMechanics/PlateEnemy.h"

#include "GameMechanics/Camera/Camera.h"
#include "GameMechanics/MapBackground.h"

#include "GFX/Font.h"

class PlayingState : public GameState
{
public:
    PlayingState(Game& game, Graphics &gfx, Keyboard &keyboard);
    ~PlayingState();

    void Update();
    void Render();
    void Input();

private:
    Camera cCam;

    MapBackground cMapBackground;

    Player cPlayer;
    std::vector<Enemy *> cEnemysPointer;

    Font cFont;

    int cScore;

    int cStartTime;
};

#endif