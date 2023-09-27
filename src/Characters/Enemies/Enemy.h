#include "../Character.h"
#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public virtual Character
{
public:
    void increaseDamage(const int dmg_points) override{};
    void increaseHealth(const int hp_points) override{};
    void stand() override;
    void attack(std::shared_ptr<Character> &target) override;
};

#endif