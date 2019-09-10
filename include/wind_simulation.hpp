//
// Created by Peterek, Filip on 10/09/2019.
//

#ifndef AIRPORT_CPP_WIND_SIMULATION_HPP
#define AIRPORT_CPP_WIND_SIMULATION_HPP


#include <cstdint>

/*************************/
/*                       */
/*          180°         */
/*           ^           */
/*           |           */
/*    90° <--|--> 270°   */
/*           |           */
/*           ˇ           */
/*        0°/360°        */
/*                       */
/*************************/


class WindSimulation {

    int64_t windDirection = 0; // Direction in degrees
    uint64_t windSpeed = 0; // Speed in knots

    enum class ChangeDirection {
        Up = 1,
        Down = -1
    };

    static const uint64_t ticksPerDay = 60 * 60 * 60 * 24; // 60 ticks per second

    void checkDirBounds();
    void changeWindDir();
    void changeWindVelocity();

public:

    void update();
    uint64_t speed();
    int64_t direction();

};


#endif //AIRPORT_CPP_WIND_SIMULATION_HPP
