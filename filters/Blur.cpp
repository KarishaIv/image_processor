#include "../headers/Blur.h"
#include <cmath>

static constexpr size_t MAX_PIXEL = 255;  // NOLINT

BlurParams::BlurParams(double arg1) {
    sigma = arg1;
}

Blur::Blur(BlurParams *&params) {
    sigma_ = params->sigma;
}

double Blur::Gauss(int32_t c0, int32_t c) const {
    double delta_c = static_cast<double>(c0) - static_cast<double>(c);
    double gauss = exp(-delta_c * delta_c / (2 * sigma_ * sigma_));
    gauss = gauss / sqrt(2 * M_PI * sigma_ * sigma_);
    return gauss;
}

void Blur::ApplyFilter(Image &image) {
    Image horizon = image;
    int32_t delta_sigma = static_cast<int32_t>(ceil(3 * sigma_));
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            double r = 0;
            double g = 0;
            double b = 0;
            int32_t min_y0 = static_cast<int32_t>(j) - delta_sigma;
            int32_t max_y0 = static_cast<int32_t>(j) + delta_sigma;
            for (int32_t y0 = min_y0; y0 <= max_y0; ++y0) {
                double gauss = Gauss(y0, static_cast<int32_t>(j));
                int32_t new_y0 = y0;
                if (new_y0 < 0) {
                    new_y0 = 0;
                } else if (new_y0 >= static_cast<int32_t>(image.Width())) {
                    new_y0 = static_cast<int32_t>(image.Width()) - 1;
                }
                r += gauss * static_cast<double>(image.At(i, new_y0).R());
                g += gauss * static_cast<double>(image.At(i, new_y0).G());
                b += gauss * static_cast<double>(image.At(i, new_y0).B());
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
            horizon.SetPixel(i, j, Pixel(static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b)));
        }
    }
    Image gauss_image = image;
    for (size_t j = 0; j < image.Width(); ++j) {
        for (size_t i = 0; i < image.Height(); ++i) {
            double r = 0;
            double g = 0;
            double b = 0;
            int32_t min_x0 = static_cast<int32_t>(i) - delta_sigma;
            int32_t max_x0 = static_cast<int32_t>(i) + delta_sigma;
            for (int32_t x0 = min_x0; x0 <= max_x0; ++x0) {
                double gauss = Gauss(x0, static_cast<int32_t>(i));
                int32_t new_x0 = x0;
                if (new_x0 < 0) {
                    new_x0 = 0;
                } else if (new_x0 >= static_cast<int32_t>(image.Height())) {
                    new_x0 = static_cast<int32_t>(image.Width()) - 1;
                }
                r += gauss * static_cast<double>(horizon.At(new_x0, j).R());
                g += gauss * static_cast<double>(horizon.At(new_x0, j).G());
                b += gauss * static_cast<double>(horizon.At(new_x0, j).B());
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
            gauss_image.SetPixel(i, j,
                                 Pixel(static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b)));
        }
    }
    image = gauss_image;
}
