#ifndef __BURNING_SHIP__
#define __BURNING_SHIP__

#include "params.hpp"

#include <cmath>

typedef struct {
    double x;
    double y;
} Point;

class BurningShip {
private:
    float *buf;
    int iter;
    int width;
    int height;
    double center_x;
    double center_y;
    double dimension_x;
    double dimension_y;

public:
    BurningShip(Params &init_params);
    ~BurningShip();
    void render();
    float *getBuf();
};

#endif