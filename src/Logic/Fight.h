#pragma once
#include <vector>
#include <string>
#include <memory>
#include "../Characters/Character.h"
#include "../Characters/Enemies/Enemy.h"
#include "../Characters/Enemies/Skeleton.h"
#include "../Characters/Heros/Hero.h"
#include "../Characters/Heros/Wizard.h"
#include "../Characters/Heros/Warrior.h"
#include "Party.h"
#include "constants.h"
#ifndef FIGHT_H
#define FIGHT_H

class Fight
{
public:
    Fight(const Party &fheroes, const Party &fenemies);
    //      GETTERS     //
    Party &getHeroes() { return this->heroes; }
    Party &getEnemies() { return this->enemies; }
    const unsigned int getRound() const { return this->round_counter; }
    const unsigned int getMovingHeroIndex() const { return this->moving_hero_index; }
    const unsigned int getAttackerIndex() const { return this->attacker_index; }
    const unsigned int getTargetndex() const { return this->target_index; }
    std::shared_ptr<Character> &getAttacker() { return this->attacker; }
    std::shared_ptr<Character> &getTarget() { return this->target; }
    const sf::Vector2f &getPreviousAttackerPosition() const { return this->previous_attacker_position; }
    const sf::Vector2f &getPreviousTargetPosition() const { return this->previous_target_position; }
    const int getState() const { return this->current_state; }
    const std::vector<std::shared_ptr<Character>> &getHeroesQueue() const { return this->heroes_queue; }
    const std::vector<std::shared_ptr<Character>> &getEnemiesQueue() const { return this->enemies_queue; }

    void incrementMoveIndex() { this->moving_hero_index++; }
    void incrementTargetIndex();
    void changeState(const int new_state);

    void updateTarget();
    void updateAttacker();

    void setTargetIndex(const unsigned int new_index) { this->target_index = new_index; }
    void setAttackerIndex(const unsigned int new_index) { this->attacker_index = new_index; }
    void savePreviousAttackerPosition() { this->previous_attacker_position = this->attacker->getVisuals().getPosition(); }
    void savePreviousTargetPosition() { this->previous_target_position = this->target->getVisuals().getPosition(); }

    void updateAfterAttack();

private:
    Party heroes;  // must contain Hero class!
    Party enemies; // must contain Enemy class!
    unsigned int round_counter;
    bool end_of_round;
    int current_state;
    unsigned int moving_hero_index;
    unsigned int target_index;
    unsigned int attacker_index;
    std::shared_ptr<Character> attacker;
    std::shared_ptr<Character> target;
    // unsigned int moving_enemy_index;
    std::vector<std::shared_ptr<Character>> heroes_queue;  // order of moves in round
    std::vector<std::shared_ptr<Character>> enemies_queue; // order of moves in round
    sf::Vector2f previous_attacker_position;
    sf::Vector2f previous_target_position;

    void getQueue();
};

#endif