#include "Skeleton.h"
#include <iostream>

Skeleton::Skeleton(const int dmg_bonus_percent, const int hp_bonus_percent) : Character()
{
    this->initVisuals();
    this->initParameters();

    this->damage = float(this->damage) * (1.f + float(dmg_bonus_percent) / 100.f);
    this->health = float(this->health) * (1.f + float(hp_bonus_percent) / 100.f);

    this->max_attack_anim_counter = 5;
    this->anim_counter_damage_frame = 3;
    this->animation_counter = 0;
}

void Skeleton::initVisuals()
{
    this->texture.loadFromFile(TEXTURE_PATH_SKELETON);
    this->visuals.setTexture(this->texture);
    this->visuals.setTextureRect(sf::IntRect(0, 256, 256, 256));
    this->visuals.setScale(0.5f, 0.5f);
}

void Skeleton::initParameters()
{
    this->damage = 5;
    this->health = 25;
}