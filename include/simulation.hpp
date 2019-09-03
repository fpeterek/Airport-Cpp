//
// Created by Peterek, Filip on 2019-08-12.
//

#ifndef AIRPORTSIM_SIMULATION_HPP
#define AIRPORTSIM_SIMULATION_HPP

#include <unordered_map>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics.hpp>

#include "aircraft.hpp"

class Simulation {

    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite background;

    std::vector<std::string> textureList;
    std::unordered_map<std::string, sf::Texture> aircraftTextures;
    std::vector<std::string> templateList;
    std::unordered_map<std::string, AircraftTemplate> templates;

    std::vector<Aircraft> aircraft;

    static const size_t noAircraftSelected = -1;
    size_t selectedIndex = noAircraftSelected;

    float scale = 1.f;

    const uint64_t chance = 3;
    uint64_t width;
    uint64_t height;

    int64_t removalBound;
    const uint64_t aircraftLimit = 20;

    bool aircraftSelected();
    Aircraft & selected();

    void handleEvents();
    void update();
    void render();
    void randomAircraft();
    void removeDistantAircraft(size_t index = 0);

    void loadTexture(const std::string & texture);
    void loadAircraftTexturePair(const std::string & aircraft);
    void loadAircraftTextures();
    void loadTextureList(const std::string & filename);

    void loadTemplates();
    void loadTemplateList(const std::string & filename);

    static std::vector<std::string> loadList(const std::string & filename);

    void initTextures();
    void initTemplates();
    void initBackground();
    void initWindow();
    void calcScale();

    void onKeyPress(sf::Keyboard::Key key);
    void onMouseDown(sf::Event::MouseButtonEvent button);
    void onMouseScroll(sf::Event::MouseWheelScrollEvent wheel);

    void selectAircraft(int64_t x, int64_t y);
    void selectAircraft(size_t index);
    void deselectAircraft();

    void moveAircraft(int64_t x, int64_t y);
    void changeAircraftVelocity(int64_t delta);

public:

    Simulation();

    void run();

};

#endif //AIRPORTSIM_SIMULATION_HPP
