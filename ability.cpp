//
// Created by Mariia Nosko on 10.01.2020.
//

#include "game.h"
#include <algorithm>


Ability::Ability(int abilityNum, double x, double y, int width, int height) : GameObject() {
    this->abilityNum = abilityNum;
    this->positionX = x;
    this->positionY = y;
    this->width = width;
    this->height = height;
}

bool Ability::collisionAABBvsCircle(double x, double y, int width, int height) {
    double n_x = positionX + width / 2 - x;
    double n_y = positionY + height / 2 - y;

    double closestX = n_x;
    double closestY = n_y;

    double extentX = (width - x) / 2;
    double extentY = (height - y) / 2;

    closestX = std::clamp(-extentX, extentX, closestX);
    closestY = std::clamp(-extentY, extentY, closestY);

    bool inside = false;

    if (n_x == closestX && n_y == closestY) {
        inside = true;

        // if (abs(n_x) > abs(n_y)){
        //     if (closestX > 0)
        //         closestX = extentX;
        //     else
        //         closestX = -extentX;
        // } else {
        //     if (closestY > 0)
        //         closestY = extentY;
        //     else
        //         closestY = -extentY;
        // }
    }

    double normalX = n_x - closestX;
    double normalY = n_y - closestY;
    double d = dot(normalX, normalY, normalX, normalY);
    double r = shieldRadius;

    if (d > r * r && !inside)
        return false;

    // d = sqrt(d);

    if (inside)
        return true;

}

void Ability::shield(std::vector<Asteroid> &asteroids, double shipSpeed) {
    for (auto &asteroid : asteroids) {
        if (collisionAABBvsCircle(asteroid.getLeftUpX(), asteroid.getLeftUpY(), asteroid.getWidth(),
                                  asteroid.getHeight()))
            asteroid.setSpeed(shipSpeed);
    }
}

void Ability::homingMissile(double targetX, double targetY) {
    double d = perpDot(targetX - missileX, targetY - missileY, missileVX, missileVY);
    auto theta = asin(
            d / (sqrt(missileX * missileX + missileY * missileY) * sqrt(targetX * targetX + targetY * targetY)));

    if (d < 0) {
        auto dx = directionX * cos(theta) - directionY * sin(theta);
        auto dy = directionX * sin(theta) + directionY * cos(theta);

        directionX = dx;
        directionY = dy;
    } else if (d > 0) {
        auto dx = directionX * cos(theta) + directionY * sin(theta);
        auto dy = directionX * sin(theta) - directionY * cos(theta);

        directionX = dx;
        directionY = dy;
    } else {
        d = dot(targetX - missileX, targetY - missileY, missileVX, missileVY);
        theta = acos(
                d / (sqrt(missileX * missileX + missileY * missileY) * sqrt(targetX * targetX + targetY * targetY)));

        if (d < 0) {
            auto dx = directionX * cos(theta) - directionY * sin(theta);
            auto dy = directionX * sin(theta) + directionY * cos(theta);

            directionX = dx;
            directionY = dy;
        } else {

        }
    }
}

void
Ability::getNearestEnemy(std::vector<Asteroid> asteroids, double &asteroidX, double &asteroidY) {
    double distance = std::numeric_limits<double>::infinity();
    asteroidX = 0;
    asteroidY = 0;

    for (auto &asteroid : asteroids) {
        double x = asteroid.getLeftUpX() + asteroid.getDirectionX() * asteroid.getSpeed() - positionX;
        double y = asteroid.getLeftUpY() + asteroid.getDirectionY() * asteroid.getSpeed() - positionY;

        double currentDistance = sqrt(x * x + y * y);

        if (currentDistance < distance) {
            distance = currentDistance;
            asteroidX = asteroid.getLeftUpX();
            asteroidY = asteroid.getLeftUpY();
        }
    }

}

int Ability::getAbilityNum() {
    return abilityNum;
}
