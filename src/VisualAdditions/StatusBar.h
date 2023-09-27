#pragma once
#include "../Logic/constants.h"
#include <SFML/Graphics.hpp>

#ifndef STATUS_BAR_H
#define STATUS_BAR_H

class StatusBar
{
protected:
    sf::Font font;
    sf::Text text;
    sf::RectangleShape bar_backside;
    sf::RectangleShape bar_innerside;

    void initFont();
public:
    StatusBar();
    sf::Text getText() const;
    void setText(const std::string& new_text);
    sf::Color getColor() const;
    void setColor(const sf::Color& new_color);
    void shrinkBar(const float& damage);
    void refillBar();
    void setPosition(const float& x, const float& y);
    void setPosition(const sf::Vector2f& new_position); 
    
};


#endif