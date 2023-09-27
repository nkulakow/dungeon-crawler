#include "Skull_Boss.h"
#include <iostream>

Skull_Boss::Skull_Boss(const int dmg_bonus_percent, const int hp_bonus_percent) : Character()
{
    this->initVisuals();
    this->initParameters();

    this->damage = this->damage * (1.f + float(dmg_bonus_percent) / 100.f);
    this->health = this->health * (1.f + float(hp_bonus_percent) / 100.f);

    this->max_attack_anim_counter = 9;
    this->anim_counter_damage_frame = 6;
    this->animation_counter = 0;
}

void Skull_Boss::initVisuals()
{
    this->texture.loadFromFile(TEXTURE_PATH_SKULL_BOSS);
    this->visuals.setTexture(this->texture);
    this->visuals.setTextureRect(sf::IntRect(0, 256, 256, 256));
}

void Skull_Boss::initParameters()
{
    this->damage = 20;
    this->health = 85;
}
