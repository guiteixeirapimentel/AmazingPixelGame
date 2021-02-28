#ifndef PLAYER_H
#define PLAYER_H
#include "../GFX/Graphics.h"
#include "../Physics/Vector2D.h"

class Player
{
public:
    Player(const Vector2DF& posInicial, const Vector2DF& velInicial);
    ~Player();

    void Update(float dt = Graphics::cMiliPerFrame/1000.0f);
    void Render(Graphics &gfx) const;

    void ApplyAcceleration(const Vector2DF& accel);

    void MoveTop();
    void MoveLeft();
    void MoveRight();
    void MoveDown();

    void MoveTopLeft();
    void MoveTopRight();
    void MoveBottomLeft();
    void MoveBottomRight();

private:
    Vector2DF cPos;
    Vector2DF cVel;
    Vector2DF cAcel;

    const float cWalkingAccel = 3000.0f;
    bool cMoving = false;
    float cDirMovingDegrees = 0;
};

#endif