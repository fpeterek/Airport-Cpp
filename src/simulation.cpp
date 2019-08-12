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

void Simulation::loadAircraftTextures(const std::string & aircraft) {
    loadTexture(aircraft);
    loadTexture(aircraft + "_red");
}

void Simulation::loadTexturesFromFile(const std::string & filename) {

    std::ifstream is(filename);

    if (not is) {
        throw std::runtime_error("Could not open file " + filename);
    }

    while (not is.eof()) {
        std::string line;
        std::getline(is, line);
        if (not line.empty()) {
            loadAircraftTextures(line);
        }
    }

}

void Simulation::initTextures() {
    backgroundTexture.loadFromFile("resources/kxb-airport.png");
    backgroundTexture.setSmooth(true);
    loadTexturesFromFile("resources/textures.txt");
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
}

void Simulation::update() {

    if (Random::randUInt(0, 99)) {
        randomAircraft();
    }

    for (Aircraft & a : aircraft) {
        a.update();
    }

}

void Simulation::run() {

    while (window.isOpen()) {

        handleEvents();
        update();
        render();

    }

}

void Simulation::render() {
    window.clear(sf::Color::Red);
    window.draw(background);
    window.display();
}

void Simulation::handleEvents() {

    sf::Event event;
    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            return window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            onKeyPress(event.key.code);
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


    /////////////////////////////
    //                         //
    //           (27)          //
    //            N            //
    //            |            //
    //  (18) W ---+--- E (00)  //
    //            |            //
    //            S            //
    //           (09)          //
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
        x = Random::randInt(-50, 1250);
    } else {
        if (eastbound) {
            x = -50;
        } else {
            x = 1250;
        }
    }
    int64_t y;
    if (fixedHor) {
        x = Random::randInt(-50, 850);
    } else {
        if (southbound) {
            x = -50;
        } else {
            x = 850;
        }
    }

    std::pair<uint64_t, uint64_t> hBounds;
    if (eastbound and northbound) hBounds = std::make_pair(270, 360);
    else if (eastbound && southbound) hBounds = std::make_pair(0, 90);
    else if (westbound && northbound) hBounds = std::make_pair(180, 270);
    else if (westbound && southbound) hBounds = std::make_pair(90, 180);
    else hBounds = std::make_pair(0, 360);

    const int64_t roughHeading = Random::randInt(hBounds.first * 10, hBounds.second * 10);
    const int64_t heading = (roughHeading % 3600) / 10.0;

    const int64_t velocity = Random::randInt(200, 450);

    return Airplane(sprite, x, y, heading, velocity)

}
