#ifndef CAMERA_H
#define CAMERA_H
#include "../../GFX/Graphics.h"

class Camera
{
public:
    Camera(const Vector2DF& startPosition, Graphics& gfx):cRefGFX(gfx),cPosition(startPosition){};
    ~Camera(){}

    void Render(Drawable& refDrawable) const
    {
        Vector2DF v = {float(cRefGFX.GetWidth()), float(cRefGFX.GetHeight())}; 
        refDrawable.SetPosOffset(cPosition - v/2);
        refDrawable.Render(cRefGFX);
    }

    void SetPosition(const Vector2DF& pos)
    {
        cPosition = pos;
    }

    Vector2DF GetPosition() const
    {
        return cPosition;
    }

private:
    Graphics& cRefGFX;
    Vector2DF cPosition;
};

#endif