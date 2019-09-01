//
// Created by Filip Peterek on 2019-09-01.
//

#include "aircraft_template.hpp"

std::ostream & operator<<(std::ostream & os, WeightCategory cat) {

    std::string str;

    switch (cat) {
        case WeightCategory::Light:
            str = "Light"; break;
        case WeightCategory::Medium:
            str = "Medium"; break;
        case WeightCategory::Heavy:
            str = "Heavy"; break;
        case WeightCategory::Super:
            str = "Super"; break;
    }

    return os << str;

}


AircraftTemplate::AircraftTemplate() { }

AircraftTemplate AircraftTemplateParser::createAircraft() {
    return AircraftTemplate();
}

std::unordered_map<std::string, WeightCategory> AircraftTemplateParser::categories = {
        { "light", WeightCategory::Light   },
        { "medium", WeightCategory::Medium },
        { "heavy", WeightCategory::Heavy   },
        { "super", WeightCategory::Super   }
};

AircraftTemplate AircraftTemplateParser::parseFile(const std::string & filename) {
    std::ifstream is = openFile(filename);
    loadFile(is);
    return createTemplate();
}

std::ifstream AircraftTemplateParser::openFile(const std::string &filename) {

    this->filename = filename;
    std::ifstream is(filename);
    if (not is) {
        throw std::runtime_error("Could not load file " + filename);
    }
    return is;

}

void AircraftTemplateParser::loadFile(std::ifstream & is) {

    lines = std::unordered_map<std::string, std::string>();
    specs = std::unordered_map<std::string, uint64_t>();
    sprites = std::pair<std::string, std::string>();

    parseLines(is);
    parseType();
    parseSpecs();
    parseSprites();
    parseCategory();

}

void AircraftTemplateParser::parseLines(std::ifstream &is) {

    std::string line;

    while (not is.eof()) {
        std::getline(is, line);
        if (line.empty()) {
            continue;
        }
        parseLine(line);
    }

}

size_t firstNonSpace(const std::string & str) {

    for (size_t i = 0; i < str.size(); ++i) {
        if (not std::isspace(str[i])) {
            return i;
        }
    }

    return std::string::npos;

}

size_t lastNonSpace(const std::string & str) {

    for (size_t i = str.size() - 1; i != std::string::npos; --i) {
        if (not std::isspace(str[i])) {
            return i;
        }
    }

    return 0;

}


std::string trim(const std::string & str) {

    std::string ltrim = str.substr(firstNonSpace(str), std::string::npos);
    std::string rtrim = ltrim.substr(0, lastNonSpace(ltrim) + 1);
    return rtrim;

}

void AircraftTemplateParser::parseLine(const std::string &line) {

    const std::string noComment = line.substr(0, line.find('#'));
    const size_t eqIndex = noComment.find('=');

    if (eqIndex == std::string::npos) {
        throw std::runtime_error("Invalid line '" + line + "' in file " + filename);
    }

    const std::string left = noComment.substr(0, eqIndex);
    const std::string right = noComment.substr(eqIndex + 1);

    if (left.empty() or right.empty()) {
        throw std::runtime_error("Invalid line '" + line + "' in file " + filename);
    }

    const std::string ltrim = trim(left);
    const std::string rtrim = trim(right);

    lines[ltrim] = rtrim;

}

AircraftTemplate AircraftTemplateParser::createTemplate() {

    AircraftTemplate tmpl = createAircraft();

    tmpl.type = type;

    tmpl.mtow = specs["mtow"];
    tmpl.maxFuel = specs["fuel"];
    tmpl.maxAltitude = specs["max_altitude"];
    tmpl.range = specs["range"];
    tmpl.vCruise = specs["v_cruise"];
    tmpl.vMax = specs["v_max"];
    tmpl.vLanding = specs["v_landing"];
    tmpl.vStall = specs["v_stall"];
    tmpl.sprite = sprites.first;
    tmpl.spriteSelected = sprites.second;
    tmpl.weightCategory = category;

    return tmpl;

}

void AircraftTemplateParser::parseType() {
    try {
        type = lines.at("type");
    } catch (const std::out_of_range & e) {
        throw std::runtime_error("Missing field 'type' in file " + filename);
    }
}

void AircraftTemplateParser::parseSpecs() {

    parseField("mtow");
    parseField("fuel");
    parseField("max_altitude");
    parseField("range");
    parseField("v_cruise");
    parseField("v_max");
    parseField("v_landing");
    specs["v_stall"] = specs["v_landing"] / 1.3;

}

void AircraftTemplateParser::parseField(const std::string & field) {

    std::string strVal;
    try {
        strVal = lines.at(field);
    } catch (const std::out_of_range & e) {
        throw std::runtime_error("Missing field '" + field + "' in file " + filename);
    }

    uint64_t val;
    try {
        val = std::stoull(strVal);
    } catch (const std::exception & e) {
        throw std::runtime_error("Invalid value '" + strVal + "' for field '"
                                 + field + "' in file " + filename);
    }

    specs[field] = val;

}

void AircraftTemplateParser::parseSprites() {

    std::string field = "sprite";

    try {

        const std::string yellow = lines.at(field);
        const std::string red = lines.at(field = "sprite_red");
        sprites = std::make_pair(yellow, red);

    } catch (const std::out_of_range & e) {
        throw std::runtime_error("Missing field '" + field + "' in file " + filename);
    }

}

void AircraftTemplateParser::parseCategory() {

    std::string strCategory;
    try {
        strCategory = lines.at("category");
    } catch (const std::out_of_range & e) {
        throw std::runtime_error("Missing field 'category' in file " + filename);
    }

    try {
        category = categories.at(strCategory);
    } catch (const std::out_of_range & e) {
        throw std::runtime_error("Invalid value '" + strCategory +
                "' for field 'category' in file " + filename);
    }

}
