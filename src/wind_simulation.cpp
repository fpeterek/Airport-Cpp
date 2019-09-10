//
// Created by Peterek, Filip on 10/09/2019.
//

#include "wind_simulation.hpp"

void WindSimulation::checkDirBounds() {

    if (windDirection < 0) {
        windDirection += 360;
    } else if (windDirection >= 360) {
        windDirection -= 360;
    }

}

uint64_t WindSimulation::speed() {
    return windSpeed;
}

int64_t WindSimulation::direction() {
    return windDirection;
}
