//
// Created by Peterek, Filip on 03/09/2019.
//

#ifndef AIRPORT_CPP_WEIGHT_CATEGORY_HPP
#define AIRPORT_CPP_WEIGHT_CATEGORY_HPP

#include <ostream>

enum class WeightCategory {
    Light,
    Medium,
    Heavy,
    Super
};

std::ostream & operator<<(std::ostream & os, WeightCategory cat);

#endif //AIRPORT_CPP_WEIGHT_CATEGORY_HPP
