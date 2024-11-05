#include "../headers/Parser.h"
#include "../headers/Crop.h"
#include "../headers/Grayscale.h"
#include "../headers/Negative.h"
#include "../headers/Sharpening.h"
#include "../headers/Edge.h"
#include "../headers/Blur.h"
#include "../headers/MosaicFilter.h"
#include "iostream"
#include <cstring>

static constexpr std::string_view HELP =
    "Help:\n\n"
    "   ./image_processor {path to input file} {path to output file}\n"
    "   [-{filter name 1} [filter parameter 1] [filter parameter 2] ...]\n"
    "   [-{filter name 2} [filter parameter 1] [filter parameter 2] ...]\n"
    "                                ...\n"
    "Example:\n\n"
    "   ./image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5\n";

Parser::Parser(int size, char** query) {
    ParseQuery(size, query);
}

Parser::~Parser() {
    for (size_t i = 0; i < filter_info_.size(); ++i) {
        delete filter_info_[i].params;
    }
}

char* Parser::InputPath() {
    return input_path_;
}

char* Parser::OutputPath() {
    return output_path_;
}

std::vector<FilterInfo> Parser::Info() {
    return filter_info_;
}

void Parser::ParseQuery(int size, char** query) {
    if (size == 1) {
        std::cout << HELP << std::endl;
        return;
    }
    if (size < 3) {
        throw std::runtime_error("ERROR: NOT ENOUGH ARGUMENTS");
    }
    input_path_ = query[1];
    output_path_ = query[2];
    for (size_t i = 3; i < size;) {
        if (strcmp(query[i], "-crop") == 0) {
            if (i + 2 >= size) {
                throw std::runtime_error("ERROR: NOT ENOUGH ARGUMENTS FOR -crop");
            }
            if (!(std::stoi(query[i + 1]) >= 0 && std::stoi(query[i + 2]) >= 0)) {
                throw std::runtime_error("ERROR: WRONG ARGUMENTS FOR -crop");
            }
            size_t arg1 = std::stoi(query[i + 1]);
            size_t arg2 = std::stoi(query[i + 2]);
            if (arg1 == 0 || arg2 == 0) {
                arg1 = arg2 = 0;
            }
            filter_info_.push_back(FilterInfo(CROP, new CropParams(arg1, arg2)));
            i += 3;
        } else if (strcmp(query[i], "-gs") == 0) {
            filter_info_.push_back(FilterInfo(GRAYSCALE, new GrayscaleParams()));
            ++i;
        } else if (strcmp(query[i], "-neg") == 0) {
            filter_info_.push_back(FilterInfo(NEGATIVE, new NegativeParams()));
            ++i;
        } else if (strcmp(query[i], "-sharp") == 0) {
            filter_info_.push_back(FilterInfo(SHARPENING, new SharpeningParams()));
            ++i;
        } else if (strcmp(query[i], "-edge") == 0) {
            if (i + 1 >= size) {
                throw std::runtime_error("ERROR: NOT ENOUGH ARGUMENTS FOR -edge");
            }
            if (!(std::stod(query[i + 1]) >= 0 && std::stod(query[i + 1]) <= 1)) {
                throw std::runtime_error("ERROR: WRONG ARGUMENTS FOR -edge");
            }
            double arg1 = std::stod(query[i + 1]);
            filter_info_.push_back(FilterInfo(EDGE, new EdgeParams(static_cast<double>(arg1))));
            i += 2;
        } else if (strcmp(query[i], "-blur") == 0) {
            if (i + 1 >= size) {
                throw std::runtime_error("ERROR: NOT ENOUGH ARGUMENTS FOR -blur");
            }
            double arg1 = std::stod(query[i + 1]);
            filter_info_.push_back(FilterInfo(BLUR, new BlurParams(static_cast<double>(arg1))));
            i += 2;
        } else if (strcmp(query[i], "-mosaic") == 0) {
            if (i + 1 >= size) {
                throw std::runtime_error("ERROR: NOT ENOUGH ARGUMENTS FOR -mosaic");
            }
            size_t arg1 = std::stoi(query[i + 1]);
            filter_info_.push_back(FilterInfo(M0SAIC, new MosaicParams(static_cast<size_t>(arg1))));
            i += 2;
        } else {
            throw std::runtime_error("ERROR: WRONG FILTER NAME/FILTER NOT IMPLEMENTED");
        }
    }
}
