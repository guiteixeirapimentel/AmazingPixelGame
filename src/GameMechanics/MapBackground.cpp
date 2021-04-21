#include "MapBackground.h"
#include <cmath>
#include <iostream>

MapBackground::MapBackground()
{
    cStars.reserve(100);

    for(size_t i = 0; i < 100; i++)
    {
        const Vector2DF pos = { float(rand()%1500) -750, float(rand()%1500) - 750 };
        const float distDepth = float((rand() % 2) + 2) + 0.5f;

        Graphics::Color whiteColor = {255, 255, 255, 255};

        cStars.emplace_back(pos, distDepth, whiteColor);
    }
}

MapBackground::~MapBackground()
{}

void MapBackground::Render(const Camera& refCamera)
{
    for(Star& star : cStars)
    {
        refCamera.Render(star);
    }
}

void MapBackground::Update(Player& refPlayer, const Camera& refCam)
{
    const Vector2DF playerPos = refPlayer.GetPosition();
    const Vector2DF camPos = refCam.GetPosition();

    for(Star& star : cStars)
    {
        const Vector2DF starPos = star.GetPos() + camPos*(1.0f - 1.0f / star.GetDepthDistance());
        const float dist = (starPos - playerPos).GetMagnitudeSquared();

        if(dist > 1000.0f*1000.0f)
        {
            const Vector2DF pos = { float(rand()%800) - 400.0f, float(rand()%800) - 400.0f };

            const float distDepth = float((rand() % 2) + 2) + 0.5f;

            star.SetPos((playerPos - pos*distDepth) - refCam.GetPosition()*(1.0f - 1.0f / distDepth), distDepth);
        }
    }
}