
#include "asteroid.h"

Asteroid::Asteroid(bool big) : GameObject()
{
    this->big = big;
}

bool Asteroid::isBig(){
    return big;
}
