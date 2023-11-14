#pragma once

enum BMP_INFO {
    BMP_HEADER_SIZE = 14, BMP_INFO_HEADER_SIZE = 40
};

enum DIGITS {
    DIGITS_DECIMAL = 10
};

const double BLUR_DELTA = 3.0;
const double GRAYSCALE_RED_COEF = 0.299;
const double GRAYSCALE_GREEN_COEF = 0.587;
const double GRAYSCALE_BLUE_COEF = 0.114;

const double BYTE_TO_DOUBLE_COEF = 255.0;
