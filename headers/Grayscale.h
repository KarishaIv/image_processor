#include "../headers/MainFilter.h"

struct GrayscaleParams : BaseParams {};

class Grayscale : public MainFilter {
public:
    Grayscale() = default;
    void ApplyFilter(Image& image) override;
    ~Grayscale() override = default;
};
