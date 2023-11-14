#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <variant>

#include "filter.hpp"

#include "negative_filter.hpp"
#include "grayscale_filter.hpp"
#include "sharpening_filter.hpp"
#include "edge_filter.hpp"
#include "blur_filter.hpp"
#include "crop_filter.hpp"
#include "pixellate_filter.hpp"

struct Parser {
    char* in;
    char* out;
    enum FILTERS {
        NEGATIVE,
        GRAYSCALE,
        SHARP,
        EDGE,
        CROP,
        PIXELLATE,
        BLUR
    };
    using Elem = std::pair<std::variant<NegativeFilter, GrayscaleFilter, SharpeningFilter, EdgeFilter, BlurFilter, CropFilter, PixellateFilter>, FILTERS>;

    std::list<Elem> filters;

    Parser(int argc, char* argv[]);
};
