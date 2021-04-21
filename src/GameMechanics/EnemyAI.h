#ifndef ENEMYAI_H
#define ENEMYAI_H

class EnemyAI
{
public:
    EnemyAI(class Enemy &refEnemy);
    ~EnemyAI();

    virtual void Act(class Player &refPlayer) = 0;

protected:
    Enemy &cRefEnemy;
};

#endif