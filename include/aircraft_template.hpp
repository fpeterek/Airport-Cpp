//
// Created by Filip Peterek on 2019-09-01.
//

#ifndef AIRPORT_CPP_AIRCRAFT_TEMPLATE_HPP
#define AIRPORT_CPP_AIRCRAFT_TEMPLATE_HPP

#include <string>
#include <fstream>
#include <ostream>
#include <unordered_map>

enum class WeightCategory {
    Light,
    Medium,
    Heavy,
    Super
};

std::ostream & operator<<(std::ostream & os, WeightCategory cat);

struct AircraftTemplate;

class AircraftTemplateParser {

    static std::unordered_map<std::string, WeightCategory> categories;

    std::string filename;
    std::unordered_map<std::string, std::string> lines;
    std::unordered_map<std::string, uint64_t> specs;
    std::string type;
    std::pair<std::string, std::string> sprites;
    WeightCategory category;

    friend AircraftTemplate;
    AircraftTemplate createAircraft();
    AircraftTemplate createTemplate();
    std::ifstream openFile(const std::string & filename);
    void loadFile(std::ifstream & is);
    void parseLines(std::ifstream & is);
    void parseLine(const std::string & line);
    void parseType();
    void parseField(const std::string & field);
    void parseSpecs();
    void parseSprites();
    void parseCategory();

public:

    AircraftTemplate parseFile(const std::string & filename);

};

struct AircraftTemplate {

private:

    // Only AircraftTemplateParser can construct this struct
    AircraftTemplate();
    friend AircraftTemplate AircraftTemplateParser::createAircraft();

public:

    std::string type;
    uint64_t mtow;
    uint64_t maxFuel;
    uint64_t maxAltitude;
    uint64_t range;
    uint64_t vCruise;
    uint64_t vMax;
    uint64_t vLanding;
    uint64_t vStall;
    std::string sprite;
    std::string spriteSelected;
    WeightCategory weightCategory;

};

#endif //AIRPORT_CPP_AIRCRAFT_TEMPLATE_HPP
