#include "Chamber.h"
#include <memory>
#include <vector>

/*public functions*/
Chamber::Chamber()
{
    this->chamberName = "Chamber";
    this->backFilepath = "Textures/backgrounds/Chamber.jpg";

    this->is_fight = true;
    this->MaxAnimCounter = 400U;
}
