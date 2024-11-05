#include "../headers/MainFilter.h"

struct SharpeningParams : BaseParams {};

class Sharpening : public MainFilter {
public:
    Sharpening() = default;
    void ApplyFilter(Image& image) override;
    ~Sharpening() override = default;
};
