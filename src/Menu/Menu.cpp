#include "Menu.h"

Menu::Menu()
{
    this->background_path = "Textures/backgrounds/menu_background.png";
    this->selected_option_index = 0;
    this->initText();
    this->initOptions();
}

void Menu::initText()
{
    this->options_text.push_back("PLAY");
    this->options_text.push_back("EXIT");
}

void Menu::initOptions()
{
    this->font.loadFromFile("fonts/Beyond-Wonderland.ttf");
    for (int index = 0; index <= MAX_MENU_INDEX; ++index)
    {
        this->options.push_back(sf::Text(this->options_text[index], this->font, 55));
        float width = this->options[index].getGlobalBounds().width;
        this->options[index].setPosition(sf::Vector2f(400 - (width / 2), 200 + index * 96));
        if (index == 0)
            this->options[index].setFillColor(sf::Color::Red);
        else
            this->options[index].setFillColor(sf::Color::White);
    }
}

void Menu::selectOptionUp()
{
    if (this->selected_option_index == 0)
        this->selected_option_index = MAX_MENU_INDEX;
    else
        this->selected_option_index -= 1;
}

void Menu::selectOptionDown()
{
    if (this->selected_option_index == MAX_MENU_INDEX)
        this->selected_option_index = 0;
    else
        this->selected_option_index += 1;
}