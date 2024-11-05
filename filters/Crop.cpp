#include "../headers/Crop.h"

CropParams::CropParams(size_t arg1, size_t arg2) {
    new_width = arg1;
    new_height = arg2;
}

void Crop::ApplyFilter(Image &image) {
    std::vector<std::vector<Pixel>> new_image;
    size_t min_width = std::min(new_width_, image.Width());
    size_t min_height = std::min(new_height_, image.Height());

    new_image.resize(min_height);
    for (auto &row : new_image) {
        row.resize(min_width);
    }
}

Crop::Crop(CropParams *&params) {
    new_width_ = params->new_width;
    new_height_ = params->new_height;
}
