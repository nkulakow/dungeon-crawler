#include <vector>
#include <memory>
#include "Chamber.h"
#include "Corridor.h"
#include "Room.h"
#include "../Characters/Enemies/Skeleton.h"
#include "../Logic/constants.h"

#ifndef MAP_H
#define MAP_H

class Map
{
private:
    void generateMap();
    int roomNumber;
    std::vector<std::shared_ptr<Room>> roomVector;

public:
    Map();
    int getCurrentRoomNumber();
    std::shared_ptr<Room> &getCurrentRoom();
    void incrementRoomNumber();
    void decrementRoomNumber();
    int getNumberOfRooms() { return roomVector.size(); };
    const unsigned int updateBackgrountAnimationCounter() const;
};

#endif