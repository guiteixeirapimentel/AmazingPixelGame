#include "BitmapMapping.h"

BitmapMapping::BitmapMapping(const std::string &filename, const Graphics::Color& backgroundColor)
:
Bitmap(filename),
cBackgroundColor(backgroundColor)
{}

void BitmapMapping::Draw(const Vector2DI& pos, const Graphics::Color& color, Graphics& refGfx) const
{
	const int yStart = std::max<int>( -pos.cY, 0 );
	const int xStart = std::max<int>( -pos.cX, 0 );
	const int yEnd = std::min<int>( refGfx.GetHeight() - pos.cY,cHeight );
	const int xEnd = std::min<int>( refGfx.GetWidth() - pos.cX,cWidth );

	for(int y = yStart; y < yEnd; y++)
	{
		for(int x = xStart; x < xEnd; x++)
		{
            if(cPPixelData[x + y*cWidth] != cBackgroundColor)
            {
			    refGfx.PutPixel(x+pos.cX, y+pos.cY, color);
            }            
		}
	}
}

void BitmapMapping::DrawCropped(
      const Vector2DI& pos, 
      const Vector2DI& initPoint,
      const Vector2DI& endPoint,
      const Graphics::Color& color,
      Graphics& refGfx
   ) const
{
	const int widthCropped = endPoint.cX - initPoint.cX;
	const int heightCropped = endPoint.cY - initPoint.cY;

	const int yStart = std::max<int>( -pos.cY, 0 );
	const int xStart = std::max<int>( -pos.cX, 0 );
	const int yEnd = std::min<int>( refGfx.GetHeight() - pos.cY, heightCropped );
	const int xEnd = std::min<int>( refGfx.GetWidth() - pos.cX, widthCropped );

	for(int y = yStart; y < yEnd; y++)
	{
		for(int x = xStart; x < xEnd; x++)
		{
            if(cPPixelData[x+ initPoint.cX + (y+ initPoint.cY)*cWidth] != cBackgroundColor)
            {
			    refGfx.PutPixel(x+pos.cX, y+pos.cY, color);
            }
        }
	}
}