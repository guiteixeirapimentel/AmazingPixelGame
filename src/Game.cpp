#include "Game.h"

#include "PlayingState.h"
#include "MainMenuState.h"

Game::Game(Keyboard &kbd)
    : cKeyboard(kbd),
      cGraphics(800, 600),
      cPtrGameState(std::make_unique<MainMenuState>(*this, cGraphics, cKeyboard))
{
}

Game::~Game()
{
}

void Game::SetNextGameState(std::unique_ptr<GameState>&& newGameState)
{
    cPtrGameState = std::move(newGameState);
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
    cPtrGameState->Update();
}

void Game::Render()
{
    cPtrGameState->Render();
}

void Game::Input()
{
    cPtrGameState->Input();
}
