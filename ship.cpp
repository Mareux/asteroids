//
// Created by Mariia Nosko on 10.01.2020.
//
#include <utility>

#include "game.h"

Ship::Ship(double x, double y, double speed, double dirX, double dirY, int width, int height, int bulletQuantity)
        : GameObject() {
    this->positionX = x;
    this->positionY = y;
    this->directionX = dirX;
    this->directionY = dirY;
    this->speed = speed;
    this->width = width;
    this->height = height;
    this->bulletQuantity = bulletQuantity;
}

void Ship::createBullet(int x, int y) {
    double bulletDirX, bulletDirY;

    bulletDirX = x - positionX;
    bulletDirY = y - positionY;

    auto bulletDirVectorLength = sqrt(bulletDirX * bulletDirX + bulletDirY * bulletDirY);

    bulletDirX = bulletDirX / bulletDirVectorLength;
    bulletDirY = bulletDirY / bulletDirVectorLength;

    spawnedBullet.push_back(new Bullet(positionX + width / 2.0 * bulletDirX,
                                       positionY + height / 2.0 * bulletDirY,
                                       16.0,
                                       bulletDirX, bulletDirY,
                                       12,
                                       12));

    if (spawnedBullet.size() > bulletQuantity) {
        auto oldestBullet = spawnedBullet.begin();
        delete[] *oldestBullet;
        spawnedBullet.erase(oldestBullet);
    }
} //rename

void Ship::moveBullet(int screen_w, int screen_h) {
    for (auto &iter : spawnedBullet) {
        iter->getObjectFromUnderworld(screen_w, screen_h);
        iter->movement();
    }
}

void Ship::drawBullet(Sprite *bulletSprite, double cameraX, double cameraY) {
    for (auto &iter : spawnedBullet) {
        drawSprite(bulletSprite, iter->getScreenX() - cameraX, iter->getScreenY() - cameraY);
    }
}

void Ship::getAbility() {
    for (auto ability = spawnedAbilities.begin(); ability != spawnedAbilities.end(); ++ability) {
        if ((*ability)->collision(positionX, positionY, width, height)) {
            delete[]currentAbility;
            currentAbility = (*ability);
            spawnedAbilities.erase(ability);
            break;
        }
    }
}

void Ship::useAbility(std::vector<Asteroid> asteroids, int screen_w, int screen_h) {
    if (currentAbility) {
        if (currentAbility->getAbilityNum() == 3) {
            double x, y;
            currentAbility->setPositionX(positionX);
            currentAbility->setPositionY(positionY);
            currentAbility->getNearestEnemy(std::move(asteroids), x, y);
            createBullet(x, y);
            delete[]currentAbility;
            currentAbility = NULL;
        }
        else if (currentAbility->getAbilityNum() == 1){

        }
        else {

        }
    }
}

void Ship::drawAbility(Sprite *abilitySprite, double cameraX, double cameraY) {
    for (auto &iter : spawnedAbilities) {
        drawSprite(abilitySprite, iter->getScreenX() - cameraX, iter->getScreenY() - cameraY);
    }
}

bool Ship::checkBulletCollision(std::vector<Asteroid> &asteroids, std::__wrap_iter<Asteroid *> &asteroidPosition) {
    for (auto bullet = spawnedBullet.begin(); bullet != spawnedBullet.end(); ++bullet) {
        for (auto asteroid = asteroids.begin(); asteroid != asteroids.end(); ++asteroid) {
            if ((*bullet)->collision((double) (*asteroid).getLeftUpX(), (double) (*asteroid).getLeftUpY(),
                                     (*asteroid).getWidth(), (*asteroid).getHeight())) {
                delete[] *bullet;
                asteroidPosition = asteroid;
                spawnedBullet.erase(bullet);

                return true;
            }
        }
    }
    return false;
}

void Ship::setSpeedX(double x) {
    speedX = x;
}

void Ship::setSpeedY(double y) {
    speedY = y;
}


void Ship::applyVelocity(double &x, double &y) {
    x += velocityX;
    y += velocityY;
}

void Ship::shipMovement() {
    frictionX = velocityX * -0.03;
    frictionY = velocityY * -0.03;

    accelerationX = speedX + frictionX;
    accelerationY = speedY + frictionY;

    velocityX += accelerationX;
    velocityY += accelerationY;

    if (velocityX > 10.0)
        velocityX = 10.0;
    if (velocityX < -10.0)
        velocityX = -10.0;
    if (velocityY > 10.0)
        velocityY = 10.0;
    if (velocityY < -10.0)
        velocityY = -10.0;

    applyVelocity(positionX, positionY);
}

void Ship::createAbility(double x, double y, int width, int height) {
    auto *ability = new Ability(3, x, y, width, height);

    spawnedAbilities.push_back(ability);
}