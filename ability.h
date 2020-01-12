//
// Created by Mariia Nosko on 10.01.2020.
//

#ifndef PROJECT2_ABILITY_H
#define PROJECT2_ABILITY_H

#include <vector>
#include "game_object.h"
#include "asteroid.h"

class Ability: public GameObject{
public:

    Ability (int abilityNum, double x, double y, int width, int height);

    bool collisionAABBvsCircle(double x, double y, int w, int h);

    void shield(std::vector<Asteroid> &asteroids, double velocityX, double velocityY);

    void follow(double targetX, double targetY, Bullet *missile);

    void getNearestEnemy(std::vector<Asteroid> asteroids, double &asteroidX, double &asteroidY);

    int getAbilityNum();

    void homingMissile(double targetX, double targetY, Bullet *missile);

private:
    int abilityNum = 0;
    double missileX, missileY;
    double missileVX = 10.0, missileVY = 10.0;
    double shieldRadius = 50;

};



#endif //PROJECT2_ABILITY_H
