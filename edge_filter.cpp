#include "edge_filter.hpp"
#include "grayscale_filter.hpp"

static Matrix<double> EdgeMatrix() {
    Matrix<double> res(3, 3);
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            if (i == 1 && j == 1) {
                res[{i, j}] = 4;
            } else if ((i + j) % 2 == 0) {
                res[{i, j}] = 0;
            } else {
                res[{i, j}] = -1;
            }
        }
    }
    return res;
}

EdgeFilter::EdgeFilter(double threshold) : MatrixFilter(EdgeMatrix()), threshold_(threshold) {
}

Picture EdgeFilter::operator()(const Picture& pic) const {
    Picture res = GrayscaleFilter()(pic);
    res = MatrixFilter::operator()(res);
    for (size_t i = 0; i < pic.Height(); ++i) {
        for (size_t j = 0; j < pic.Width(); ++j) {
            if (res[{i, j}] > Pixel(threshold_)) {
                res[{i, j}] = Pixel(1);
            } else {
                res[{i, j}] = Pixel(0);
            }
        }
    }
    return res;
}
