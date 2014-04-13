#include "includes/png_maker.hpp"

#include <iostream>
#include <cstdio>

PngMaker::PngMaker() {}

PngMaker::~PngMaker() {
    if (fp != NULL) fclose(fp);
    if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
    if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
    if (row != NULL) free(row);
}

int PngMaker::initialize(std::string file_name, int width, int height, std::string title) {
    this->width = width;
    this->height = height;

    // Open file for writing (binary mode)
    this->fp = fopen(file_name.c_str(), "wb");
    if (fp == NULL) {
        std::cerr << "Could not open file " << file_name <<  " for writing" << std::endl;
        return -1;
    }

    // Initialize write structure
    this->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (this->png_ptr == NULL) {
        std::cerr << "Could not allocate write struct" << std::endl;
        return -1;
    }

    // Initialize info structure
    this->info_ptr = png_create_info_struct(this->png_ptr);
    if (this->info_ptr == NULL) {
        std::cerr << "Could not allocate info struct" << std::endl;
        return -1;
    }

    // Setup Exception handling
    if (setjmp(png_jmpbuf(this->png_ptr))) {
        std::cerr << "Error during png creation" << std::endl;
        return -1;
    }

    return 0;
}

void PngMaker::output(float *buffer) {
    png_init_io(this->png_ptr, this->fp);

    // Write header (8 bit colour depth)
    png_set_IHDR(this->png_ptr, this->info_ptr, width, height,
                 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    // Set title
    png_text title_text;
    title_text.compression = PNG_TEXT_COMPRESSION_NONE;
    title_text.key = (char *)"Title";
    title_text.text = (char *)this->title.c_str();
    png_set_text(png_ptr, info_ptr, &title_text, 1);

    png_write_info(png_ptr, info_ptr);

    // Allocate memory for one row (3 bytes per pixel - RGB)
    row = (png_bytep) malloc(3 * width * sizeof(png_byte));

    // Write image data
    int x, y;
    for (y=0 ; y<height ; y++) {
        for (x=0 ; x<width ; x++) {
            setRGB(&(row[x*3]), buffer[y*width + x]);
        }
        png_write_row(png_ptr, row);
    }

    // End write
    png_write_end(png_ptr, NULL);
}

inline void setRGB(png_byte *ptr, float val) {
    int v = (int)(val * 767);
    if (v < 0) v = 0;
    if (v > 767) v = 767;
    int offset = v % 256;

    if (v<256) {
        ptr[0] = 0; ptr[1] = 0; ptr[2] = offset;
    }
    else if (v<512) {
        ptr[0] = 0; ptr[1] = offset; ptr[2] = 255-offset;
    }
    else {
        ptr[0] = offset; ptr[1] = 255-offset; ptr[2] = 0;
    }
}
