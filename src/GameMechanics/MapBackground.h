#ifndef MAPBACKGROUND_H
#define MAPBACKGROUND_H
#include <vector>

#include "Star.h"
#include "Camera/Camera.h"
#include "Player.h"

class MapBackground
{
public:
    MapBackground();
    ~MapBackground();

    void Render(const Camera& cam);

    void Update(Player& refPlayer);
private:
    std::vector<Star> cStars;
};

#endif