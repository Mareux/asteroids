//
// Created by Mariia Nosko on 10.01.2020.
//

#ifndef PROJECT2_ASTEROID_H
#define PROJECT2_ASTEROID_H

#include "game_object.h"

class Asteroid : public GameObject {
public:
    Asteroid()= default;

    explicit Asteroid(bool big) : GameObject()
    {
        this->big = big;
    }

    bool isBig(){
        return big;
    }

    ~Asteroid()= default;

private:
    bool big{};
};

#endif //PROJECT2_ASTEROID_H
