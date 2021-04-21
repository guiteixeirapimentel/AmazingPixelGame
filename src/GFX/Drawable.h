#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "../Physics/Vector2D.h"

class Drawable
{
public:
    Drawable() : cPosOffset({0.0f, 0.0f}){};
    ~Drawable(){};

    virtual void Render(class Graphics &gfx) const = 0;

    void SetPosOffset(const Vector2DF& newPosOffset)
    {
        cPosOffset = newPosOffset;
    }

protected:
    Vector2DF cPosOffset;
    float cDistanceDepth = 1.0f;
};

#endif