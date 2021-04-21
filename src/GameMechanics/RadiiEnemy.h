#ifndef RADIIENEMY_H
#define RADIIENEMY_H
#include "Enemy.h"
#include "../GFX/Colors.h"

class RadiiEnemy : public Enemy
{
public:
    RadiiEnemy(const Vector2DF& pos, const Vector2DF& vel, float minRadius, float maxRadius, float period = 5.0f, float dragCoef = 0.93f, const Graphics::Color& color = GFXColor::LIGHTBLUE_COLOR);
    ~RadiiEnemy();

    void Update(float dt = 1.0f/60.0f) override;
    void Act(Player& refPlayer) override
    {
        cPAI->Act(refPlayer);
    }
    void Render(Graphics& gfx) const override;

    bool IsColliding(const Player& player) const override;

private:
    const float cMaxRadius;
    const float cMinRadius;
    const float cPeriod;
    const float cRateOfChangeRadius;

    Graphics::Color cColor;

    bool cGrowing;
    float cRadius;
};

#endif