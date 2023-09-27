#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <memory>
#include "Room.h"

#ifndef CHAMBER_H
#define CHAMBER_H

class Chamber : virtual public Room
{
protected:
    /*name*/
    std::string chamberName;

public:
    /*constructor*/
    Chamber();

    /*getters*/
    std::string getName() { return this->chamberName; };
    virtual std::string getBackFile() { return this->backFilepath; };

    /*setters*/
    void setName(std::string name) { this->chamberName = name; };
    void setIsLvlHard(bool lvl) { this->isLvlHard = lvl; };
};

#endif