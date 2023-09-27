#include "Enemy.h"
#ifndef SKELETON_H
#define SKELETON_H

class Skeleton : public virtual Enemy
{
public:
    Skeleton(const int dmg_bonus_percent = 0, const int hp_bonus_percent = 0);

protected:
    void initVisuals() override;
    int animation_counter;
    void initParameters() override;
};

#endif