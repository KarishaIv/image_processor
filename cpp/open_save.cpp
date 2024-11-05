#include "../headers/Image.h"
#include <fstream>

enum BMPHeaderIndex {
    HEADER_IND0 = 0,
    HEADER_IND1 = 1,
    HEADER_IND2 = 2,
    HEADER_IND3 = 3,
    HEADER_IND4 = 4,
    HEADER_IND5 = 5,
    HEADER_IND6 = 6,
    HEADER_IND7 = 7,
    HEADER_IND8 = 8,
    HEADER_IND9 = 9,
    HEADER_IND10 = 10,
    HEADER_IND11 = 11,
    HEADER_IND12 = 12,
    HEADER_IND14 = 14,
    HEADER_IND15 = 15
};

static constexpr size_t SIZE_FILE_HEADER = 14;  // NOLINT
static constexpr size_t SIZE_INFO_HEADER = 40;  // NOLINT
static constexpr int N6 = 6;                    // NOLINT
static constexpr size_t BITS_IN_BYTE = 8;       // NOLINT
static constexpr size_t BYTES_IN_PIXEL = 3;     // NOLINT
static constexpr size_t PIXELS_ALIGNMENT = 4;   // NOLINT
static constexpr uint16_t BIT_PER_PIXEL = 24;   // NOLINT

void CreateFileHeader(uint8_t* file_header, const size_t file_size) {
    file_header[HEADER_IND0] = 'B';
    file_header[HEADER_IND1] = 'M';
    file_header[HEADER_IND2] = static_cast<uint8_t>(file_size);
    file_header[HEADER_IND3] = static_cast<uint8_t>(file_size >> BITS_IN_BYTE);
    file_header[HEADER_IND4] = static_cast<uint8_t>(file_size >> (2 * BITS_IN_BYTE));
    file_header[HEADER_IND5] = static_cast<uint8_t>(file_size >> (3 * BITS_IN_BYTE));
    for (size_t i = N6; i < SIZE_FILE_HEADER; ++i) {
        if (i == HEADER_IND10) {
            file_header[i] = SIZE_FILE_HEADER + SIZE_INFO_HEADER;
            continue;
        }
        file_header[i] = 0;
    }
}

void Image::OpenFile(const char* path) {
    std::ifstream f;
    f.open(path, std::ios::binary | std::ios::in);

    if (!f) {
        throw std::runtime_error("ERROR: WRONG INPUT PATH");
    }

    uint8_t file_header[SIZE_FILE_HEADER];
    f.read(reinterpret_cast<char*>(file_header), SIZE_FILE_HEADER);

    uint8_t info_header[SIZE_INFO_HEADER];
    f.read(reinterpret_cast<char*>(info_header), SIZE_INFO_HEADER);
    int bits_per_pixel = info_header[HEADER_IND14] + (info_header[HEADER_IND15] << BITS_IN_BYTE);

    if ((!(file_header[HEADER_IND0] == 'B' && file_header[HEADER_IND1] == 'M')) ||
        ((bits_per_pixel != BIT_PER_PIXEL))) {
        f.close();
        throw std::runtime_error("ERROR: WRONG IMAGE TYPE");
    }

    width_ = static_cast<size_t>(info_header[HEADER_IND4] + (info_header[HEADER_IND5] << BITS_IN_BYTE) +
                                 (info_header[HEADER_IND6] << (BITS_IN_BYTE * 2)) +
                                 (info_header[HEADER_IND7] << (BITS_IN_BYTE * 3)));

    height_ = static_cast<size_t>(info_header[HEADER_IND8] + (info_header[HEADER_IND9] << BITS_IN_BYTE) +
                                  (info_header[HEADER_IND10] << (BITS_IN_BYTE * 2)) +
                                  (info_header[HEADER_IND11] << (BITS_IN_BYTE * 3)));

    if (width_ == 0 || height_ == 0) {
        width_ = height_ = 0;
    }

    size_t padding = (PIXELS_ALIGNMENT - BYTES_IN_PIXEL * (width_ % PIXELS_ALIGNMENT)) % PIXELS_ALIGNMENT;

    image_.assign(height_, std::vector<Pixel>(width_));
    for (ssize_t i = static_cast<ssize_t>(height_ - 1); i >= 0; --i) {
        for (ssize_t j = 0; j < static_cast<ssize_t>(width_); ++j) {
            uint8_t pixel[3];
            f.read(reinterpret_cast<char*>(pixel), 3);
            image_[i][j] = Pixel(pixel[2], pixel[1], pixel[0]);
        }
        f.ignore(static_cast<int64_t>(padding));
    }

    f.close();
}

void Image::SaveFile(const char* path) {
    std::ofstream f;
    f.open(path, std::ios::binary | std::ios::out);
    if (!f) {
        throw std::runtime_error("ERROR: WRONG OUTPUT PATH");
    }

    size_t padding = (PIXELS_ALIGNMENT - BYTES_IN_PIXEL * (width_ % PIXELS_ALIGNMENT)) % PIXELS_ALIGNMENT;

    size_t file_size = SIZE_FILE_HEADER + SIZE_INFO_HEADER + width_ * height_ * 3 + height_ * padding;

    uint8_t file_header[SIZE_FILE_HEADER];
    CreateFileHeader(file_header, file_size);

    uint8_t info_header[SIZE_INFO_HEADER];
    for (size_t i = 0; i < SIZE_INFO_HEADER; ++i) {
        info_header[i] = 0;
    }
    info_header[HEADER_IND0] = SIZE_INFO_HEADER;
    info_header[HEADER_IND4] = width_;
    info_header[HEADER_IND5] = width_ >> BITS_IN_BYTE;
    info_header[HEADER_IND6] = width_ >> (2 * BITS_IN_BYTE);
    info_header[HEADER_IND7] = width_ >> (3 * BITS_IN_BYTE);
    info_header[HEADER_IND8] = height_;
    info_header[HEADER_IND9] = height_ >> BITS_IN_BYTE;
    info_header[HEADER_IND10] = height_ >> (2 * BITS_IN_BYTE);
    info_header[HEADER_IND11] = height_ >> (3 * BITS_IN_BYTE);
    info_header[HEADER_IND12] = 1;
    info_header[HEADER_IND14] = BIT_PER_PIXEL;
    f.write(reinterpret_cast<char*>(file_header), SIZE_FILE_HEADER);
    f.write(reinterpret_cast<char*>(info_header), SIZE_INFO_HEADER);
    uint8_t pad[3] = {0, 0, 0};
    for (ssize_t i = static_cast<ssize_t>(height_) - 1; i >= 0; --i) {
        for (size_t j = 0; j < width_; ++j) {
            uint8_t pixel[3] = {image_[i][j].B(), image_[i][j].G(), image_[i][j].R()};
            f.write(reinterpret_cast<char*>(pixel), 3);
        }
        if (padding != 0) {
            f.write(reinterpret_cast<char*>(pad), static_cast<int64_t>(padding));
        }
    }
    f.close();
}
