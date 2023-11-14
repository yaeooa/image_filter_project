#include "sharpening_filter.hpp"

const double CENTRAL_CELL = 5;

static Matrix<double> SharpeningMatrix() {
    Matrix<double> res(3, 3);
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            if (i == 1 && j == 1) {
                res[{i, j}] = CENTRAL_CELL;
            } else if ((i + j) % 2 == 0) {
                res[{i, j}] = 0;
            } else {
                res[{i, j}] = -1;
            }
        }
    }
    return res;
}

SharpeningFilter::SharpeningFilter() : MatrixFilter(SharpeningMatrix()) {
}
