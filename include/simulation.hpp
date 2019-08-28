//
// Created by Peterek, Filip on 2019-08-12.
//

#ifndef AIRPORTSIM_SIMULATION_HPP
#define AIRPORTSIM_SIMULATION_HPP

#include <unordered_map>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "aircraft.hpp"

class Simulation {

    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite background;

    std::vector<std::string> textureList;
    std::unordered_map<std::string, sf::Texture> aircraftTextures;
    std::vector<Aircraft> aircraft;

    float scale = 1.f;

    const uint64_t chance = 3;
    uint64_t width;
    uint64_t height;

    int64_t removalBound;
    const uint64_t aircraftLimit = 20;

    void handleEvents();
    void update();
    void render();
    void randomAircraft();
    void removeDistantAircraft();

    void loadTexture(const std::string & texture);
    void loadAircraftTexturePair(const std::string & aircraft);
    void loadAircraftTextures();
    void loadTextureList(const std::string & filename);

    void initTextures();
    void initBackground();
    void initWindow();
    void calcScale();

    void onKeyPress(sf::Keyboard::Key key);
    void onMouseDown(sf::Mouse::Button button);
    void onMouseScroll(sf::Mouse::Wheel wheel);

public:

    Simulation();

    void run();

};

#endif //AIRPORTSIM_SIMULATION_HPP
