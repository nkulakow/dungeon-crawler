#include "Wizard.h"

Wizard::Wizard() : Hero()
{
    this->TexturePath = TEXTURE_PATH_WIZARD;
    this->initVisuals();
    this->initParameters();
    this->MaxWalkCounter = 4;
    this->max_attack_anim_counter = 11;
    this->anim_counter_damage_frame = 9;
}

void Wizard::attack(std::shared_ptr<Character> &target)
{
    if (this->stand_anim_counter == anim_counter_damage_frame)
        target->takeDamage(this->damage);

    this->visuals.setTextureRect(sf::IntRect(stand_anim_counter * 256, 0, 256, 256));
    this->stand_anim_counter++;
}

void Wizard::initParameters()
{
    this->health = 25;
    this->damage = 15;
}