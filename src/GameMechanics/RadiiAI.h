#ifndef RADIIAI_H
#define RADIIAI_H
#include "EnemyAI.h"
#include "RadiiEnemy.h"

class RadiiAI : public EnemyAI
{
public:
    RadiiAI(RadiiEnemy& refEnemy)
    :
    EnemyAI(refEnemy)
    {};
    ~RadiiAI(){};

    void Act(Player& refPlayer) override
    {
        cRefEnemy.AddAcceleration((refPlayer.GetPosition() - cRefEnemy.GetPosition()) * 30.0f);
    }
    
};

#endif