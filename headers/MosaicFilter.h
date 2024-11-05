#include "../headers/MainFilter.h"

//Фильтр делает из КВАДРАТНОГО изображения мозаику
//Если подается не квадратное, то фильтр обрезает его до квадратного
//Для вызова -mosaic param

struct MosaicParams : BaseParams {
    explicit MosaicParams(size_t arg1);
    size_t cell;
};

class MosaicFilter : public MainFilter {
private:
    size_t cell_;

public:
    MosaicFilter() = default;
    explicit MosaicFilter(MosaicParams *&params);
    void ApplyFilter(Image &image) override;
    Pixel GetAverageColor(Image &image, size_t x_start, size_t y_start, size_t cell_size);
    void FillCell(Image &image, size_t x_start, size_t y_start, size_t cell_size, const Pixel &color);
    ~MosaicFilter() override = default;
};
