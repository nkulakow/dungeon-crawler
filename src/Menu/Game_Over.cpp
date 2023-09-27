#include "Game_Over.h"

GameOver::GameOver()
{
    this->background_path = "Textures/backgrounds/menu_background.png";
    this->selected_option_index = 0;
    this->initText();
    this->initOptions();
}

void GameOver::initText()
{
    this->options_text.push_back("GAME OVER");
}

void GameOver::initOptions()
{
    this->font.loadFromFile("fonts/Beyond-Wonderland.ttf");
    this->options.push_back(sf::Text(this->options_text[0], this->font, 55));
    float width = this->options[0].getGlobalBounds().width;
    this->options[0].setPosition(sf::Vector2f(400 - (width / 2), 200 + 0 * 96));
    this->options[0].setFillColor(sf::Color::Red);
}
