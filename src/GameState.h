#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <memory>

class Graphics;
class Keyboard;
class Game;

class GameState
{
public:
    GameState(Game& game, Graphics& gfx, Keyboard& keyboard);
    virtual ~GameState() = default;

    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Input() = 0;

protected:
    Game& cGame;
    Graphics& cGraphics;
    Keyboard& cKeyboard;

};
#endif