#include "../headers/MosaicFilter.h"
#include <iostream>

MosaicParams::MosaicParams(size_t arg1) {
    cell = arg1;
}

MosaicFilter::MosaicFilter(MosaicParams *&params) {
    cell_ = std::max(static_cast<size_t>(1), params->cell);  // Устанавливаем минимальное значение 1
}

void MosaicFilter::ApplyFilter(Image &image) {
    size_t width = image.Width();
    size_t height = image.Height();

    // Приводим изображение к квадратному виду
    std::vector<std::vector<Pixel>> new_image;
    size_t min_width = std::min(width, height);
    size_t min_height = std::min(width, height);
    new_image.assign(min_height, std::vector<Pixel>(min_width));
    for (size_t i = 0; i < min_height; ++i) {
        for (size_t j = 0; j < min_width; ++j) {
            new_image[i][j] = image.At(i, j);
        }
    }
    image.SetImage(new_image);

    // Получаем размер ячейки мозаики
    size_t cell_size = cell_;
    size_t width_new = image.Width();
    size_t height_new = image.Height();

    // Применяем фильтр к каждой ячейке мозаики
    for (size_t y = 0; y < height_new; y += cell_size) {
        for (size_t x = 0; x < width_new; x += cell_size) {
            // Получаем средний цвет для текущей ячейки мозаики
            Pixel average_color = GetAverageColor(image, x, y, cell_size);

            // Заполняем текущую ячейку мозаики средним цветом
            FillCell(image, x, y, cell_size, average_color);
        }
    }
}

Pixel MosaicFilter::GetAverageColor(Image &image, size_t x_start, size_t y_start, size_t cell_size) {
    size_t total_pixels = 0;
    uint64_t red_sum = 0;
    uint64_t green_sum = 0;
    uint64_t blue_sum = 0;

    // Перебираем пиксели в текущей ячейке мозаики и суммируем их компоненты цвета
    for (size_t y = y_start; y < std::min(y_start + cell_size, image.Height()); ++y) {
        for (size_t x = x_start; x < std::min(x_start + cell_size, image.Width()); ++x) {
            Pixel pixel = image.At(x, y);
            red_sum += pixel.R();
            green_sum += pixel.G();
            blue_sum += pixel.B();
            ++total_pixels;
        }
    }

    // Вычисляем средние значения компонент цвета
    uint8_t average_red = static_cast<uint8_t>(red_sum / total_pixels);
    uint8_t average_green = static_cast<uint8_t>(green_sum / total_pixels);
    uint8_t average_blue = static_cast<uint8_t>(blue_sum / total_pixels);

    return Pixel(average_red, average_green, average_blue);
}

void MosaicFilter::FillCell(Image &image, size_t x_start, size_t y_start, size_t cell_size, const Pixel &color) {
    // Заполняем текущую ячейку мозаики средним цветом
    for (size_t y = y_start; y < std::min(y_start + cell_size, image.Height()); ++y) {
        for (size_t x = x_start; x < std::min(x_start + cell_size, image.Width()); ++x) {
            image.SetPixel(x, y, color);
        }
    }
}
