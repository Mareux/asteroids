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

void Ability::shield(std::vector<Asteroid> &asteroids, double velocityX, double velocityY) {
    for (auto &asteroid : asteroids) {
        if (collisionAABBvsCircle(asteroid.getLeftUpX(), asteroid.getLeftUpY(), asteroid.getWidth(),
                                  asteroid.getHeight())) {
            asteroid.setPositionX(asteroid.getLeftUpX() - asteroid.getSpeed() * asteroid.getDirectionX() + velocityX);
            asteroid.setPositionY(asteroid.getLeftUpY() - asteroid.getSpeed() * asteroid.getDirectionY() + velocityY);
        }
    }
}

void Ability::homingMissile(double targetX, double targetY, Bullet *missile) {


}

void Ability::follow(double targetX, double targetY, Bullet *missile) {
    double d = perpDot(targetX - positionX, targetY - positionY, missileVX, missileVY);
    auto theta = asin(
            d / (sqrt(positionX * positionX + positionY * positionY) * sqrt(targetX * targetX + targetY * targetY)));

    if (d < 0) {
        auto dx = missile->getDirectionX() * cos(theta) - missile->getDirectionY() * sin(theta);
        auto dy = missile->getDirectionX() * sin(theta) + missile->getDirectionY() * cos(theta);

        missile->setDirection(dx, dy);

    } else if (d > 0) {
        auto dx = missile->getDirectionX() * cos(theta) + missile->getDirectionY() * sin(theta);
        auto dy = missile->getDirectionX() * -sin(theta) + missile->getDirectionY() * cos(theta);

        missile->setDirection(dx, dy);

    } else {
        d = dot(targetX - positionX, targetY - positionY, missileVX, missileVY);
        theta = acos(
                d /
                (sqrt(positionX * positionX + positionY * positionY) * sqrt(targetX * targetX + targetY * targetY)));

        if (d < 0) {
            auto dx = missile->getDirectionX() * cos(theta) - missile->getDirectionY() * sin(theta);
            auto dy = missile->getDirectionX() * sin(theta) + missile->getDirectionY() * cos(theta);

            missile->setDirection(dx, dy);

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
