#include "includes/burning_ship.hpp"

#include <iostream>
#include <omp.h>

BurningShip::BurningShip(Params &init_params)
  : iter(init_params.iterations),
    width(init_params.width), height(init_params.height),
    center_x(init_params.center_x), center_y(init_params.center_y),
    dimension_x(init_params.dimension_x), dimension_y(init_params.dimension_y),
    divergence(init_params.divergence),
    core(init_params.core) {

    // create the buffer with the size of image to render: image width * image height
    this->buf = new float[this->width * this->height];
}

BurningShip::~BurningShip() { delete this->buf; }

float *BurningShip::getBuf() { return this->buf; }


// divergence was 2
void BurningShip::render() {
    Point c,p0,p;
    int current_iter = 0;
    int i = 0;
    int j = 0;
    omp_set_num_threads(this->core);


    #pragma omp parallel for private(j, current_iter, c, p0, p)
    for (i = 0; i < this->width; i++) {
        #pragma omp parallel for private(current_iter, c, p0, p)
        for (j = 0; j < this->height ; j++) {
            p0.x = 0;
            p0.y = 0;
            c.x = this->center_x + this->divergence * this->dimension_x * (i / (double)this->width - 0.5);
            c.y = this->center_y + this->divergence * this->dimension_y * (j / (double)this->height - 0.5);
            for (current_iter = 0; current_iter < this->iter; current_iter++) {
                p.x = p0.x * p0.x - p0.y * p0.y - c.x;
                p.y = 2 * fabs(p0.x * p0.y) - c.y;
                p0 = p;
                if (p.x * p.x + p.y * p.y > 5) { break; }
            }
            if (current_iter == this->iter) {
                this->buf[((this->height - j - 1) * this->width) + i] = 0;
            } else {
                this->buf[((this->height - j - 1) * this->width) + i] = current_iter;
            }
        }
    }
}
