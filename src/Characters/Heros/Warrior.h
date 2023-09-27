#include "Hero.h"
#ifndef WARRIOR_H
#define WARRIOR_H

class Warrior : public virtual Hero
{
protected:
    void initParameters() override;

public:
    Warrior();
    void attack(std::shared_ptr<Character> &target) override;
};

#endif