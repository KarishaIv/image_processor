#include "../headers/MainFilter.h"

struct CropParams : BaseParams {
    CropParams(size_t arg1, size_t arg2);
    size_t new_width;
    size_t new_height;
};

class Crop : public MainFilter {
private:
    size_t new_width_;
    size_t new_height_;

public:
    Crop() = default;
    explicit Crop(CropParams*& params);
    ~Crop() override = default;

    void ApplyFilter(Image& image) override;
};
