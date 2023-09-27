#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <memory>
#include <vector>
#include "../Characters/Enemies/Enemy.h"
#include "../Characters/Enemies/Skeleton.h"
#ifndef ROOM_H
#define ROOM

class Room
{
protected:
    /*Background*/
    std::string backFilepath;
    bool is_fight;
    bool isLvlHard;
    unsigned int MaxAnimCounter;

public:
    /*constructors*/
    virtual ~Room(){};

    /*getters*/
    virtual std::string getName() = 0;
    virtual std::string getBackFile() = 0;
    const bool getIsLvlHard() const { return this->isLvlHard; }
    const bool isFight() const { return this->is_fight; }
    const unsigned int getMaxAnimCounter() const { return this->MaxAnimCounter; }

    /*setters*/
    virtual void setName(std::string name) = 0;
    void setIsFight(const bool new_value) { this->is_fight = new_value; }
    virtual void setIsLvlHard(bool lvl) = 0;
};

#endif