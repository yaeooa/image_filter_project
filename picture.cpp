#include "picture.hpp"
#include <unistd.h>
#include <fstream>
#include "exception.hpp"
#include <iostream>
#include <climits>

Picture::Picture(const char* filename) {
    std::ifstream in;
    in.open(filename, std::ios::in | std::ios::binary);
    if (!in.is_open()) {
        throw exception::FileOpeningException(filename);
    }
    try {
        in.read(reinterpret_cast<char*>(header_), sizeof(header_));
        if (in.tellg() != sizeof(header_)) {
            std::cerr << "header_" << std::endl;
            throw exception::FileReadException();
        }
        in.read(reinterpret_cast<char*>(info_header_), sizeof(info_header_));
        if (in.tellg() != sizeof(header_) + sizeof(info_header_)) {
            std::cerr << "info_header_" << std::endl;
            throw exception::FileReadException();
        }
    } catch (const std::ios_base::failure& fail) {
        std::cerr << fail.what() << std::endl;
        std::cerr << "body_" << std::endl;
        throw exception::FileReadException();
    }
    int bits[4];
    for (int i = 0; i < 4; ++i) {
        bits[i] = i * CHAR_BIT;
    }
    size_t width = 0;
    size_t height = 0;
    for (size_t i = 2; i < sizeof(int) + 1; ++i) {
        size_ += (header_[i] << bits[i - 2]);
        width += (info_header_[i + 2] << bits[i - 2]);
        height += (info_header_[i + 2 + sizeof(int)] << bits[i - 2]);
    }
    body_ = Matrix<Pixel>(height, width);
    padding_amount_ = ((4 - (static_cast<int64_t>(width) * 3) % 4) % 4);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            uint8_t pixel[3];
            in.read(reinterpret_cast<char*>(pixel), sizeof(pixel[0]) * 3);
            std::pair<size_t, size_t> index = {i, j};
            body_[index] = {pixel[2] / BYTE_TO_DOUBLE_COEF, pixel[1] / BYTE_TO_DOUBLE_COEF,
                            pixel[0] / BYTE_TO_DOUBLE_COEF};
        }
        in.ignore(padding_amount_);
    }
    in.close();
}

void Picture::WriteFile(const char* filename) const {
    // Print();
    std::ofstream out;
    out.open(filename, std::ios::out | std::ios::binary);
    if (!out.is_open()) {
        throw exception::FileOpeningException(filename);
    }
    auto padding = new unsigned char[((4 - (Width() * 3) % 4) % 4)];
    out.write(reinterpret_cast<const char*>(header_), sizeof(header_));
    out.write(reinterpret_cast<const char*>(info_header_), sizeof(info_header_));
    for (size_t i = 0; i < Height(); ++i) {
        for (size_t j = 0; j < Width(); ++j) {
            std::pair<size_t, size_t> index = {i, j};
            uint8_t red = static_cast<uint8_t>(body_[index].red * BYTE_TO_DOUBLE_COEF);
            uint8_t green = static_cast<uint8_t>(body_[index].green * BYTE_TO_DOUBLE_COEF);
            uint8_t blue = static_cast<uint8_t>(body_[index].blue * BYTE_TO_DOUBLE_COEF);
            uint8_t pixel[3] = {blue, green, red};
            out.write(reinterpret_cast<char*>(pixel), sizeof(pixel));
        }
        out.write(reinterpret_cast<char*>(padding), static_cast<int64_t>((4 - (Width() * 3) % 4) % 4));
    }
    delete[] padding;
    out.close();
}

size_t Picture::Height() const {
    return body_.Rows();
}

size_t Picture::Width() const {
    return body_.Cols();
}

Pixel Picture::operator[](std::pair<size_t, size_t> index) const {
    return body_[index];
}

Pixel& Picture::operator[](std::pair<size_t, size_t> index) {
    return body_[index];
}

void Picture::Resize(size_t new_height, size_t new_width) {
    Matrix<Pixel> tmp(new_height, new_width);
    for (size_t i = 0; i < new_height; ++i) {
        for (size_t j = 0; j < new_width; ++j) {
            std::pair<size_t, size_t> index = {i, j};
            tmp[index] = body_[{Height() - new_height + i, j}];
        }
    }
    body_ = tmp;
    unsigned bits[4];
    for (size_t i = 0; i < 4; ++i) {
        bits[i] = i * CHAR_BIT;
    }
    for (size_t i = sizeof(int); i < 2 * sizeof(int); ++i) {
        info_header_[i] = static_cast<uint8_t>(new_width >> bits[i - sizeof(int)]);
    }
    for (size_t i = 2 * sizeof(int); i < 3 * sizeof(int); ++i) {
        info_header_[i] = static_cast<uint8_t>(new_height >> bits[i - 2 * sizeof(int)]);
    }
    size_ = sizeof(header_) + sizeof(info_header_) + Height() * Width() * 3 + ((4 - (Width() * 3) % 4) % 4) * Height();
    for (size_t i = 2; i < CHAR_BIT / 2 + 2; ++i) {
        header_[i] = static_cast<uint8_t>(size_ >> bits[i - 2]);
    }
}
