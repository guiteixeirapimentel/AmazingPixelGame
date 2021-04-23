#include "Font.h"

Font::Font(const std::string& fontFilename, int fontWidth, int fontHeight)
:
cFontBitmap(fontFilename, {255, 255, 255, 255}),
cWidth(fontWidth),
cHeight(fontHeight)
{}

Font::~Font()
{}

void Font::DrawString(const Vector2DI& pos, const std::string& text, const Graphics::Color& color, Graphics& refGfx) const
{
    Vector2DI charPos = pos;
    for(size_t i = 0; i < text.length(); i++)
    {
        DrawCharacter(charPos, text[i], color, refGfx);
        charPos += Vector2DI(cWidth, 0);
    }
}

void Font::DrawCharacter(const Vector2DI& pos, char c, const Graphics::Color& color, Graphics& refGfx) const
{
    // 32 por linha (32 colunas)
    // 3 linhas

    const int index = c - ' '; 
    
    const int i = index / 32;
    const int j = index % 32;

    const Vector2DI initPoint = { j*cWidth, i*cHeight };
    const Vector2DI endPoint = initPoint + Vector2DI(cWidth, cHeight);
    cFontBitmap.DrawCropped(pos, initPoint, endPoint, color, refGfx);
}