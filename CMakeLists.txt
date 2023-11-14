cmake_minimum_required(VERSION 3.24)
project(HSE_CPP)

set(CMAKE_CXX_FLAGS "-O2 -lm -Wall -Werror -fsanitize=leak,address,undefined -m64 -D_GNU_SOURCE -MD -MT -fno-sanitize-recover=all")
set(CMAKE_CXX_STANDARD 17)
add_executable(image_processor image_processor.cpp pixel.cpp pixel.hpp picture.cpp matrix.hpp filter.hpp filter.cpp crop_filter.cpp crop_filter.hpp grayscale_filter.cpp grayscale_filter.hpp negative_filter.cpp negative_filter.hpp blur_filter.cpp blur_filter.hpp picture.hpp matrix_filter.cpp exception.hpp matrix_filter.hpp sharpening_filter.cpp sharpening_filter.hpp edge_filter.cpp edge_filter.hpp constants.hpp pixellate_filter.cpp pixellate_filter.hpp parser.cpp parser.hpp)
