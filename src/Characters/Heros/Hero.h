#include "../Character.h"
#include <string>
#ifndef HERO_H
#define HERO_H

class Hero : public virtual Character
{
public:
    Hero();
    void walkRigth() override;
    void walkLeft() override;
    void stand() override;
    void increaseDamage(const int dmg_points) override { this->damage += dmg_points; }
    void increaseHealth(const int hp_points) override { this->health += hp_points; }

protected:
    /*  VISUALS */
    std::string TexturePath;
    unsigned int MaxWalkCounter;
    int walkAnimCounter;
    void initVisuals() override;
};

#endif
