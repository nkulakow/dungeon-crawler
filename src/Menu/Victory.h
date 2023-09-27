#pragma once
#ifndef VICTORY_H
#define VICTORY_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Menu.h"

class Victory
{
public:
    Victory();
    const std::string &getBackgroundPath() const { return this->background_path; }
    std::vector<sf::Text> &getOptions() { return this->options; }
    const unsigned int getSelectedOptionIndex() const { return this->selected_option_index; }

protected:
    sf::Font font;
    std::vector<std::string> options_text;
    std::vector<sf::Text> options;
    unsigned int selected_option_index;

    std::string background_path;

    //      INITIALIZING       //
    void initOptions();
    void initText();
};

#endif