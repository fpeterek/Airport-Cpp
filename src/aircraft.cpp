//
// Created by Peterek, Filip on 2019-08-12.
//

#include <cmath>
#include <iostream>

#include "aircraft.hpp"

Aircraft::Aircraft(const sf::Texture & yellow, const sf::Texture & red) : yellow(yellow), red(red) {
    setOrigin(getPosition().x / 2, getPosition().y / 2);
    setTexture(this->yellow.get());
}



void Aircraft::update() {

    const float heading = (180 + getRotation() + 90) * M_PI / 180;
    const sf::Vector2f current = getPosition();
    const float x = current.x + std::cosf(heading) * (velocity / 350.f);
    const float y = current.y + std::sinf(heading) * (velocity / 350.f);

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

void Aircraft::setPosition(const float x, const float y) {
    sf::Sprite::setPosition(x, y);
}

void Aircraft::setHeading(const float heading) {
    setRotation(180 - heading - 90);
}

void Aircraft::setVelocity(const int64_t vc) {
    velocity = vc;
}

const sf::Sprite & Aircraft::drawable() const {
    return *((sf::Sprite*)this);
}

sf::Vector2f Aircraft::getPosition() const {
    return sf::Sprite::getPosition();
}

