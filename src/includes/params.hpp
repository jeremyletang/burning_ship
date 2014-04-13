#ifndef __PARAMS__
#define __PARAMS__

#include <string>

struct Params {
    int iterations;
    int divergence;
    int width;
    int height;
    double center_x;
    double center_y;
    double dimension_x;
    double dimension_y;
    int core;
    std::string output;

    Params();
    ~Params();
    bool parseCmdLine(int ac, char **av);
    void printUsage();

private:
    static const int DEFAULT_ITERATIONS  = 255;
    static const int DEFAULT_DIVERGENCE = 2;
    static const int DEFAULT_WIDTH = 1280;
    static const int DEFAULT_HEIGHT = 720;
    static const int DEFAULT_CORE = 1;
    double DEFAULT_CENTER_X() { return 0.; }
    double DEFAULT_CENTER_Y() { return 0.; }
    double DEFAULT_DIMENSION_X() { return 0.; }
    double DEFAULT_DIMENSION_Y() { return 0.; }
    bool printBadArgsCnt(std::string option_name, int needed, int provided);
    bool nextNotNumber(std::string arg);
};

#endif
