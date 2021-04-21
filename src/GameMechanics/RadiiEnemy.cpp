#include "RadiiEnemy.h"
#include "Player.h"
#include "RadiiAI.h"

RadiiEnemy::RadiiEnemy(const Vector2DF &pos, const Vector2DF &vel, float minRadius, float maxRadius, float period, float dragCoef, const Graphics::Color &color)
    : Enemy(pos, vel, dragCoef),
      cMaxRadius(maxRadius),
      cMinRadius(minRadius),
      cPeriod(period),
      cRadius(cMinRadius),
      cGrowing(true),
      cRateOfChangeRadius((cMaxRadius - cMinRadius / cPeriod)),
      cColor(color)
{
    cPAI = new RadiiAI(*this);
}

RadiiEnemy::~RadiiEnemy()
{
    if(cPAI)
    {
        delete cPAI;
        cPAI = nullptr;
    }
}

void RadiiEnemy::Update(float dt)
{
    if (cGrowing)
    {
        cRadius += cRateOfChangeRadius * dt;
        if (cRadius >= cMaxRadius)
        {
            cGrowing = false;
        }
    }
    else
    {
        cRadius -= cRateOfChangeRadius * dt;

        if (cRadius <= cMinRadius)
        {
            cGrowing = true;
        }
    }

    // update velocity stuff
    Enemy::Update(dt);
}

void RadiiEnemy::Render(Graphics &gfx) const
{
    const Vector2DF finalPos = cPosition - cPosOffset/cDistanceDepth;

    gfx.DrawCircle(static_cast<int>(cRadius), finalPos.cX, finalPos.cY, cColor);
}

bool RadiiEnemy::IsColliding(const Player &player) const
{
    const Vector2DF playerPos = player.GetPosition();
    const float playerRadius = player.GetRadius();
    if((playerPos-cPosition).GetMagnitude() < (playerRadius+cRadius))
    {
        return true;
    }
    else
    {
        return false;
    }
}
