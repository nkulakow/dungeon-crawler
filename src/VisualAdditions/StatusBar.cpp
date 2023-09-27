#include "StatusBar.h"

StatusBar::StatusBar()
{
    this->refillBar();

    this->bar_backside.setFillColor(BASIC_BACK);
    this->bar_innerside.setFillColor(FULL_HP_GREEN);

    this->text.setFont(this->font);
    this->text.setFillColor(sf::Color::White);
    this->text.setOutlineColor(sf::Color::Black);
    this->text.setOutlineThickness(1.5f);
}

sf::Text StatusBar::getText() const
{
    return this->text;
}

void StatusBar::setText(const std::string &new_text)
{
    this->text.setString(new_text);
}

sf::Color StatusBar::getColor() const
{
    return this->bar_innerside.getFillColor();
}

void StatusBar::setColor(const sf::Color &new_color)
{
    this->bar_innerside.setFillColor(new_color);
}

void StatusBar::shrinkBar(const float &damage)
{
    if (damage > 0 || damage < ST_BAR_INNER_WIDTH)
    {
        this->bar_innerside.setSize(sf::Vector2f(ST_BAR_INNER_WIDTH - damage, ST_BAR_INNER_HEIGHT));
    }
    else if (damage >= ST_BAR_INNER_WIDTH)
    {
        this->bar_innerside.setSize(sf::Vector2f(5.f, ST_BAR_INNER_HEIGHT));
    }
}

void StatusBar::refillBar()
{
    this->bar_backside.setSize(sf::Vector2f(ST_BAR_MAX_WIDTH, ST_BAR_MAX_HEIGHT));
    this->bar_innerside.setSize(sf::Vector2f(ST_BAR_INNER_WIDTH, ST_BAR_INNER_HEIGHT));
}

void StatusBar::setPosition(const float &x, const float &y)
{
    this->setPosition(sf::Vector2f(x, y));
}

void StatusBar::setPosition(const sf::Vector2f &new_position)
{
    this->bar_backside.setPosition(new_position);
    float x_offset = (ST_BAR_MAX_HEIGHT - ST_BAR_INNER_HEIGHT) / 2;
    float y_offset = (ST_BAR_MAX_WIDTH - ST_BAR_INNER_WIDTH) / 2;
    this->bar_innerside.setPosition(new_position.x - x_offset, new_position.y - y_offset);
}

void StatusBar::initFont()
{
    this->font.loadFromFile("fonts/Beyond-Wonderland.ttf");
}
