#include "GameState.h"

GameState::GameState(Game& game, Graphics& gfx, Keyboard& keyboard)
    :
    cGame(game),
    cGraphics(gfx),
    cKeyboard(keyboard)
{}