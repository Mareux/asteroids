
#ifndef PROJECT2_ASTEROID_H
#define PROJECT2_ASTEROID_H

#include "game_object.h"

class Asteroid : public GameObject {
public:
    Asteroid()= default;

    explicit Asteroid(bool big);

    bool isBig();

    ~Asteroid()= default;

private:
    bool big{};
};

#endif //PROJECT2_ASTEROID_H
