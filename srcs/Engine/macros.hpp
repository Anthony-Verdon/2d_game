#pragma once

#include <iostream>

#define CHECK(condition, message)   \
    if (!condition)                 \
        std::cerr << __FILE__ << "(" << __LINE__ << ") : " << message << std::endl;

#define CHECK_AND_RETURN(condition, message)                                            \
    if (!condition)                                                                     \
    {                                                                                   \
        std::cerr << __FILE__ << "(" << __LINE__ << ") : " << message << std::endl;     \
        return;                                                                         \
    }