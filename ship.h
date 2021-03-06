#ifndef SHIP_H
#define SHIP_H

#include "game_object.h"
#include "bullet.h"
#include "ability.h"
#include "asteroid.h"

class Ship : public GameObject {
public:
    Ship(double x, double y, double speed, double dirX, double dirY, int width, int height, int bulletQuantity);

    ~Ship(){
        for (auto &bullet:spawnedBullet)
            delete bullet;
        spawnedBullet.clear();
        for (auto &ability:spawnedAbilities)
            delete ability;
        spawnedAbilities.clear();
        delete currentAbility;
        delete missile;
    };

    void createBullet(int x, int y);

    void moveBullet(int screen_w, int screen_h);

    void drawBullet(Sprite *bulletSprite, double cameraX, double cameraY);

    void getAbility();

    void useAbility(std::vector<Asteroid> &asteroids);

    void drawAbility(std::vector<Sprite *> abilitySprite, double cameraX, double cameraY, bool used);

    bool checkBulletCollision(std::vector<Asteroid>& asteroids, std::__wrap_iter<Asteroid*> &asteroidPosition);

    void setSpeedX(double x);

    void setSpeedY(double y);

    void applyVelocity(double &x, double&y);

    void shipMovement();

    void createAbility(double x, double y, int width, int height);

    void deleteCurrentAbility();


private:
    std::vector<Bullet*> spawnedBullet{};
    std::vector<Ability*> spawnedAbilities{};
    Ability *currentAbility = NULL;
    Bullet *missile = NULL;
    int bulletQuantity;
    double speedX = 0, speedY = 0;
    double accelerationX = 0, accelerationY = 0;
    double velocityX = 0, velocityY = 0;
    double frictionX = 0, frictionY = 0;

};

#endif
