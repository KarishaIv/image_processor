#pragma once
#include "MainFilter.h"

class Parser {
private:
    char* input_path_;
    char* output_path_;
    std::vector<FilterInfo> filter_info_;

public:
    Parser() = default;
    ~Parser();

    char* InputPath();
    char* OutputPath();
    std::vector<FilterInfo> Info();

    Parser(int size, char** query);
    void ParseQuery(int size, char** query);
};
