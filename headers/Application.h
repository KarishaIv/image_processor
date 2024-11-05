#pragma once
#include "MainFilter.h"

class Application {
private:
    std::vector<MainFilter*> filters_;

public:
    Application() = default;
    explicit Application(const std::vector<FilterInfo>& info);
    ~Application();

    void ApplyFilters(Image& image);
    void CreateFilters(const std::vector<FilterInfo>& info);
};
