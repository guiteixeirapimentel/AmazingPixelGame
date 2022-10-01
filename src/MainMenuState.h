#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "GameState.h"

class MainMenuState : public GameState
{
public:
    MainMenuState(Game& game, Graphics& gfx, Keyboard& keyboard);
    ~MainMenuState();

    virtual void Update();
    virtual void Render();
    virtual void Input();
private:
    int tmp= 0;
};

#endif