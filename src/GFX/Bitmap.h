#ifndef BITMAP_H
#define BITMAP_H

#include "Colors.h"
#include "../Physics/Vector2D.h"

class Bitmap
{
public:
   Bitmap(const std::string &filename);
   ~Bitmap();

   virtual void Draw(const Vector2DI& pos, Graphics &refGfx) const;
   virtual void DrawCropped(
      const Vector2DI& pos, 
      const Vector2DI& initPoint,
      const Vector2DI& endPoint, 
      Graphics& refGfx
   ) const;

protected:
   int cWidth;
   int cHeight;

   Graphics::Color* cPPixelData;
private:
   struct BitmapFileHeader
   {
      unsigned int fileSize;
      unsigned short reserved1, reserved2;
      unsigned int offsetToPixelData;
   };

   struct BitmapInfoHeader
   {
      unsigned int headerSize;
      int width, height;
      unsigned short planes;
      unsigned short bits;
      unsigned int compression;
      unsigned int imageSize;
      int xResolution, yResolution;
      unsigned int nColors;
      unsigned int importantColours;
   };

   struct Pixel24
   {
      unsigned char blue;
      unsigned char green;
      unsigned char red;
   };
};

#endif