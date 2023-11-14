#pragma once

#include "pixel.hpp"
#include "matrix.hpp"
#include <cinttypes>
#include "constants.hpp"

class Picture {
    uint8_t header_[BMP_INFO::BMP_HEADER_SIZE];
    uint8_t info_header_[BMP_INFO::BMP_INFO_HEADER_SIZE];
    size_t size_;
    Matrix<Pixel> body_;
    int64_t padding_amount_;

public:
    Picture() = delete;

    Picture(const Picture& other) = default;

    explicit Picture(const char* filename);

    void WriteFile(const char* filename) const;

    [[nodiscard]] size_t Height() const;

    [[nodiscard]] size_t Width() const;

    Pixel operator[](std::pair<size_t, size_t> index) const;

    Pixel& operator[](std::pair<size_t, size_t> index);

    void Resize(size_t new_height, size_t new_width);
};
