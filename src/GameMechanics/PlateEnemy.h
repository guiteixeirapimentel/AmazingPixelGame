#ifndef PLATEENEMY_H
#define PLATEENEMY_H
#include "Player.h"
#include "Enemy.h"
#include "../GFX/Colors.h"
#include "PlateAI.h"

class PlateEnemy : public Enemy
{
public:
    PlateEnemy(const Vector2DF &posdot1, const Vector2DF &posdot2, const Vector2DF &vel, float dragCoef = 0.93f, const Graphics::Color &color = GFXColor::LIGHTBLUE_COLOR);
    ~PlateEnemy();

    void Update(float dt = 1.0f / 60.0f) override;

    void Act(Player& refPlayer) override
    {
        cPAI->Act(refPlayer);
    }

    void Render(Graphics &gfx) const override;

    bool IsColliding(const Player &player) const override;

    inline virtual void AddAcceleration2(const Vector2DF &addedAccel) override
    {
        cAcceleration2 += addedAccel;
    }

    inline Vector2DF GetPosition() const override
    {
        return cPosition;
    }

    inline Vector2DF GetSecondPosition() const override
    {
        return cPosition2;
    }

private:
    static bool IsDotInLine(const Vector2DF& dot, const Vector2DF& line1, const Vector2DF& line2, float precision=0.1f);
private:
    Vector2DF cPosition2;
    Vector2DF cVelocity2;
    Vector2DF cAcceleration2;

    Graphics::Color cColor;
};

#endif