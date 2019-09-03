//
// Created by Peterek, Filip on 03/09/2019.
//

#include "weight_category.hpp"

std::ostream & operator<<(std::ostream & os, WeightCategory cat) {

    std::string str;

    switch (cat) {
        case WeightCategory::Light:
            str = "Light"; break;
        case WeightCategory::Medium:
            str = "Medium"; break;
        case WeightCategory::Heavy:
            str = "Heavy"; break;
        case WeightCategory::Super:
            str = "Super"; break;
    }

    return os << str;

}
