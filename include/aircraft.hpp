//
// Created by Peterek, Filip on 2019-08-12.
//

#ifndef AIRPORTSIM_AIRCRAFT_HPP
#define AIRPORTSIM_AIRCRAFT_HPP

#include <functional>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "aircraft_template.hpp"

class Aircraft: protected sf::Sprite {

    std::reference_wrapper<const sf::Texture> yellow;
    std::reference_wrapper<const sf::Texture> red;

    bool selected = false;

    int64_t velocity = 0;
    float desiredRotation = 0.f;
    float maxRotation = 3.5f;

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
