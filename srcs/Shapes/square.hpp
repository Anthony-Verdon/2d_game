#pragma once

#include <vector>

#define SQUARE_VERTICES std::vector<float> {    \
        -0.5, -0.5,                             \
         0.5, -0.5,                             \
         0.5,  0.5,                             \
        -0.5,  0.5                              \
}

#define SQUARE_FACES std::vector<int>{  \
       3, 1, 0,                         \
       3, 2, 1                          \
} 