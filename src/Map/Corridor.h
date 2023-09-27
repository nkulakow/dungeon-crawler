#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Chamber.h"
#include "Room.h"

#ifndef CORRIDOR_H
#define CORRIDOR_H

class Corridor : virtual public Room
{
protected:
    /*Background*/
    void initBackground();

    /*name*/
    std::string corridorName;

public:
    /*constructor*/
    Corridor();

    /*getters*/
    std::string getName() { return this->corridorName; };
    virtual std::string getBackFile() { return this->backFilepath; };

    /*setters*/
    void setName(std::string name) { this->corridorName = name; };
    void setIsLvlHard(bool lvl){};
};

#endif