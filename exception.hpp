#pragma once

#include <exception>

namespace exception {
    class FileOpeningException : public std::exception {
        const char* str;
    public:
        explicit FileOpeningException(const char* str) : str(str) {
        }

        [[nodiscard]] const char* what() const noexcept override {
            return str;
        }
    };

    class FileReadException : public std::exception {
    public:
        explicit FileReadException() = default;

        [[nodiscard]] const char* what() const noexcept override {
            return "Error: could not read file";
        }
    };

    class FileWriteException : public std::exception {
    public:
        explicit FileWriteException() = default;

        [[nodiscard]] const char* what() const noexcept override {
            return "Error: could not write to file";
        }
    };
}  // namespace exception
