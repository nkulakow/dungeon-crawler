#include <SFML/Graphics.hpp>
#include "Character.h"


//              VISUALS             //
void Character:: setPosition(const sf:: Vector2f &position)
{
    this->visuals.setPosition(position);
}

void Character:: setPosition(const float pos_x, const float pos_y)
{
    this->visuals.setPosition(pos_x, pos_y);
}

void Character:: setScale(const sf:: Vector2f &scale)
{
    this->visuals.setScale(scale);
}

void Character:: setScale(const float scale_x, const float scale_y)
{
    this-> visuals.setScale(scale_x, scale_y);
}

void Character::move(const sf::Vector2f &dislocation)
{
    this->visuals.move(dislocation);
}

void Character::changeState(const int new_state)
{
    if (new_state != this->current_state)
    {
        if (new_state == CHARACTER_STATES::CharacterStand)
            this->visuals.setTextureRect(sf::IntRect(256, 256, 256, 256));
        this->current_state = new_state;
    }
}

void Character::takeDamage(const unsigned int damage)
{
    if (damage > this->health)
        this->health = 0;
    else
        this->health -= damage;
}