#include "headers/Parser.h"
#include "headers/Application.h"

int main(int argc, char** argv) {
    Parser parser(argc, argv);
    if (argc == 1) {
        return 0;
    }
    Image image(parser.InputPath());
    Application applicator(parser.Info());
    applicator.ApplyFilters(image);
    image.SaveFile(parser.OutputPath());
    return 0;
}
