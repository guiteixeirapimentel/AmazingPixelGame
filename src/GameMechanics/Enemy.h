#ifndef ENEMY_H
#define ENEMY_H
#include "../GFX/Graphics.h"
#include "../Physics/Vector2D.h"

class Enemy
{
public:
    Enemy(const Vector2DF &pos, const Vector2DF &vel, float dragCoeff = 0.93f) : cPosition(pos), cVelocity(vel), cAcceleration({0.0f, 0.0f}), cDragCoeff(dragCoeff) {}
    ~Enemy() {}

    virtual void Update(float dt = 1.0f / 60.0f)
    {
        cVelocity *= cDragCoeff;
        cVelocity += cAcceleration * dt;
        cPosition += cVelocity * dt;

        cAcceleration = {0.0f, 0.0f};
    }
    virtual void Render(Graphics &gfx) const = 0;
    virtual bool IsColliding(const class Player &player) const { return false; }

    virtual void AddAcceleration(const Vector2DF& addedAccel){ cAcceleration += addedAccel; }

    inline Vector2DF GetPosition() const {return cPosition;}

protected:
    Vector2DF cPosition;
    Vector2DF cVelocity;
    Vector2DF cAcceleration;

    float cDragCoeff;
};

#endif