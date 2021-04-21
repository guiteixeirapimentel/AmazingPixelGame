#ifndef STAR_H
#define STAR_H
#include "../GFX/Drawable.h"
#include "../GFX/Colors.h"

class Star : public Drawable
{
public:
    Star(const Vector2DF& pos, float distanceDepth, const Graphics::Color& color = GFXColor::LIGHTRED_COLOR);
    Star(const Star& refStar);
    ~Star();

    void SetPos(const Vector2DF& pos, float distanceDepth);

    void Render(Graphics& refGfx) const override;

    Vector2DF GetPos() const {return cPosition;}

private:
    Vector2DF cPosition;
    Graphics::Color cColor;
};

#endif