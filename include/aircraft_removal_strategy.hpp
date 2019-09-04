//
// Created by Peterek, Filip on 04/09/2019.
//

#ifndef AIRPORT_CPP_AIRCRAFT_REMOVAL_STRATEGY_HPP
#define AIRPORT_CPP_AIRCRAFT_REMOVAL_STRATEGY_HPP

#include <vector>

#include "aircraft.hpp"

class Simulation;

class AircraftRemovalStrategy {

    const size_t noAircraftSelected = -1;
    std::vector<Aircraft> & aircraftMutable;
    size_t & selectedIndexMutable;

protected:

    const std::vector<Aircraft> & aircraft;
    const size_t & selectedIndex;
    const int64_t width;
    const int64_t height;
    const int64_t removalBound;

    AircraftRemovalStrategy(std::vector<Aircraft> & aircraft, size_t & selectedIndex, int64_t width, int64_t height);

    bool aircraftSelected();
    bool subjectForRemoval(const Aircraft & ac);
    void adjustSelected(int64_t indexOfRemoved);
    void removeAtIndex(size_t index);

    virtual void remove() = 0;
    virtual bool conditionForRemoval() = 0;

public:

    void removeDistantAircraft();
    virtual ~AircraftRemovalStrategy() = default;

};

class ProgressiveRemovalStrategy : public AircraftRemovalStrategy {

    friend Simulation;

    size_t removalIndex = 0;

    ProgressiveRemovalStrategy(std::vector<Aircraft> & aircraft, size_t & selectedIndex, int64_t width, int64_t height);

    void remove() override;
    bool conditionForRemoval() override;

public:

    ~ProgressiveRemovalStrategy() override = default;

};

class PeriodicalCheckStrategy : public AircraftRemovalStrategy {

    friend Simulation;

    const uint64_t period;
    uint64_t counter;

    PeriodicalCheckStrategy(std::vector<Aircraft> & aircraft, size_t & selectedIndex, int64_t width, int64_t height,
                            uint64_t period);

    void remove() override;
    bool conditionForRemoval() override;
    void removeRecursively(size_t index = 0);

public:

    ~PeriodicalCheckStrategy() override = default;

};

#endif //AIRPORT_CPP_AIRCRAFT_REMOVAL_STRATEGY_HPP
