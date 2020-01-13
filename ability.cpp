
#include "game.h"
#include <algorithm>


Ability::Ability(double x, double y, int width, int height) : GameObject() {
    this->positionX = x;
    this->positionY = y;
    this->width = width;
    this->height = height;
}


bool Ability::collisionAABBvsCircle(double x, double y, int w, int h) {
    double circleDistX = abs(positionX - x);
    double circleDistY = abs(positionY - y);

    if (circleDistX > (w / 2.0 + shieldRadius))
        return false;
    if (circleDistY > (h / 2.0 + shieldRadius))
        return false;

    if (circleDistX <= w / 2.0)
        return true;
    if (circleDistY <= h / 2.0)
        return true;

    auto cornerDistSq = (circleDistX - w / 2.0) * (circleDistX - w / 2.0)
                        + (circleDistY - h / 2.0) * (circleDistY - h / 2.0);

    return (cornerDistSq <= shieldRadius * shieldRadius);
}

void Ability::shield(std::vector<Asteroid> &asteroids, double velocityX, double velocityY, double positionX,
                     double positionY) {
    for (auto &asteroid : asteroids) {
        if (collisionAABBvsCircle(asteroid.getLeftUpX(), asteroid.getLeftUpY(), asteroid.getWidth(),
                                  asteroid.getHeight())) {

            auto dirX = asteroid.getLeftUpX() - positionX;
            auto dirY = asteroid.getLeftUpY() - positionY;

            auto length = sqrt(dirX * dirX + dirY * dirY);
            auto normalDirX = dirX / length;
            auto normalDirY = dirY / length;

            asteroid.setPositionX(asteroid.getLeftUpX() + asteroid.getSpeed() * normalDirX + velocityX);
            asteroid.setPositionY(asteroid.getLeftUpY() + asteroid.getSpeed() * normalDirY + velocityY);
        }
    }
}
