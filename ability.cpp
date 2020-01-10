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

void Ability::shield(std::vector<Asteroid> &asteroids) {

}

void Ability::homingMissile(double targetX, double targetY) {
    double d = perpDot(targetX - missileX, targetY - missileY, missileVX, missileVY);

    if (d < 0) {

    } else if (d > 0) {

    } else {
        d = dot(targetX - missileX, targetY - missileY, missileVX, missileVY);

        if (d < 0) {

        } else {

        }
    }
}

void
Ability::getNearestEnemy(std::vector<Asteroid> asteroids, double &asteroidX, double &asteroidY) {
    double distance = std::numeric_limits<double>::infinity();
    asteroidX = 0;
    asteroidY = 0;

    for (auto & asteroid : asteroids) {
        double x = asteroid.getLeftUpX() + asteroid.getDirectionX() * asteroid.getSpeed() - positionX;
        double y = asteroid.getLeftUpY() + asteroid.getDirectionY() * asteroid.getSpeed() - positionY;

        double currentDistance = sqrt(x * x + y * y);

        if (currentDistance < distance) {
            distance = currentDistance;
            asteroidX =  asteroid.getLeftUpX();
            asteroidY = asteroid.getLeftUpY();
        }
    }

}

void Ability::autoshoting(std::vector<Asteroid> asteroids, int screen_width, int screen_height) {
//    std::__wrap_iter<Asteroid *> *asteroid = getNearestEnemy(asteroids, <#initializer#>, <#initializer#>);
    //    delete []asteroid;
}

int Ability::getAbilityNum() {
    return abilityNum;
}
