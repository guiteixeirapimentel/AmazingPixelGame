#include "Player.h"
#include <iostream>

Player::Player(const Vector2DF &posInicial, const Vector2DF &velInicial)
    : cPos(posInicial),
      cVel(velInicial),
      cAcel({0.0f, 0.0f})
{
}

Player::~Player()
{
}

void Player::Update(float dt)
{
    cVel *= 0.98f;

    if(cMoving)
    {   
        const float dirMoving = cDirMovingDegrees * float(M_PI) / 180.0f;

        cAcel += Vector2DF(cosf(dirMoving), sinf(dirMoving)) * cWalkingAccel;
        cMoving = false;
        cDirMovingDegrees = 0;
    }

    cVel += cAcel * dt;
    cPos += cVel * dt;
    cAcel = {};
}

void Player::Render(Graphics &gfx) const
{
    gfx.DrawCircle(cRadius, int(cPos.cX), int(cPos.cY), {128, 180, 96, 255});
}

void Player::MoveTop()
{
    cDirMovingDegrees = -90;
    cMoving = true;
}
void Player::MoveLeft()
{
    cDirMovingDegrees = 180;
    cMoving = true;
}
void Player::MoveRight()
{
    cDirMovingDegrees = 0;
    cMoving = true;
}
void Player::MoveDown()
{
    cDirMovingDegrees = 90;
    cMoving = true;
}

void Player::MoveTopLeft()
{
    cDirMovingDegrees = -90 - 45;
    cMoving = true;
}
void Player::MoveTopRight()
{
    cDirMovingDegrees = -90 + 45;
    cMoving = true;
}
void Player::MoveBottomLeft()
{
    cDirMovingDegrees = 90 + 45;
    cMoving = true;
}
void Player::MoveBottomRight()
{
    cDirMovingDegrees = 90-45;
    cMoving = true;
}

void Player::ApplyAcceleration(const Vector2DF& accel)
{
    cAcel += accel;
}
