#include "../headers/Application.h"
#include <iostream>
#include "../headers/Crop.h"
#include "../headers/Grayscale.h"
#include "../headers/Negative.h"
#include "../headers/Sharpening.h"
#include "../headers/Edge.h"
#include "../headers/Blur.h"
#include "../headers/MosaicFilter.h"

Application::Application(const std::vector<FilterInfo>& info) {
    CreateFilters(info);
}

Application::~Application() {
    for (auto& filter : filters_) {
        delete filter;
    }
}

void Application::CreateFilters(const std::vector<FilterInfo>& info) {
    for (auto& item : info) {
        if (item.filter_name == CROP) {
            CropParams* params = reinterpret_cast<CropParams*>(item.params);
            filters_.push_back(new Crop(params));
        } else if (item.filter_name == GRAYSCALE) {
            filters_.push_back(new Grayscale());
        } else if (item.filter_name == NEGATIVE) {
            filters_.push_back(new Negative());
        } else if (item.filter_name == SHARPENING) {
            filters_.push_back(new Sharpening());
        } else if (item.filter_name == EDGE) {
            EdgeParams* params = reinterpret_cast<EdgeParams*>(item.params);
            filters_.push_back(new Edge(params));
        } else if (item.filter_name == BLUR) {
            BlurParams* params = reinterpret_cast<BlurParams*>(item.params);
            filters_.push_back(new Blur(params));
        } else if (item.filter_name == M0SAIC) {
            MosaicParams* params = reinterpret_cast<MosaicParams*>(item.params);
            filters_.push_back(new MosaicFilter(params));
        } else {
            std::cout << "WRONG FILTER NAME/FILTER NOT IMPLEMENTED";
        }
    }
}

void Application::ApplyFilters(Image& image) {
    for (auto& filter : filters_) {
        filter->ApplyFilter(image);
    }
}
