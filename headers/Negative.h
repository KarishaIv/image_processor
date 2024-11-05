#include "../headers/MainFilter.h"

struct NegativeParams : BaseParams {};

class Negative : public MainFilter {
public:
    Negative() = default;
    void ApplyFilter(Image& image) override;
    ~Negative() override = default;
};
