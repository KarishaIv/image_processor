#pragma once
#include <cstdint>

class Pixel {
private:
    uint8_t r_;
    uint8_t g_;
    uint8_t b_;

public:
    Pixel();
    Pixel(const Pixel& other);
    Pixel(const uint8_t r, const uint8_t g, const uint8_t b);
    ~Pixel() = default;

    uint8_t R() const;
    uint8_t G() const;
    uint8_t B() const;

    void SetR(const uint8_t r);
    void SetG(const uint8_t g);
    void SetB(const uint8_t b);

    friend Pixel operator*(double k, Pixel pixel);
    friend Pixel operator+(Pixel lhs, Pixel rhs);
    friend Pixel operator!(const Pixel& pixel);
    Pixel& operator+=(Pixel other);
};
