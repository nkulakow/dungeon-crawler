#include "Warrior.h"

Warrior::Warrior() : Hero()
{
    this->TexturePath = TEXTURE_PATH_WARRIOR;
    this->initVisuals();
    this->initParameters();
    this->MaxWalkCounter = 6;
    this->walkAnimCounter = 0;
    this->max_attack_anim_counter = 7;
    this->anim_counter_damage_frame = 5;
}

void Warrior::attack(std::shared_ptr<Character> &target)
{
    if (this->stand_anim_counter == anim_counter_damage_frame)
        target->takeDamage(this->damage);

    this->visuals.setTextureRect(sf::IntRect(stand_anim_counter * 256, 0, 256, 256));
    this->stand_anim_counter++;
}

void Warrior::initParameters()
{
    this->health = 30;
    this->damage = 10;
}