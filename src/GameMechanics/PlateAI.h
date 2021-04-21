#ifndef PLATEAI_H
#define PLATEAI_H
#include "EnemyAI.h"

class PlateAI : public EnemyAI
{
public:
    PlateAI(class PlateEnemy& refEnemy);
    ~PlateAI();

    void Act(Player& refPlayer) override;
    
};

#endif