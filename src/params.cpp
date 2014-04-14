#include "includes/params.hpp"
#include <iostream>

Params::Params()
  : iterations(DEFAULT_ITERATIONS),
    divergence(DEFAULT_DIVERGENCE),
    width(DEFAULT_WIDTH), height(DEFAULT_HEIGHT),
    center_x(DEFAULT_CENTER_X()), center_y(DEFAULT_CENTER_Y()),
    dimension_x(DEFAULT_DIMENSION_X()), dimension_y(DEFAULT_DIMENSION_Y()),
    core(DEFAULT_CORE),
    output("") {}

Params::~Params() {}

void Params::printUsage() {
    std::cout << "usage:" << std::endl
    << "\t-c [center_x] [center_y]: position of the grid center." << std::endl
    << "\t-d [dimension_x] [dimension_y]: dimension of the grid" << std::endl
    << "\t-s [width] [height]: size of the image" << std::endl
    << "\t-i [iterations]: max number of iterations" << std::endl
    << "\t-core [count]: number of core to use" << std::endl
    << "\t-div [number]: divergence max" << std::endl
    << "\t-f [filename]: file to load" << std::endl << std::endl;
}

bool Params::printBadArgsCnt(std::string option_name, int needed, int provided) {
    std::cout << "invalid number of arguments for option `" << option_name <<
    "` needed " << needed << " arguments, provided " << provided << "." << std::endl;
    return false;
}

bool Params::nextNotNumber(std::string arg) {
    if (isdigit(arg[0]) || (arg[0] == '-' && isdigit(arg[1]))) {
        return false;
    } else {
        std::cout << "argument: " << arg << " should be numeric" << std::endl;
        return true;
    }
}

bool Params::parseCmdLine(int ac, char **av) {
    for (int i = 1; i < ac; i++) {
        std::string arg(av[i]);
        if (arg.compare("-c") == 0) {
            if (i + 1 >= ac || i + 2 >= ac) { return this->printBadArgsCnt("-c", 2, (ac - 1) - i); }
            if (this->nextNotNumber(av[i + 1])) { return false; }
            i++;
            this->center_x = atof(av[i]);
            if (this->nextNotNumber(av[i + 1])) { return false; }
            i++;
            this->center_y = atof(av[i]);
        } else if (arg.compare("-d") == 0) {
            if (i + 1 >= ac || i + 2 >= ac) { return this->printBadArgsCnt("-d", 2, (ac - 1) - i); }
            if (this->nextNotNumber(av[i + 1])) { return false; }
            i++;
            this->dimension_x = atof(av[i]) / 100;
            if (this->nextNotNumber(av[i + 1])) { return false; }
            i++;
            this->dimension_y = atof(av[i]) / 100;
        } else if (arg.compare("-s") == 0) {
            if (i + 1 >= ac || i + 2 >= ac) { return this->printBadArgsCnt("-s", 2, (ac - 1) - i); }
            if (this->nextNotNumber(av[i + 1])) { return false; }
            i++;
            this->width = atoi(av[i]);
            if (this->nextNotNumber(av[i + 1])) { return false; }
            i++;
            this->height = atoi(av[i]);
        } else if (arg.compare("-i") == 0) {
            if (i + 1 >= ac) { return this->printBadArgsCnt("-i", 2, (ac - 1) - i); }
            if (this->nextNotNumber(av[i + 1])) { return false; }
            i++;
            this->iterations = atoi(av[i]);
        } else if (arg.compare("-core") == 0) {
            if (i + 1 >= ac) { return this->printBadArgsCnt("-core", 2, (ac - 1) - i); }
            if (this->nextNotNumber(av[i + 1])) { return false; }
            i++;
            this->core = atoi(av[i]);
        } else if (arg.compare("-div") == 0) {
            if (i + 1 >= ac) { return this->printBadArgsCnt("-div", 2, (ac - 1) - i); }
            if (this->nextNotNumber(av[i + 1])) { return false; }
            i++;
            this->divergence = atoi(av[i]);
        } else if (arg.compare("-f") == 0) {
            if (i + 1 >= ac) { return this->printBadArgsCnt("-f", 2, (ac - 1) - i); }
            i++;
            this->output = av[i];
        } else {
            std::cout << "invalid option: " << av[i] << std::endl;
            return false;
        }
    }

    return true;
}
