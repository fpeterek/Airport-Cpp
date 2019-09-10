//
// Created by Peterek, Filip on 10/09/2019.
//

#ifndef AIRPORT_CPP_WIND_INDICATOR_HPP
#define AIRPORT_CPP_WIND_INDICATOR_HPP

#include <SFML/Graphics/Drawable.hpp>

class WindIndicator : public sf::Drawable {

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif //AIRPORT_CPP_WIND_INDICATOR_HPP
