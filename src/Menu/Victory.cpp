#include "Victory.h"

Victory::Victory()
{
    this->background_path = "Textures/backgrounds/menu_background.png";
    this->selected_option_index = 0;
    this->initText();
    this->initOptions();
}

void Victory::initText()
{
    this->options_text.push_back("VICTORY");
}

void Victory::initOptions()
{
    this->font.loadFromFile("fonts/Beyond-Wonderland.ttf");
    this->options.push_back(sf::Text(this->options_text[0], this->font, 55));
    float width = this->options[0].getGlobalBounds().width;
    this->options[0].setPosition(sf::Vector2f(400 - (width / 2), 200 + 0 * 96));
    this->options[0].setFillColor(sf::Color::Red);
}
