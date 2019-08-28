//
// Created by Peterek, Filip on 2019-08-12.
//

#include <SFML/Window/Event.hpp>
#include <iostream>
#include <fstream>
#include <random.hpp>

#include "simulation.hpp"

void Simulation::initBackground() {
    background.setScale(scale, scale);
    background.setTexture(backgroundTexture);
}

void Simulation::loadTexture(const std::string & texture) {
    sf::Texture tx;
    tx.loadFromFile("resources/" + texture + ".png");
    tx.setSmooth(true);

    aircraftTextures[texture] = tx;
}

void Simulation::loadAircraftTexturePair(const std::string & aircraft) {
    loadTexture(aircraft);
    loadTexture(aircraft + "_red");
}

void Simulation::loadAircraftTextures() {
    for (const auto & texture : textureList) {
        loadAircraftTexturePair(texture);
    }
}

void Simulation::loadTextureList(const std::string &filename) {

    std::ifstream is(filename);

    if (not is) {
        throw std::runtime_error("Could not open file " + filename);
    }

    while (not is.eof()) {
        std::string line;
        std::getline(is, line);
        if (not line.empty()) {
            textureList.emplace_back(line);
        }
    }

}

void Simulation::initTextures() {
    backgroundTexture.loadFromFile("resources/kxb-airport.png");
    backgroundTexture.setSmooth(true);
    loadTextureList("resources/textures.txt");
    loadAircraftTextures();
}

void Simulation::initWindow() {
    window.create(sf::VideoMode::getDesktopMode(), "Airport Simulation", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
}

void Simulation::calcScale() {
    const float xscale = window.getSize().x / (float)backgroundTexture.getSize().x;
    const float yscale = window.getSize().y / (float)backgroundTexture.getSize().y;
    scale = std::max(xscale, yscale);
}

Simulation::Simulation() {
    initWindow();
    initTextures();
    calcScale();
    initBackground();

    width = window.getSize().x;
    height = window.getSize().y;
    removalBound = width / 2;
}

void Simulation::update() {

    if (aircraftLimit < aircraft.size() and Random::randUInt(0, 99) <= chance) {
       randomAircraft();
    }

    for (Aircraft & a : aircraft) {
        a.update();
    }

    removeDistantAircraft();

}

void Simulation::run() {

    aircraft.emplace_back(aircraftTextures["a380"], aircraftTextures["a380_red"], scale);
    aircraft.back().setHeading(300);
    aircraft.back().setPosition(width / 2, height / 2);
    aircraft.back().setVelocity(410);

    while (window.isOpen()) {

        handleEvents();
        update();
        render();

    }

}

void Simulation::render() {
    window.clear(sf::Color::Red);
    window.draw(background);
    for (const auto & ac : aircraft) {
        window.draw(ac.drawable());
    }
    window.display();
}

void Simulation::handleEvents() {

    sf::Event event;
    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            return window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            return onKeyPress(event.key.code);
        }

    }

}

void Simulation::onMouseDown(sf::Mouse::Button button) {

}

void Simulation::onMouseScroll(sf::Mouse::Wheel wheel) {

}

void Simulation::onKeyPress(sf::Keyboard::Key key) {
    switch(key) {
        case sf::Keyboard::Escape:
            window.close();
            break;
        default:
            break;
    }
}

void Simulation::randomAircraft() {

    std::string sprite = textureList[Random::randUInt(0, textureList.size() - 1)];

    /////////////////////////////
    //                         //
    //           (09)          //
    //            N            //
    //            |            //
    //  (18) W ---+--- E (00)  //
    //            |            //
    //            S            //
    //           (27)          //
    //                         //
    /////////////////////////////

    const bool northbound = Random::randBool();
    const bool southbound = not northbound;
    const bool westbound = Random::randBool();
    const bool eastbound = not westbound;

    const bool fixedVert = Random::randBool();
    const bool fixedHor = not fixedVert;

    int64_t x;

    if (fixedVert) {
        x = Random::randInt(-(removalBound / 2), width + (removalBound / 2));
    } else {
        if (eastbound) {
            x = -(removalBound / 2);
        } else {
            x = width + (removalBound / 2);
        }
    }
    int64_t y;
    if (fixedHor) {
        y = Random::randInt(-(removalBound / 2), height + (removalBound / 2));
    } else {
        if (southbound) {
            y = -(removalBound / 2);
        } else {
            y = height + (removalBound / 2);
        }
    }

    std::pair<uint64_t, uint64_t> hBounds;
    if (eastbound and northbound) hBounds = std::make_pair(0, 90);
    else if (eastbound && southbound) hBounds = std::make_pair(270, 360);
    else if (westbound && northbound) hBounds = std::make_pair(90, 180);
    else if (westbound && southbound) hBounds = std::make_pair(180, 270);
    else hBounds = std::make_pair(0, 360);

    const int64_t roughHeading = Random::randInt(hBounds.first * 10, hBounds.second * 10);
    const int64_t heading = (roughHeading % 3600) / 10.0;

    const int64_t velocity = Random::randInt(200, 450);

    aircraft.emplace_back(aircraftTextures[sprite], aircraftTextures[sprite + "_red"], scale);
    Aircraft & ac = aircraft.back();
    ac.setPosition(x, y);
    ac.setHeading(heading);
    ac.setVelocity(velocity);

}

void Simulation::removeDistantAircraft() {

    for (auto it = aircraft.begin(); it != aircraft.end(); ++it) {
        const int64_t x = it->getPosition().x;
        const int64_t y = it->getPosition().y;

        if ((x < -removalBound) or (width + removalBound < x) or
            (y < -removalBound) or (height + removalBound < y)) {
            std::cout << "Erasing aircraft" << std::endl;
            aircraft.erase(it);
        }
    }

}
