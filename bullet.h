
#ifndef PROJECT2_BULLET_H
#define PROJECT2_BULLET_H

#include "game_object.h"

class Bullet : public GameObject{
public:
    Bullet (double x, double y, double speed, double dirX, double dirY, int width, int height);

    ~Bullet() = default;
};


#endif //PROJECT2_BULLET_H
