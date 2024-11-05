#include "../headers/Image.h"
#include "fstream"

static constexpr double MAX_PIXEL = 255.0;  // NOLINT

Image::Image(const Image& other) {
    image_ = other.image_;
    width_ = other.width_;
    height_ = other.height_;
}

Image::Image(const std::vector<std::vector<Pixel>>& field) {
    image_ = field;
    height_ = field.size();
    if (height_ == 0) {
        width_ = 0;
    } else {
        width_ = field[0].size();
    }
}

Image::Image(const char* path) {
    OpenFile(path);
}

size_t Image::Width() const {
    return width_;
}

size_t Image::Height() const {
    return height_;
}

Pixel Image::At(const size_t x, const size_t y) {
    return image_[x][y];
}

Pixel Image::SetPixel(const size_t i, const size_t j, const Pixel pixel) {
    image_[i][j] = pixel;
    return image_[i][j];
}

void Image::SetImage(const std::vector<std::vector<Pixel>>& image) {
    image_ = image;
    height_ = image.size();
    if (height_ == 0) {
        width_ = 0;
    } else {
        width_ = image[0].size();
    }
}

Pixel Image::ApplyMatrix(size_t i, size_t j, const std::vector<std::vector<double>>& matrix) {
    size_t matrix_size = matrix.size();
    const int64_t matrix_center = static_cast<int64_t>((matrix_size - 1) / 2);

    double r = 0;
    double g = 0;
    double b = 0;

    for (size_t n = 0; n < matrix_size; ++n) {
        for (size_t m = 0; m < matrix_size; ++m) {
            int64_t x = static_cast<int64_t>(i) + static_cast<int64_t>(n) - matrix_center;
            int64_t y = static_cast<int64_t>(j) + static_cast<int64_t>(m) - matrix_center;
            if (x < 0) {
                x = 0;
            } else if (x >= static_cast<int64_t>(height_)) {
                x = static_cast<int64_t>(height_) - 1;
            }
            if (y < 0) {
                y = 0;
            } else if (y >= static_cast<int64_t>(width_)) {
                y = static_cast<int64_t>(width_) - 1;
            }

            r += matrix[n][m] * image_[x][y].R();
            g += matrix[n][m] * image_[x][y].G();
            b += matrix[n][m] * image_[x][y].B();
        }
    }

    if (r < 0) {
        r = 0;
    } else if (r > MAX_PIXEL) {
        r = MAX_PIXEL;
    }
    if (g < 0) {
        g = 0;
    } else if (g > MAX_PIXEL) {
        g = MAX_PIXEL;
    }
    if (b < 0) {
        b = 0;
    } else if (b > MAX_PIXEL) {
        b = MAX_PIXEL;
    }
    return Pixel(static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b));
}
