#include "../headers/MainFilter.h"

struct EdgeParams : BaseParams {
    explicit EdgeParams(double arg1);
    double threshold;
};

class Edge : public MainFilter {
private:
    double threshold_;

public:
    Edge() = default;
    explicit Edge(EdgeParams*& params);
    void ApplyFilter(Image& image) override;
    ~Edge() override = default;
};
