#pragma once

#include "picture.hpp"

class Filter {
public:
    virtual Picture operator()(const Picture& pic) const;

    virtual ~Filter() = default;
};
