#include "../headers/Edge.h"
#include "../headers/Grayscale.h"

static constexpr size_t N4 = 4;             // NOLINT
static constexpr double MAX_PIXEL = 255.0;  // NOLINT

EdgeParams::EdgeParams(double arg1) {
    threshold = arg1;
}

Edge::Edge(EdgeParams *&params) {
    threshold_ = params->threshold;
}

void Edge::ApplyFilter(Image &image) {
    Grayscale grayscale_filter;
    grayscale_filter.ApplyFilter(image);

    std::vector<std::vector<double>> matrix = {{0, -1, 0}, {-1, N4, -1}, {0, -1, 0}};

    Image temp = image;
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            Pixel pixel = image.ApplyMatrix(i, j, matrix);
            uint8_t pixel_value = (pixel.R() > (MAX_PIXEL * threshold_)) ? MAX_PIXEL : 0;

            temp.SetPixel(i, j, Pixel(pixel_value, pixel_value, pixel_value));
        }
    }
    image = temp;
}
