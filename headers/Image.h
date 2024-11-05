#pragma once
#include <vector>
#include "Pixel.h"
#include "cstdint"
#include <stddef.h>

class Image {
private:
    std::vector<std::vector<Pixel>> image_;
    size_t width_;
    size_t height_;

public:
    Image() = default;
    Image(const Image& other);
    explicit Image(const std::vector<std::vector<Pixel>>& field);
    void SetImage(const std::vector<std::vector<Pixel>>& image);
    Pixel SetPixel(const size_t i, const size_t j, const Pixel pixel);
    Pixel ApplyMatrix(size_t i, size_t j, const std::vector<std::vector<double>>& matrix);
    explicit Image(const char* path);
    ~Image() = default;

    Pixel At(const size_t x, const size_t y);
    void OpenFile(const char* path);
    void SaveFile(const char* path);

    size_t Width() const;
    size_t Height() const;
};
