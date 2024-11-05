#pragma once
#include "Image.h"

enum FilterName { CROP, GRAYSCALE, NEGATIVE, SHARPENING, EDGE, BLUR, M0SAIC };

struct BaseParams {};

struct FilterInfo {
    FilterInfo(FilterName arg1, BaseParams* arg2) {
        filter_name = arg1;
        params = arg2;
    }
    ~FilterInfo() = default;
    FilterName filter_name;
    BaseParams* params;
};

class MainFilter {
public:
    virtual void ApplyFilter(Image& image) = 0;
    virtual ~MainFilter() = default;
};
