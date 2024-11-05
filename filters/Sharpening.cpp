#include "../headers/Sharpening.h"

static constexpr size_t N5 = 5;  // NOLINT

void Sharpening::ApplyFilter(Image &image) {
    std::vector<std::vector<double>> matrix = {{0, -1, 0}, {-1, N5, -1}, {0, -1, 0}};
    Image temp = image;
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            temp.SetPixel(i, j, image.ApplyMatrix(i, j, matrix));
        }
    }
    image = temp;
}
