//
// Created by Mariia Nosko on 10.01.2020.
//

#include "bullet.h"

Bullet :: Bullet (double x, double y, double speed, double dirX, double dirY, int width, int height) : GameObject() {
    this->positionX = x;
    this->positionY = y;
    this->directionX = dirX;
    this->directionY = dirY;
    this->speed = speed;
    this->width = width;
    this->height = height;
}
