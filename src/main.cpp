#include "includes/burning_ship.hpp"
#include "includes/png_maker.hpp"
#include "includes/params.hpp"

// ./burning_ship -d 0.08 0.06 -c 1.6 0.005

int main(int ac,char **av)
{
    char file_name[256] = "ship.png";
    char title[256] = "Burning ship fractal";
    Params p;

    if (p.parseCmdLine(ac, av)) {

        // calculate fractale
        BurningShip b(p);
        b.render();

        // store in png
        PngMaker png;
        png.initialize(file_name, p.width, p.height, title);
        png.output(b.getBuf());
    } else {
        p.printUsage();
    }

    return 0;
}