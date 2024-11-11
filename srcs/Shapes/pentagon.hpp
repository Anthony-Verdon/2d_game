#pragma once

#include <vector>                                         

#define PENTAGON_VERTICES std::vector<float> {  \
            0, -0.5,                            \
          0.5,    0,                            \
         0.25,  0.5,                            \
        -0.25,  0.5,                            \
         -0.5,    0,                            \
}

#define PENTAGON_FACES std::vector<int>{      \
       3, 0, 4,                               \
       3, 1, 0,                               \
       3, 2, 1                                \
}   