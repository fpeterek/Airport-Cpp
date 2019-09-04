//
// Created by Filip Peterek on 2019-09-01.
//

#ifndef AIRPORT_CPP_AIRCRAFT_TEMPLATE_HPP
#define AIRPORT_CPP_AIRCRAFT_TEMPLATE_HPP

#include <string>
#include <fstream>
#include <ostream>
#include <unordered_map>

#include "weight_category.hpp"
#include "aircraft_base.hpp"

struct AircraftTemplate: public AircraftBase {

    std::string sprite;
    std::string spriteSelected;

};

class AircraftTemplateParser {

    static std::unordered_map<std::string, WeightCategory> categories;

    std::string filename;
    std::unordered_map<std::string, std::string> lines;
    std::unordered_map<std::string, uint64_t> specs;
    std::string type;
    std::pair<std::string, std::string> sprites;
    WeightCategory category;

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

#endif //AIRPORT_CPP_AIRCRAFT_TEMPLATE_HPP
