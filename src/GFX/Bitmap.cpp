#include "Bitmap.h"
#include <stdio.h>
#include <assert.h>

Bitmap::Bitmap(const std::string& filename)
:
cWidth(0),
cHeight(0),
cPPixelData(nullptr)
{
	FILE* bmpFile = fopen( filename.c_str(),"rb" );
	
	char signature[ 2 ];
	fread( signature,sizeof( char ),2,bmpFile );
	assert(signature[ 0 ] == 'B' && signature[ 1 ] == 'M');

	BitmapFileHeader fileHeader;
	fread( &fileHeader,sizeof( fileHeader ),1,bmpFile );

	BitmapInfoHeader infoHeader;
	fread( &infoHeader,sizeof( infoHeader ),1,bmpFile );

	fseek( bmpFile,fileHeader.offsetToPixelData,SEEK_SET );

	int nPaddingBytesPerRow = (4 - ((infoHeader.width * 3) % 4)) % 4;
	cHeight = infoHeader.height;
	cWidth = infoHeader.width;
	cPPixelData = new Graphics::Color[cWidth*cHeight];

	for( int y = infoHeader.height - 1; y >= 0; y-- )
	{
		for( int x = 0; x < infoHeader.width; x++ )
		{
			Pixel24 pixel;
			fread( &pixel,sizeof( pixel ),1,bmpFile );
			cPPixelData[ x + y * infoHeader.width ] = {pixel.red,pixel.green,pixel.blue, 255};
		}
		fseek( bmpFile,nPaddingBytesPerRow,SEEK_CUR );
	}

	fclose( bmpFile );
}

Bitmap::~Bitmap()
{
	if(cPPixelData)
	{
		delete [] cPPixelData;

		cPPixelData = nullptr;
	}
}

void Bitmap::Draw(const Vector2DI& pos, Graphics& refGfx) const
{
	const int yStart = std::max<int>( -pos.cY, 0 );
	const int xStart = std::max<int>( -pos.cX, 0 );
	const int yEnd = std::min<int>( refGfx.GetHeight() - pos.cY,cHeight );
	const int xEnd = std::min<int>( refGfx.GetWidth() - pos.cX,cWidth );

	for(int y = yStart; y < yEnd; y++)
	{
		for(int x = xStart; x < xEnd; x++)
		{
			refGfx.PutPixel(x+pos.cX, y+pos.cY, cPPixelData[x + y*cWidth]);
		}
	}
}

void Bitmap::DrawCropped(
      const Vector2DI& pos, 
      const Vector2DI& initPoint,
      const Vector2DI& endPoint, 
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
			refGfx.PutPixel(x+pos.cX, y+pos.cY, cPPixelData[x+ initPoint.cX + (y+ initPoint.cY)*cWidth]);
		}
	}
}
