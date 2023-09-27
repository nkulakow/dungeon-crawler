#include "Map.h"

/*private functions*/
void Map::generateMap()
{
    for (int nChamber = 1; nChamber < NUMBER_OF_CHAMBERS; nChamber++)
    {
        std::shared_ptr<Room> chamber = std::make_shared<Chamber>();
        std::shared_ptr<Room> corridor = std::make_shared<Corridor>();
        chamber->setName(chamber->getName() + " " + std::to_string(nChamber));
        corridor->setName(corridor->getName() + " " + std::to_string(nChamber));
        if (nChamber % 2 == 0)
            chamber->setIsLvlHard(true);
        else
            chamber->setIsLvlHard(false);
        this->roomVector.push_back(std::move(chamber));
        this->roomVector.push_back(std::move(corridor));
    }
    std::shared_ptr<Room> chamber = std::make_shared<Chamber>();
    chamber->setName("Final " + chamber->getName());
    chamber->setIsLvlHard(true);
    this->roomVector.push_back(std::move(chamber));
}
/*constructor and destructor*/
Map::Map()
{
    this->generateMap();
    this->roomNumber = 0;
}

/*public functions*/

int Map::getCurrentRoomNumber()
{
    return this->roomNumber;
}

void Map::incrementRoomNumber()
{
    if (this->roomNumber < this->roomVector.size() - 1)
        this->roomNumber++;
}
void Map::decrementRoomNumber()
{
    if (this->roomNumber > 0)
        this->roomNumber--;
}

std::shared_ptr<Room> &Map::getCurrentRoom()
{
    return this->roomVector[this->roomNumber];
}

const unsigned int Map::updateBackgrountAnimationCounter() const
{
    return this->roomVector[this->roomNumber + 1]->getMaxAnimCounter();
}