#include "includes/burning_ship.hpp"
#include "includes/png_maker.hpp"
#include "includes/params.hpp"

#include <cmath>
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

// ./burning_ship -d 0.08 0.06 -c 1.6 0.005

struct Config {
    double center_x;
    double center_y;
    double dimension_x;
    double dimension_y;
};

Config extract(std::string line) {
    std::vector<std::string> tokens;
    std::istringstream iss(line);

    copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         std::back_inserter<std::vector<std::string> >(tokens));

    return {
        atof(tokens[0].c_str()),
        atof(tokens[1].c_str()),
        atof(tokens[2].c_str()),
        atof(tokens[3].c_str())
    };
}

std::list<Config> *load_config(std::string filename) {
    std::string line;
    std::ifstream file(filename);
    std::list<Config> *configs_list = new std::list<Config>();

    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (line != "") {
                configs_list->push_back(extract(line));
            }
        }
        file.close();
    }
    else throw std::invalid_argument(filename);
    return configs_list;
}


void simple_ship(Params &params, std::string file_name) {
    std::string title = "Burning ship fractal";
    // calculate fractal
    BurningShip b_ship(params);
    b_ship.render();

    // store in png
    PngMaker png;
    png.initialize(file_name, params.width, params.height, title);
    png.output(b_ship.getBuf(), GreyScale);
}

void video_ship(Params params) {
    std::list<Config> *configs_list;

    try { configs_list = load_config(params.output); }
    catch (const std::invalid_argument& ia) {
        std::cerr << "option `-f`, invalid filename, no such file or directory: "
        << ia.what() << std::endl;
        return;
    }
    int i = 0;
    for (Config &c : *configs_list) {
        // file_name
        std::stringstream ss;
        ss << "burning_ship_" << i << ".png";
        // fill params
        params.center_x = c.center_x;
        params.center_y = c.center_y;
        params.dimension_x = c.dimension_x / 100;
        params.dimension_y = c.dimension_y / 100;
        std::cout << c.center_x << " "
        << c.center_y << " "
        << c.dimension_x << " "
        << c.dimension_y << " " << std::endl;
        // calculate fractal
        simple_ship(params, ss.str());
        i++;
    }

    delete configs_list;
}

int main(int ac,char **av)
{
    Params params;

    if (params.parseCmdLine(ac, av)) {
        if (params.output == "") { simple_ship(params, "burning_ship.png"); }
        else { video_ship(params); }
    } else { params.printUsage(); }

    return 0;
}
