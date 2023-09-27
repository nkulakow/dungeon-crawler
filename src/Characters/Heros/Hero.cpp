#include "Hero.h"

Hero::Hero() : Character()
{
    this->walkAnimCounter = 0;
}

void Hero::walkRigth() 
{
    if (this->walkAnimCounter == this->MaxWalkCounter)
    {
        this->walkAnimCounter = 0;
    }
    else
        this->walkAnimCounter++;

    this->visuals.setTextureRect(sf::IntRect(this->walkAnimCounter * 256, 512, 256, 256));
}

void Hero::walkLeft()
{
    if (this->walkAnimCounter == 0)
    {
        this->walkAnimCounter = this->MaxWalkCounter;
    }
    else
        this->walkAnimCounter--;

    this->visuals.setTextureRect(sf::IntRect(this->walkAnimCounter * 256, 512, 256, 256));
}

void Hero::stand()
{
    this->visuals.setTextureRect(sf::IntRect(this->stand_anim_counter * 256, 256, 256, 256));
    this->stand_anim_counter = (this->stand_anim_counter + 1) % 2;  //always 0 or 1
}

void Hero::initVisuals()
{
    this->texture.loadFromFile(this->TexturePath);
    this->visuals.setTexture(this->texture);
    this->visuals.setTextureRect(sf::IntRect(0, 256, 256, 256));
    this->visuals.setScale(0.5f, 0.5f);
}
