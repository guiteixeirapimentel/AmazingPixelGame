#include "Star.h"
#include "../GFX/Graphics.h"

Star::Star(const Vector2DF& pos, float distanceDepth, const Graphics::Color& color)
:
cPosition(pos),
cColor(color)
{
    cDistanceDepth = distanceDepth;
}

Star::Star(const Star& refStar)
{
    cPosition = refStar.cPosition;
    cDistanceDepth = refStar.cDistanceDepth;
}

Star::~Star()
{}

void Star::Render(Graphics& refGfx) const
{
    const Vector2DF finalPos = cPosition - cPosOffset/cDistanceDepth;
    refGfx.PutPixelSafe(finalPos.cX, finalPos.cY, cColor);
}

void Star::SetPos(const Vector2DF& pos, float distanceDepth)
{
    cPosition = pos;
    cDistanceDepth = distanceDepth;
}