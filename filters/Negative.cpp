#include "../headers/Negative.h"

static constexpr size_t MAX_PIXEL = 255;  // NOLINT

void Negative::ApplyFilter(Image &image) {
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            Pixel pixel = image.At(i, j);
            uint8_t new_r = static_cast<uint8_t>(MAX_PIXEL - pixel.R());
            uint8_t new_g = static_cast<uint8_t>(MAX_PIXEL - pixel.G());
            uint8_t new_b = static_cast<uint8_t>(MAX_PIXEL - pixel.B());
            pixel.SetR(new_r);
            pixel.SetG(new_g);
            pixel.SetB(new_b);
            image.SetPixel(i, j, pixel);
        }
    }
}
