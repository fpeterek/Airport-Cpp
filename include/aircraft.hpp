//
// Created by Peterek, Filip on 2019-08-12.
//

#ifndef AIRPORTSIM_AIRCRAFT_HPP
#define AIRPORTSIM_AIRCRAFT_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Aircraft: protected sf::Sprite {

    const sf::Texture & yellow;
    const sf::Texture & red;

    bool selected = false;

    uint64_t velocity = 0;
    float desiredRotation = 0.f;
    float maxRotation = 3.5f;

    void rotateAircraft();

public:

    Aircraft(const sf::Texture & yellow, const sf::Texture & red);

    void update();


};

#endif //AIRPORTSIM_AIRCRAFT_HPP
