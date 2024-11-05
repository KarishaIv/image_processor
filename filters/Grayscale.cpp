#include "../headers/Grayscale.h"

static constexpr double N0299 = 0.299;  // NOLINT
static constexpr double N0587 = 0.587;  // NOLINT
static constexpr double N0114 = 0.114;  // NOLINT

void Grayscale::ApplyFilter(Image &image) {
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            Pixel pixel = image.At(i, j);
            uint8_t gray = static_cast<uint8_t>(N0299 * pixel.R() + N0587 * pixel.G() + N0114 * pixel.B());
            pixel.SetR(gray);
            pixel.SetG(gray);
            pixel.SetB(gray);
            image.SetPixel(i, j, pixel);
        }
    }
}
