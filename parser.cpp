#include "parser.hpp"
#include "constants.hpp"

Parser::Parser(int argc, char* argv[]) {
    in = nullptr;
    out = nullptr;
    filters = {};
    if (argc < 3) {
        throw std::invalid_argument("Error: too few arguments");
    }
    in = argv[1];
    out = argv[2];
    for (int i = 3; i < argc; ++i) {
        std::string cmd(argv[i]);
        if (cmd == "-gs") {
            filters.emplace_back(GrayscaleFilter(), GRAYSCALE);
        } else if (cmd == "-neg") {
            filters.emplace_back(NegativeFilter(), NEGATIVE);
        } else if (cmd == "-sharp") {
            filters.emplace_back(SharpeningFilter(), SHARP);
        } else if (cmd == "-edge" && i < argc - 1) {
            char* eptr = nullptr;
            double threshold = strtod(argv[++i], &eptr);
            if (*eptr || eptr == argv[i]) {
                throw std::invalid_argument("Error: invalid command line argument" + std::string(argv[i]));
            }
            filters.emplace_back(EdgeFilter(threshold), EDGE);
        } else if (cmd == "-blur" && i < argc - 1) {
            char* eptr = nullptr;
            double blur = strtod(argv[++i], &eptr);
            if (*eptr || eptr == argv[i]) {
                throw std::invalid_argument("Error: invalid command line argument" + std::string(argv[i]));
            }
            filters.emplace_back(BlurFilter(blur), BLUR);
        } else if (cmd == "-crop" && i < argc - 2) {
            char* eptr = nullptr;
            ssize_t crop_height = strtoll(argv[++i], &eptr, DIGITS::DIGITS_DECIMAL);
            if (*eptr || eptr == argv[i]) {
                throw std::invalid_argument("Error: invalid command line argument" + std::string(argv[i]));
            }
            eptr = nullptr;
            ssize_t crop_width = strtoll(argv[++i], &eptr, DIGITS::DIGITS_DECIMAL);
            if (*eptr || eptr == argv[i]) {
                throw std::invalid_argument("Error: invalid command line argument" + std::string(argv[i]));
            }
            filters.emplace_back(CropFilter(crop_height, crop_width), CROP);
        } else if (cmd == "-pixellate" && i < argc - 2) {
            char* eptr = nullptr;
            ssize_t pixellate_height = strtoll(argv[++i], &eptr, DIGITS::DIGITS_DECIMAL);
            if (*eptr || eptr == argv[i]) {
                throw std::invalid_argument("Error: invalid command line argument" + std::string(argv[i]));
            }
            eptr = nullptr;
            ssize_t pixellate_width = strtoll(argv[++i], &eptr, DIGITS::DIGITS_DECIMAL);
            if (*eptr || eptr == argv[i]) {
                throw std::invalid_argument("Error: invalid command line argument" + std::string(argv[i]));
            }
            filters.emplace_back(PixellateFilter(pixellate_height, pixellate_width), PIXELLATE);
        } else {
            throw std::invalid_argument("Error: invalid command line argument" + std::string(argv[i]));
        }
    }
}
