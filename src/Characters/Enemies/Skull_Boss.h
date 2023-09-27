#include "Enemy.h"
#ifndef SKULL_BOSS_H
#define SKULL_BOSS_H

class Skull_Boss : public virtual Enemy
{
public:
    Skull_Boss(const int dmg_bonus_percent = 0, const int hp_bonus_percent = 0);

protected:
    void initVisuals() override;
    int animation_counter;
    void initParameters() override;
};

#endif