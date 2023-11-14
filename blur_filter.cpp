#include "blur_filter.hpp"
#include <cmath>
#include "constants.hpp"

double Gaussian(double x, double sigma) {
    return std::exp(-std::pow(x, 2) / 2 / sigma / sigma) / std::sqrt(2 * M_PI) / sigma;
}

BlurFilter::BlurFilter(double sigma) : sigma_(sigma) {
}

Picture BlurFilter::operator()(const Picture& pic) const {
    std::vector<double> kernel{};
    double sum = 0;
    ssize_t kernel_size = static_cast<ssize_t>(BLUR_DELTA * sigma_) + 1;
    for (size_t i = 0; i < static_cast<size_t>(kernel_size); ++i) {
        double x = Gaussian(static_cast<double>(i), sigma_);
        kernel.push_back(x);
        sum += x;
    }
    sum -= kernel[0];
    sum *= 2;
    sum += kernel[0];
    for (auto& elem: kernel) {
        elem /= sum;
    }
    Picture res = pic;
    for (ssize_t x0 = 0; static_cast<size_t>(x0) < res.Height(); ++x0) {
        for (ssize_t y0 = 0; static_cast<size_t>(y0) < res.Width(); ++y0) {
            Pixel p = {0.0, 0.0, 0.0};
            for (ssize_t x = x0 - kernel_size; x <= x0 + kernel_size; ++x) {
                ssize_t index = std::max(0L, std::min(static_cast<ssize_t>(res.Height() - 1), x));
                p += pic[{index, y0}] * kernel[std::abs(x - x0)];
                if (p > Pixel(1)) {
                    p = Pixel(1);
                    break;
                }
            }
            res[{x0, y0}] = p;
            if (res[{x0, y0}] > Pixel(1)) {
                res[{x0, y0}] = Pixel(1);
            }
        }
    }
    Picture res_res = res;
    for (ssize_t x0 = 0; static_cast<size_t>(x0) < res.Height(); ++x0) {
        for (ssize_t y0 = 0; static_cast<size_t>(y0) < res.Width(); ++y0) {
            Pixel p = {0.0, 0.0, 0.0};
            for (ssize_t y = y0 - kernel_size; y <= y0 + kernel_size; ++y) {
                ssize_t index = std::max(0L, std::min(static_cast<ssize_t>(res.Width() - 1), y));
                p += res[{x0, index}] * kernel[std::abs(y - y0)];
                if (p > Pixel(1)) {
                    p = Pixel(1);
                    break;
                }
            }
            res_res[{x0, y0}] = p;
            if (res_res[{x0, y0}] > Pixel(1)) {
                res_res[{x0, y0}] = Pixel(1);
            }
        }
    }
    return res_res;
}
