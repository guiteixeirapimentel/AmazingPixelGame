#include "PlateAI.h"
#include "PlateEnemy.h"
#include "Player.h"

PlateAI::PlateAI(PlateEnemy& refEnemy)
:
EnemyAI(refEnemy)
{}

PlateAI::~PlateAI()
{}

void PlateAI::Act(Player& refPlayer)
{
    const Vector2DF cgEnemyPos = (cRefEnemy.GetPosition() + cRefEnemy.GetSecondPosition())/2;
    const Vector2DF toPlayerVec = (refPlayer.GetPosition()+refPlayer.GetVelocity()*0.5f - cgEnemyPos)/(refPlayer.GetPosition()+refPlayer.GetVelocity()*0.5f - cgEnemyPos).GetMagnitudeSquared();
        
    const Vector2DF toPlayerVec1 = (refPlayer.GetPosition() - cRefEnemy.GetPosition());
    const Vector2DF toPlayerVec2 = (refPlayer.GetPosition() - cRefEnemy.GetSecondPosition());

    cRefEnemy.AddAcceleration(toPlayerVec1 * toPlayerVec1.DotProduct(toPlayerVec) * 30.0f);
    cRefEnemy.AddAcceleration2(toPlayerVec2 * toPlayerVec2.DotProduct(toPlayerVec) * 30.0f);

    const Vector2DF toDot2 = cRefEnemy.GetPosition() - cRefEnemy.GetSecondPosition();

    cRefEnemy.AddAcceleration(toDot2/(toDot2.GetMagnitudeSquared()) * 30000.0f);
    cRefEnemy.AddAcceleration2(-toDot2/(toDot2.GetMagnitudeSquared()) * 30000.0f);
}