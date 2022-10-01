#include "MainMenuState.h"
#include "Game.h"
#include "GFX/Graphics.h"
#include "GFX/Colors.h"

#include "PlayingState.h"

MainMenuState::MainMenuState(Game& game, Graphics& gfx, Keyboard& keyboard)
    :
    GameState(game, gfx, keyboard)
{}

MainMenuState::~MainMenuState()
{}

void MainMenuState::Update()
{
    tmp++;
    if(tmp > 60*10)
        cGame.SetNextGameState(std::make_unique<PlayingState>(cGame, cGraphics, cKeyboard));
}

void MainMenuState::Render()
{
    cGraphics.DrawFilledRectangle(100, 100, 300, 200, GFXColor::LIGHTGREEN_COLOR);
}

void MainMenuState::Input()
{

}
