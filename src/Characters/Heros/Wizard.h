#include "Hero.h"
#ifndef WIZARD_H
#define WIZARD_H

class Wizard : public virtual Hero
{
protected:
    void initParameters() override;

public:
    Wizard();
    void attack(std::shared_ptr<Character> &target) override;
};

#endif