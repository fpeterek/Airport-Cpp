//
// Created by Peterek, Filip on 04/09/2019.
//

#ifndef AIRPORT_CPP_AIRCRAFT_BASE_HPP
#define AIRPORT_CPP_AIRCRAFT_BASE_HPP

#include <string>

struct AircraftBase {

    std::string type;
    int64_t mtow;
    int64_t maxFuel;
    int64_t maxAltitude;
    int64_t range;
    int64_t vCruise;
    int64_t vMax;
    int64_t vLanding;
    int64_t vStall;
    WeightCategory weightCategory;

};

#endif //AIRPORT_CPP_AIRCRAFT_BASE_HPP
