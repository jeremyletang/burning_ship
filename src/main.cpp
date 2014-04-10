#include "includes/burning_ship.hpp"
#include "includes/png_maker.hpp"
#include "includes/params.hpp"
#include "includes/chrono.hpp"

#include <cmath>
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <stdexcept>

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

    //
    Chrono chrono(true);
    
    // calculate fractal
    BurningShip b_ship(params);
    b_ship.render();

    // stop chrono
    chrono.pause();

    // store in png
    PngMaker png;
    png.initialize(file_name, params.width, params.height, title);
    png.output(b_ship.getBuf(), Color);

    // print exec time
    std::cout << "Temps d'execution " << chrono.get() << "sec." << std::endl;
}

// useful to accumulate 0 in the number of the file -> needed by ffmpeg
std::string get_zeros(int cur_image, int nb_image) {
    if (nb_image < 10) {
        return "0";
    } else {
        std::stringstream ss_cur;
        std::stringstream ss_nb;

        // get the length of the number 
        ss_cur << cur_image;
        ss_nb << nb_image;

        int nb_zeros = ss_cur.str().size();
        std::string return_zeros;
        while (nb_zeros != (int)ss_nb.str().size()) {
            nb_zeros += 1;
            return_zeros += "0";
        }
        return return_zeros;
    }
}

int get_count_number(int nb_image) {
    if (nb_image < 10) {
        return 2;
    } else {
        std::stringstream ss_nb;

        // get the length of the number 
        ss_nb << nb_image;

        return ss_nb.str().size();
    }
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
    int nb_image = configs_list->size();
    for (Config &c : *configs_list) {
        // file_name
        std::stringstream ss;
        ss << "burning_ship_" << get_zeros(i, nb_image) << i << ".png";
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
    
    // Create the video
    // use ffmpeg
    // ffmpeg -r 2 -i burning_ship_%02d.png  out.mp4
    std::stringstream ss;
    ss << "ffmpeg -r 10 -i burning_ship_%0" << get_count_number(nb_image) << "d.png burning_video.mp4";
    system(ss.str().c_str());
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
