#include "Enemy.h"

void Enemy::stand()
{
    this->visuals.setTextureRect(sf::IntRect(512 * this->stand_anim_counter, 256, 256, 256));
    this->stand_anim_counter = (this->stand_anim_counter + 1) % 2;
}

void Enemy::attack(std::shared_ptr<Character> &target)
{
    if (this->stand_anim_counter == anim_counter_damage_frame)
        target->takeDamage(this->damage);

    this->visuals.setTextureRect(sf::IntRect(stand_anim_counter * 256, 0, 256, 256));
    this->stand_anim_counter++;
}