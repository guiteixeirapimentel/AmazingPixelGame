#ifndef FONT_H
#define FONT_H
#include "BitmapMapping.h"
#include "../Physics/Vector2D.h"

class Font
{
public:
    Font(const std::string& fontFilename, int fontWidth, int fontHeight);
    ~Font();

    void DrawString(const Vector2DI& pos, const std::string& text, const Graphics::Color& color, Graphics& refGfx) const;
private:
    void DrawCharacter(const Vector2DI& pos, char c, const Graphics::Color& color, Graphics& refGfx) const;

private:
    BitmapMapping cFontBitmap;
    const int cWidth;
    const int cHeight;
};

#endif