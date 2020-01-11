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

    bool collisionAABBvsCircle(double x, double y, int width, int height);

    void shield(std::vector<Asteroid> &asteroids, double shipSpeed);

    void homingMissile(double targetX, double targetY);

    void getNearestEnemy(std::vector<Asteroid> asteroids, double &asteroidX, double &asteroidY);

    int getAbilityNum();

private:
    int abilityNum = 0;
    double missileX, missileY;
    double missileVX, missileVY;
    double shieldRadius;
};



#endif //PROJECT2_ABILITY_H
