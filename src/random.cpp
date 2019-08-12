//
// Created by Peterek, Filip on 2019-08-12.
//

#include "random.hpp"

std::mt19937_64 Random::rand = std::mt19937_64(std::random_device()());

uint64_t Random::randUInt(const uint64_t min, const uint64_t max) {

    std::uniform_int_distribution<uint64_t> dist(min, max);
    return dist(rand);

}

bool Random::randBool() {
    return randUInt(0, 1);
}

int64_t Random::randInt(const int64_t min, const int64_t max) {

    std::uniform_int_distribution<uint64_t> dist(min, max);
    return dist(rand);

}
