#ifndef PLAYER_H
#define PLAYER_H
#include "../GFX/Graphics.h"
#include "../Physics/Vector2D.h"
#include "../GFX/Drawable.h"

class Player : public Drawable
{
public:
    Player(const Vector2DF& posInicial, const Vector2DF& velInicial);
    ~Player();

    void Update(float dt = Graphics::cMiliPerFrame/1000.0f);
    void Render(Graphics &gfx) const override;

    void ApplyAcceleration(const Vector2DF& accel);

    void MoveTop();
    void MoveLeft();
    void MoveRight();
    void MoveDown();

    void MoveTopLeft();
    void MoveTopRight();
    void MoveBottomLeft();
    void MoveBottomRight();

    inline Vector2DF GetPosition() const {return cPos;}
    inline float GetRadius() const {return static_cast<float>(cRadius);}
    inline Vector2DF GetVelocity() const {return cVel;}

    inline void ResetPlayer(const Vector2DF& newPos){
        cVel = {0.0f, 0.0f};
        cAcel = {0.0f, 0.0f};
        cPos = newPos;
    }

private:
    Vector2DF cPos;
    Vector2DF cVel;
    Vector2DF cAcel;

    const float cWalkingAccel = 3000.0f;
    const int cRadius = 5;
    bool cMoving = false;
    float cDirMovingDegrees = 0;
};

#endif