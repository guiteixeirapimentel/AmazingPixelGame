#ifndef BITMAPMAPPING_H
#define BITMAPMAPPING_H
#include "Bitmap.h"
#include <vector>

class BitmapMapping : protected Bitmap
{
public:
    BitmapMapping(const std::string &filename, const Graphics::Color& backgroundColor);

    virtual void Draw(
        const Vector2DI& pos, 
        const Graphics::Color& color, 
        Graphics &refGfx
    ) const;

    virtual void DrawCropped(
        const Vector2DI& pos, 
        const Vector2DI& initPoint,
        const Vector2DI& endPoint,
        const Graphics::Color& color,
        Graphics& refGfx
    ) const;
    
private:
    const Graphics::Color cBackgroundColor;
};

#endif