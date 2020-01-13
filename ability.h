
#ifndef PROJECT2_ABILITY_H
#define PROJECT2_ABILITY_H

#include <vector>
#include "game_object.h"
#include "asteroid.h"

class Ability: public GameObject{
public:

    Ability (double x, double y, int width, int height);

    bool collisionAABBvsCircle(double x, double y, int w, int h);

    void shield(std::vector<Asteroid> &asteroids, double velocityX, double velocityY, double positionX,
                double positionY);

private:
    double shieldRadius = 50;
};



#endif //PROJECT2_ABILITY_H
