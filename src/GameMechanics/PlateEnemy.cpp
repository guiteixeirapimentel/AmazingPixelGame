#include "PlateEnemy.h"

PlateEnemy::PlateEnemy(const Vector2DF &posdot1, const Vector2DF &posdot2, const Vector2DF &vel, float dragCoef, const Graphics::Color &color)
    : Enemy(posdot1, vel, dragCoef),
      cPosition2(posdot2),
      cVelocity2(vel),
      cAcceleration2({0.0f, 0.0f}),
      cColor(color)
{
    cPAI = new PlateAI(*this);
}
PlateEnemy::~PlateEnemy()
{
    if(cPAI)
    {
        delete cPAI;
        cPAI = nullptr;
    }
}

void PlateEnemy::Update(float dt)
{ 
    cVelocity2 *= cDragCoeff;
    
    cVelocity2 += cAcceleration2 * dt;
    cPosition2 += cVelocity2 * dt;

    cAcceleration2 = {0.0f, 0.0f};

    Enemy::Update(dt);
}

void PlateEnemy::Render(Graphics &gfx) const
{
    gfx.DrawLine(cPosition.cX, cPosition.cY, cPosition2.cX, cPosition2.cY, cColor);
}

bool PlateEnemy::IsColliding(const Player &player) const
{
    const Vector2DF playerPos = player.GetPosition();

    const float distSqrd1Player = (playerPos - cPosition).GetMagnitudeSquared();
    const float distSqrd2Player = (playerPos - cPosition2).GetMagnitudeSquared();

    const float playerRadiusSqrd = player.GetRadius() * player.GetRadius();

    // verify if one of the points are inside the circle
    if (distSqrd1Player < playerRadiusSqrd || distSqrd2Player < playerRadiusSqrd)
    {
        return true;
    }

    const Vector2DF lineVec = cPosition2 - cPosition;
    const float lenSqrdOfEnemyLine = lineVec.GetMagnitudeSquared();

    // remember about projections. In reality you are projecting the position of the player to the line.
    const Vector2DF toDot1 = playerPos - cPosition;

    const float slope = toDot1.DotProduct(lineVec) / lenSqrdOfEnemyLine;

    const Vector2DF closestPoint = cPosition + (lineVec * slope);

    // verify if the closest point is between the two dots (not outside of it)
    if (!IsDotInLine(closestPoint, cPosition, cPosition2))
    {
        return false;
    }

    const float distSqrdToClosestPoint = (closestPoint - playerPos).GetMagnitudeSquared();

    // verify if the distance between the player and the closest point is less then the radius (of the player)
    if(distSqrdToClosestPoint <= playerRadiusSqrd)
    {
        return true;
    }

    return false;
}

bool PlateEnemy::IsDotInLine(const Vector2DF &dot, const Vector2DF &line1, const Vector2DF &line2, float precision)
{
    const float lenLine = (line2 - line1).GetMagnitude();

    const float lenDistDot = (dot - line1).GetMagnitude() + (dot - line2).GetMagnitude();

    if (lenLine - lenDistDot < 0.1 && lenLine - lenDistDot > -0.1)
    {
        return true;
    }

    return false;
}