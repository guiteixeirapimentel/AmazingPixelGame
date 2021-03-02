#include "RadiiEnemy.h"
#include "Player.h"

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
}

RadiiEnemy::~RadiiEnemy()
{
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
    gfx.DrawCircle(static_cast<int>(cRadius), cPosition.cX, cPosition.cY, cColor);
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
