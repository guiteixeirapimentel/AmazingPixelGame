#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <chrono>
#include <iomanip>
#include <vector>
#include <numeric>

#include <cinttypes>

#include <SDL/SDL.h>

class Graphics
{
public:
    struct Color
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };

public:
    Graphics(uint32_t bufWidth = 800, uint32_t bufHeight = 600);
    ~Graphics();

    void PutPixel(int x, int y, const Color &color);
    void PutPixelSafe(int x, int y, const Color &color);

    void DrawLine(int x1, int y1, int x2, int y2, const Color &color);
    void DrawLine(int x1, int y1, int x2, int y2, int thickness, const Color &color);
    void DrawRectangle(int xMin, int yMin, int xMax, int yMax, const Color &color);
    void DrawFilledRectangle(int xMin, int yMin, int xMax, int yMax, const Color &color);
    void DrawCircle(int radius, int xCenter, int yCenter, const Color &color);

    void Init();
    void Present(bool vsync = true);

    uint32_t GetWidth() const { return cWidth; }
    uint32_t GetHeight() const { return cHeight; }

private:
    const uint32_t cWidth;
    const uint32_t cHeight;

    SDL_Surface *cPScreen;

    std::chrono::steady_clock::time_point cStartRender;
    std::chrono::steady_clock::time_point cEndRender;

public:
    static constexpr size_t cFramesPerSec = 60;
    static constexpr size_t cMiliPerFrame = 1000 / cFramesPerSec;
};

#endif