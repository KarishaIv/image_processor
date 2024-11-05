#include "../headers/MainFilter.h"

struct BlurParams : BaseParams {
    explicit BlurParams(double arg1);
    double sigma;
};

class Blur : public MainFilter {
private:
    double sigma_;

public:
    Blur() = default;
    explicit Blur(BlurParams*& params);
    double Gauss(int32_t c0, int32_t c) const;
    void ApplyFilter(Image& image) override;
    ~Blur() override = default;
};