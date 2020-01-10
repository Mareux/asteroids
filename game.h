//
// Created by Mariia Nosko on 10.01.2020.
//

#ifndef PROJECT2_GAME_H
#define PROJECT2_GAME_H

#include "../Framework/inc/Framework.h"
#include <cstdlib>
#include <cmath>
#include <utility>
#include <vector>
#include <iostream>
#include "ship.h"


double dot(double a_x, double a_y, double b_x, double b_y);

double perpDot(double a_x, double a_y, double b_x, double b_y);

double    random_between_two_int(double min, double max);

int randomInt(int outerMin, int outerMax, int innerMin, int innerMax);

#endif //PROJECT2_GAME_H
