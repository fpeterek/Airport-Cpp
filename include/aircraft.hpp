//
// Created by Peterek, Filip on 2019-08-12.
//

#ifndef AIRPORTSIM_AIRCRAFT_HPP
#define AIRPORTSIM_AIRCRAFT_HPP

#include <functional>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "aircraft_template.hpp"
#include "aircraft_base.hpp"

class Aircraft: protected sf::Sprite, protected AircraftBase {

    std::reference_wrapper<const sf::Texture> yellow;
    std::reference_wrapper<const sf::Texture> red;

    bool selected = false;

    int64_t velocity = 0;
    float desiredRotation = 0.f;
    float maxRotation = 3.5f;

    void rotateAircraft();

    Aircraft(const sf::Texture & yellow, const sf::Texture & red, float scale);

public:

    static Aircraft fromTemplate(const AircraftTemplate &tmpl,
                                 const std::unordered_map<std::string, sf::Texture> &textures, float scale);

    void update();
    void setPosition(float x, float y);
    void setHeading(float heading);
    void setVelocity(int64_t velocity);
    void changeVelocityBy(int64_t delta);

    void select();
    void deselect();
    bool isSelected() const;

    bool contains(float x, float y) const;

    sf::Vector2f getPosition() const;

    const sf::Sprite & drawable() const;
};

#endif //AIRPORTSIM_AIRCRAFT_HPP
