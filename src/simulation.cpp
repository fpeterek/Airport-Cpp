//
// Created by Peterek, Filip on 2019-08-12.
//

#include <SFML/Window/Event.hpp>
#include <iostream>

#include "random.hpp"
#include "simulation.hpp"

void Simulation::initBackground() {
    background.setScale(scale, scale);
    background.setTexture(backgroundTexture);
}

void Simulation::loadTexture(const std::string & texture) {
    sf::Texture tx;
    tx.loadFromFile("resources/sprites/" + texture + ".png");
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
    textureList = loadList(filename);
}

void Simulation::loadTemplates() {

    AircraftTemplateParser atp;

    for (const std::string & tmpl : templateList) {
        templates[tmpl] = atp.parseFile("resources/aircraft/" + tmpl + ".ac");
    }

}

void Simulation::loadTemplateList(const std::string & filename) {
    templateList = loadList(filename);
}

std::vector<std::string> Simulation::loadList(const std::string & filename) {

    std::ifstream is(filename);

    if (not is) {
        throw std::runtime_error("Could not open file " + filename);
    }

    std::vector<std::string> list;

    while (not is.eof()) {
        std::string line;
        std::getline(is, line);
        if (not line.empty()) {
            list.emplace_back(line);
        }
    }

    return list;

}

void Simulation::initTextures() {
    backgroundTexture.loadFromFile("resources/kxb-airport.png");
    backgroundTexture.setSmooth(true);
    loadTextureList("resources/textures.txt");
    loadAircraftTextures();
}

void Simulation::initTemplates() {
    loadTemplateList("resources/aircraft.txt");
    loadTemplates();
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
    initTemplates();
    calcScale();
    initBackground();

    width = window.getSize().x;
    height = window.getSize().y;
    removalBound = width / 2;
}

void Simulation::update() {

    if (aircraftLimit > aircraft.size() and Random::randUInt(0, 99) <= chance) {
       randomAircraft();
    }

    for (Aircraft & a : aircraft) {
        a.update();
    }

    removeDistantAircraft();

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

        if (event.type == sf::Event::MouseButtonPressed) {
            return onMouseDown(event.mouseButton);
        }

        if (event.type == sf::Event::MouseWheelScrolled) {
            return onMouseScroll(event.mouseWheelScroll);
        }

    }

}

void Simulation::onMouseDown(const sf::Event::MouseButtonEvent event) {

    if (event.button == sf::Mouse::Left) {
        selectAircraft(event.x, event.y);
    }
    if (event.button == sf::Mouse::Right) {
        moveAircraft(event.x, event.y);
    }

}

void Simulation::onMouseScroll(const sf::Event::MouseWheelScrollEvent event) {

    float delta = event.delta;
    bool isNeg = delta > 0;
    int64_t calcDelta = (int64_t)(std::ceil(std::abs(delta)) * 10) / 10 * (isNeg ? 5 : -5);
    changeAircraftVelocity(calcDelta);

}

void Simulation::changeAircraftVelocity(const int64_t delta) {
    if (not aircraftSelected()) {
        return;
    }
    selected().changeVelocityBy(delta);
}

void Simulation::onKeyPress(const sf::Keyboard::Key key) {
    switch(key) {
        case sf::Keyboard::Escape:
            window.close();
            break;
        default:
            break;
    }
}

void Simulation::randomAircraft() {

    std::string tmplStr = templateList[Random::randUInt(0, templateList.size() - 1)];
    const AircraftTemplate & tmpl = templates.at(tmplStr);

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

    const int64_t velocity = Random::randInt(tmpl.vLanding, tmpl.vMax);

    aircraft.emplace_back(Aircraft::fromTemplate(tmpl, aircraftTextures, scale));
    Aircraft & ac = aircraft.back();
    ac.setPosition(x, y);
    ac.setHeading(heading);
    ac.setVelocity(velocity);

}

void Simulation::removeDistantAircraft(const size_t index) {

    if (index >= aircraft.size()) {
        return;
    }

    if (index == selectedIndex) {
        return removeDistantAircraft(index + 1);
    }

    const Aircraft & ac = aircraft[index];
    const int64_t x = ac.getPosition().x;
    const int64_t y = ac.getPosition().y;

    const bool xCond = (x < -removalBound) or ((int64_t)width + removalBound < x);
    const bool yCond = (y < -removalBound) or ((int64_t)height + removalBound < y);

    if (xCond or yCond) {
        if (aircraftSelected() and index < selectedIndex) {
            --selectedIndex;
        }
        aircraft.erase(aircraft.begin() + index);
        return removeDistantAircraft(index);
    }

    removeDistantAircraft(index + 1);

}

void Simulation::selectAircraft(int64_t x, int64_t y) {

    for (size_t i = 0; i < aircraft.size(); ++i) {
        if (aircraft[i].contains(x, y)) {
            return selectAircraft(i);
        }
    }

    deselectAircraft();

}

void Simulation::selectAircraft(const size_t i) {
    if (selectedIndex == i) {
        return;
    }
    deselectAircraft();
    aircraft[i].select();
    selectedIndex = i;
}

void Simulation::deselectAircraft() {
    if (aircraftSelected()) {
        selected().deselect();
        selectedIndex = noAircraftSelected;
    }
}

void Simulation::moveAircraft(int64_t x, int64_t y) {

    if (not aircraftSelected()) {
        return;
    }

    selected().setPosition(x, y);

}

bool Simulation::aircraftSelected() {
    return selectedIndex != noAircraftSelected;
}

Aircraft & Simulation::selected() {
    if (not aircraftSelected()) {
        throw std::runtime_error("Attempting to access selected aircraft when no aircraft is selected");
    }
    return aircraft[selectedIndex];
}


