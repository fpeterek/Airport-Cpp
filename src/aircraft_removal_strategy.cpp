//
// Created by Peterek, Filip on 04/09/2019.
//

#include "aircraft_removal_strategy.hpp"


AircraftRemovalStrategy::AircraftRemovalStrategy(
        std::vector<Aircraft> & aircraft, size_t & selectedIndex, const int64_t width, const int64_t height) :
            aircraft(aircraft),
            selectedIndex(selectedIndex),
            width(width),
            height(height),
            removalBound(std::max(width, height) / 2) { }

bool AircraftRemovalStrategy::aircraftSelected() {
    return selectedIndex != noAircraftSelected;
}

void AircraftRemovalStrategy::removeDistantAircraft() {

    if (aircraft.empty()) {
        return;
    }

    if (conditionForRemoval()) {
        remove();
    }

}

bool AircraftRemovalStrategy::subjectForRemoval(const Aircraft &ac) {

    const int64_t x = ac.getPosition().x;
    const int64_t y = ac.getPosition().y;

    const bool xCond = (x < -removalBound) or ((int64_t)width + removalBound < x);
    const bool yCond = (y < -removalBound) or ((int64_t)height + removalBound < y);

    return xCond or yCond;

}

void AircraftRemovalStrategy::adjustSelected(const int64_t indexOfRemoved) {
    if (aircraftSelected() and indexOfRemoved < selectedIndex) {
        --selectedIndex;
    }
}

void AircraftRemovalStrategy::removeAtIndex(size_t index) {
    aircraft.erase(aircraft.begin() + index);
    adjustSelected(index);
}


ProgressiveRemovalStrategy::ProgressiveRemovalStrategy(
        std::vector<Aircraft> & aircraft, size_t & selectedIndex, const int64_t width, const int64_t height)
        : AircraftRemovalStrategy(aircraft, selectedIndex, width, height) { }

void ProgressiveRemovalStrategy::remove() {

    if (removalIndex >= aircraft.size()) {
        removalIndex = 0;
    }

    if (subjectForRemoval(aircraft[removalIndex])) {
        removeAtIndex(removalIndex);
    }

    ++removalIndex;

}

bool ProgressiveRemovalStrategy::conditionForRemoval() {

    if (removalIndex == selectedIndex) {
        ++removalIndex;
        return false;
    }

    return true;
}

PeriodicalCheckStrategy::PeriodicalCheckStrategy(
        std::vector<Aircraft> & aircraft, size_t & selectedIndex, const int64_t width, const int64_t height,
        const uint64_t period) :
        AircraftRemovalStrategy(aircraft, selectedIndex, width, height), period(period - 1) {

    counter = period;

}

void PeriodicalCheckStrategy::removeRecursively(size_t index) {

    if (index >= aircraft.size()) {
        return;
    }

    if (index == selectedIndex) {
        return removeRecursively(index + 1);
    }

    if (subjectForRemoval(aircraft[index])) {
        removeAtIndex(index);
        return removeRecursively(index);
    }

    removeRecursively(index + 1);

}

void PeriodicalCheckStrategy::remove() {
    removeRecursively();
}

bool PeriodicalCheckStrategy::conditionForRemoval() {

    if (period == -1) {
        return false;
    }

    if (not --counter) {
        counter = period;
        return true;
    }

    return false;

}
