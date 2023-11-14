#include "pixel.hpp"
#include <algorithm>
#include "constants.hpp"

const static double EPS = 0.001;

Pixel::Pixel(double red, double green, double blue) : red(red), green(green), blue(blue) {
}

Pixel::Pixel(uint8_t red, uint8_t green, uint8_t blue)
        : red(static_cast<double>(red) / BYTE_TO_DOUBLE_COEF),
          green(static_cast<double>(green) / BYTE_TO_DOUBLE_COEF),
          blue(static_cast<double>(blue) / BYTE_TO_DOUBLE_COEF) {
}

Pixel Pixel::operator+(const Pixel& other) const {
    return {red + other.red, green + other.green, blue + other.blue};
}

Pixel& Pixel::operator+=(const Pixel& other) {
    return *this = *this + other;
}

Pixel Pixel::operator-() const {
    return {1 - red, 1 - green, 1 - blue};
}

Pixel Pixel::operator*(double k) const {
    return {red * k, green * k, blue * k};
}

Pixel& Pixel::operator*=(double k) {
    return *this = *this * k;
}

Pixel::Pixel(double gray_shade) {
    red = green = blue = gray_shade;
}

bool Pixel::operator==(const Pixel& other) const {
    if (std::abs(red - other.red) >= EPS) {
        return false;
    }
    if (std::abs(green - other.green) >= EPS) {
        return false;
    }
    if (std::abs(blue - other.blue) >= EPS) {
        return false;
    }
    return true;
}

bool Pixel::operator>(const Pixel& other) const {
    return (red + green + blue) > (other.red + other.green + other.blue);
}

std::ostream& operator<<(std::ostream& out, const Pixel& p) {
    return out << "(" << p.red << " " << p.green << " " << p.blue << ")";
}

Pixel Pixel::operator/(double k) const {
    return {red / k, green / k, blue / k};
}

Pixel& Pixel::operator/=(double k) {
    return *this = *this / k;
}
