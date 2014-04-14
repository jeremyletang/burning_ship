#ifndef __PNG_MAKER__
#define __PNG_MAKER__

#include <string>
#include <png.h>

enum ColorMod {
    GreyScale,
    Color
};

inline void setRGB(png_byte *ptr, float val, ColorMod color);

class PngMaker {
private:
    FILE *fp;
    png_structp png_ptr;
    png_infop info_ptr;
    png_bytep row;
    std::string title;
    int width;
    int height;

public:
    PngMaker();
    ~PngMaker();
    int initialize(std::string &file_name, int width, int height, std::string &title);
    void output(float *buffer, ColorMod mod);
};

#endif