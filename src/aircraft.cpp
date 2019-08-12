//
// Created by Peterek, Filip on 2019-08-12.
//

#include <cmath>

#include "aircraft.hpp"

Aircraft::Aircraft(const sf::Texture & yellow, const sf::Texture & red) : yellow(yellow), red(red) {
    setOrigin(getPosition().x / 2, getPosition().y / 2);
}



void Aircraft::update() {

    const float heading = getRotation();
    const sf::Vector2f current = getPosition();
    const float x = current.x + (std::cos(heading) * velocity / 350);
    const float y = current.y + (std::cos(heading) * velocity / 350);

    setPosition(x, y);

}

void Aircraft::rotateAircraft() {

    if (desiredRotation == 0) {
        return;
    }

    float rotation = getRotation();

    if (desiredRotation < maxRotation) {
        rotation += desiredRotation;
        desiredRotation = 0;
    } else {
        rotation += maxRotation;
        desiredRotation -= maxRotation;
    }

    setRotation(rotation);

}

