#include "Graphics.h"

#include <cstring>
#include <cassert>
#include <iostream>

#include <cmath>

Graphics::Graphics(uint32_t width, uint32_t height)
    : cWidth(width),
      cHeight(height),
      cPScreen(nullptr)
{
  SDL_Init(SDL_INIT_EVERYTHING);

  cPScreen = SDL_SetVideoMode(width, height, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
}

Graphics::~Graphics()
{
  SDL_Quit();
}

void Graphics::PutPixel(int x, int y, const Color &color)
{
  assert(x >= 0 && x < cWidth && y >= 0 && y < cHeight);

  reinterpret_cast<Uint32 *>(cPScreen->pixels)[y * cWidth + x] = SDL_MapRGBA(cPScreen->format, color.r, color.g, color.b, color.a);
}

void Graphics::PutPixelSafe(int x, int y, const Color &color)
{
  if(x < 0 || x>=cWidth || y <0 || y>= cHeight)
  {
    return;
  }

  reinterpret_cast<Uint32 *>(cPScreen->pixels)[y * cWidth + x] = SDL_MapRGBA(cPScreen->format, color.r, color.g, color.b, color.a);
}

void Graphics::Init()
{
  cStartRender = std::chrono::steady_clock::now();

  if (SDL_MUSTLOCK(cPScreen))
    SDL_LockSurface(cPScreen);

  memset(cPScreen->pixels, 0, sizeof(uint32_t) * cWidth * cHeight);
}

void Graphics::Present(bool vsync)
{
  cEndRender = std::chrono::steady_clock::now();
  std::chrono::duration<double> diff = cEndRender - cStartRender;

  const int renderTime = static_cast<int>(diff.count() * 1000);

  if (vsync && renderTime < cMiliPerFrame)
  {
    //std::cout << renderTime << std::endl;
    SDL_Delay(cMiliPerFrame - renderTime);
  }

  if (SDL_MUSTLOCK(cPScreen))
    SDL_UnlockSurface(cPScreen);

  SDL_Flip(cPScreen);
}

void Graphics::DrawLine(int x1, int y1, int x2, int y2, const Color &color)
{
  // casos triviais
  if (x1 == x2)
  {
    if (y1 > y2)
    {
      int tmp = y1;
      y1 = y2;
      y2 = tmp;
    }

    for (int j = y1; j <= y2; j++)
    {
      PutPixelSafe(x1, j, color);
    }

    return;
  }
  else if (y1 == y2)
  {
    if (x1 > x2)
    {
      int tmp = x1;
      x1 = x2;
      x2 = tmp;
    }

    for (int i = x1; i <= x2; i++)
    {
      PutPixelSafe(i, y2, color);
    }

    return;
  }

  const float dydx = static_cast<float>(y2 - y1) / (x2 - x1);
  const float dxdy = static_cast<float>(x2 - x1) / (y2 - y1);

  // se dydx for menor, desenha linha considerando funcao de x
  if (dydx < dxdy)
  {
    const float b = y1 - dydx * x1;

    if (x1 > x2)
    {
      int tmp = x1;
      x1 = x2;
      x2 = tmp;
    }

    for (int i = x1; i < x2; i++)
    {
      const int y = dydx * i + b;
      PutPixelSafe(i, y, color);
    }
  }
  else // se dxdy for menor, desenha linha considerando funcao de y
  {
    const float b = y1 - dydx * x1;

    if (y1 > y2)
    {
      int tmp = y1;
      y1 = y2;
      y2 = tmp;
    }

    for (int j = y1; j < y2; j++)
    {
      const int x = (j - b) / dydx;
      PutPixelSafe(x, j, color);
    }
  }
}

void Graphics::DrawRectangle(int xMin, int yMin, int xMax, int yMax, const Color &color)
{
  DrawLine(xMin, yMin, xMin, yMax, color);
  DrawLine(xMin, yMax, xMax, yMax, color);
  DrawLine(xMax, yMax, xMax, yMin, color);
  DrawLine(xMax, yMin, xMin, yMin, color);
}

void Graphics::DrawFilledRectangle(int xMin, int yMin, int xMax, int yMax, const Color &color)
{
  for (int j = yMin; j < yMax; j++)
  {
    for (int i = xMin; i < xMax; i++)
    {
      PutPixelSafe(i, j, color);
    }
  }
}

void Graphics::DrawCircle(int radius, int xCenter, int yCenter, const Color &color)
{
  for (int x = -radius + xCenter; x <= radius + xCenter; x++)
  {
    const float y1 = yCenter + sqrt(radius * radius - (x - xCenter) * (x - xCenter));
    const float y2 = yCenter - sqrt(radius * radius - (x - xCenter) * (x - xCenter));

    PutPixelSafe(x, y1, color);
    PutPixelSafe(x, y2, color);
  }

  for (int y = -radius + yCenter; y <= radius + yCenter; y++)
  {
    const float x1 = xCenter + sqrt(radius * radius - (y - yCenter) * (y - yCenter));
    const float x2 = xCenter - sqrt(radius * radius - (y - yCenter) * (y - yCenter));

    PutPixelSafe(x1, y, color);
    PutPixelSafe(x2, y, color);
  }
}