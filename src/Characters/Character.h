#pragma once
#include <SFML/Graphics.hpp>
#include "../Logic/constants.h"
#include <iostream>
#include <memory>
#ifndef CHARACTER_H
#define CHARACTER_H

class Character
{
public:
    Character(...)
    {
        this->current_state = CHARACTER_STATES::CharacterStand;
        this->stand_anim_counter = 0;
        this->moved_in_round = false;
    }
    virtual ~Character(){};

    /*          VISUALS         */
    sf::Sprite &getVisuals() { return this->visuals; }
    void setPosition(const sf::Vector2f &position);
    void setPosition(const float position_x, const float position_y);
    void setScale(const sf::Vector2f &scale);
    void setScale(const float scale_x, const float scale_y);
    void setAnimCounter(const unsigned int new_counter) { this->stand_anim_counter = new_counter; }

    /*          STATES          */
    const int getState() const { return this->current_state; }
    void changeState(const int new_state);

    /*          MOVEMENT        */
    virtual void walkRigth(){}; // docelowo tylko dla Heroes
    virtual void walkLeft(){};  // ja wyżej
    void move(const sf::Vector2f &dislocation);
    virtual void stand() = 0;

    /*      PARAMS              */
    const unsigned int getHealth() const { return this->health; };
    const unsigned int getDamage() const { return this->damage; };
    virtual void increaseDamage(const int dmg_points) = 0;
    virtual void increaseHealth(const int hp_points) = 0;

    //      FIGHT       //
    virtual void attack(std::shared_ptr<Character> &target) = 0;
    void takeDamage(const unsigned int damage);
    const unsigned int getMaxAttackFrame() const { return this->max_attack_anim_counter; }
    const unsigned int getAnimCounter() const { return this->stand_anim_counter; }

    const bool ifMoved() const { return this->moved_in_round; }
    void setIfMoved(const bool new_value) { this->moved_in_round = new_value; }

protected:
    sf::Texture texture;
    sf::Sprite visuals; // 64x64

    int current_state;

    unsigned int stand_anim_counter;
    unsigned int max_attack_anim_counter;
    unsigned int anim_counter_damage_frame;
    virtual void initVisuals() = 0;
    virtual void initParameters() = 0;

    /*ATTRIBUTES*/
    unsigned int health;
    unsigned int damage;

    //      FIGHT       //
    bool moved_in_round;
};

#endif