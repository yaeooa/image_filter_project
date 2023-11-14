#pragma once

#include <cinttypes>
#include <cmath>
#include <iostream>

struct Pixel {
    double red, green, blue;

    Pixel() = default;

    explicit Pixel(double gray_shade);

    Pixel(double red, double green, double blue);

    Pixel(uint8_t red, uint8_t green, uint8_t blue);

    Pixel(const Pixel& other) = default;

    Pixel(Pixel&& other) = default;

    [[nodiscard]] Pixel operator+(const Pixel& other) const;

    Pixel& operator=(const Pixel& other) = default;

    Pixel& operator+=(const Pixel& other);

    Pixel operator-() const;

    [[nodiscard]] Pixel operator*(double k) const;

    Pixel& operator*=(double k);

    [[nodiscard]] Pixel operator/(double k) const;

    Pixel& operator/=(double k);

    bool operator==(const Pixel& other) const;

    bool operator>(const Pixel& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Pixel& p);
};
