#include "matrix_filter.hpp"

Picture MatrixFilter::operator()(const Picture& pic) const {
    Picture res = pic;
    for (ssize_t i = 0; i < static_cast<ssize_t>(pic.Height()); ++i) {
        for (ssize_t j = 0; j < static_cast<ssize_t>(pic.Width()); ++j) {
            Pixel p{0.0, 0.0, 0.0};
            for (ssize_t index1 = -1; index1 <= 1; ++index1) {
                for (ssize_t index2 = -1; index2 <= 1; ++index2) {
                    ssize_t i0 = i + index1;
                    ssize_t j0 = j + index2;
                    if (i0 < 0) {
                        i0 = 0;
                    }
                    if (i0 >= static_cast<ssize_t>(pic.Height())) {
                        i0 = static_cast<ssize_t>(pic.Height() - 1);
                    }
                    if (j0 < 0) {
                        j0 = 0;
                    }
                    if (j0 >= static_cast<ssize_t>(pic.Width())) {
                        j0 = static_cast<ssize_t>(pic.Width() - 1);
                    }
                    p += pic[{i0, j0}] * matrix_[{1 + index1, 1 + index2}];
                }
            }
            p.red = std::min(1.0, std::max(0.0, p.red));
            p.green = std::min(1.0, std::max(0.0, p.green));
            p.blue = std::min(1.0, std::max(0.0, p.blue));
            res[{i, j}] = p;
        }
    }
    return res;
}

MatrixFilter::MatrixFilter(const Matrix<double>& matrix) : matrix_(matrix) {
}
