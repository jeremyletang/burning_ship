#include "includes/burning_ship.hpp"

BurningShip::BurningShip(Params &init_params)
  : iter(init_params.iterations),
    width(init_params.width), height(init_params.height),
    center_x(init_params.center_x), center_y(init_params.center_y),
    dimension_x(init_params.dimension_x), dimension_y(init_params.dimension_y) {

    // create the buffer with the size of image to render: image width * image height
    this->buf = new float[this->width * this->height];
}

BurningShip::~BurningShip() {
    delete this->buf;
}

void BurningShip::render() {
    Point c,p0,p;
    int i, j, k = 0;

     for (i = 0; i < this->width; i++) {
        for (j = 0; j < this->height ;j++) {
            p0.x = 0;
            p0.y = 0;
            c.x = this->center_x + 2 * this->dimension_x * (i / (double)this->width - 0.5);
            c.y = this->center_y + 2 * this->dimension_y * (j / (double)this->height - 0.5);
            for (k=0;k<this->iter;k++) {
                p.x = p0.x*p0.x - p0.y*p0.y - c.x;
                p.y = 2 * fabs(p0.x*p0.y) - c.y;
                p0 = p;
                if (p.x*p.x + p.y*p.y > 5) {
                    break;
                }
            }
            if (k == this->iter) {
                this->buf[((this->height - j -1) * this->width) + i] = 0;
            }
            else {
                this->buf[((this->height - j -1) * this->width) + i] = 1 - (float)k / this->iter;
            }
        }
    }
}

float *BurningShip::getBuf() {
    return this->buf;
}