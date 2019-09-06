//
// Created by Peterek, Filip on 2019-08-12.
//

#include <cmath>

#include "aircraft.hpp"

Aircraft::Aircraft(const sf::Texture & yellow, const sf::Texture & red, const float scale) : yellow(yellow), red(red) {
    setScale(scale * 1.5, scale * 1.5);
    setTexture(this->yellow.get());
    setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
}



void Aircraft::update() {

    const float heading = (180 + getRotation() + 90) * M_PI / 180;
    const sf::Vector2f current = getPosition();
    const float x = current.x + std::cos(heading) * (velocity / 350.f);
    const float y = current.y + std::sin(heading) * (velocity / 350.f);

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

void Aircraft::select() {
    selected = true;
    setTexture(red);
}

void Aircraft::deselect() {
    selected = false;
    setTexture(yellow);
}

bool Aircraft::isSelected() const {
    return selected;
}

bool Aircraft::contains(const float x, const float y) const {
    return getGlobalBounds().contains(x, y);
}

void Aircraft::changeVelocityBy(int64_t delta) {
    velocity += delta;
    if (velocity > vMax) {
        velocity = vMax;
    }
    if (velocity < vStall) {
        velocity = vStall;
    }
}

Aircraft Aircraft::fromTemplate(const AircraftTemplate & tmpl,
        const std::unordered_map<std::string, sf::Texture> & textures, const float scale) {

    Aircraft ac(textures.at(tmpl.sprite), textures.at(tmpl.spriteSelected), scale);

    AircraftBase & base = ac;
    base = (AircraftBase)tmpl;

    return ac;

}

