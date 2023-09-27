#include "src/Logic/Game.h"
#include "src/Logic/globals.h"
#include "src/Logic/Fight.h"
#include <vector>
#include <memory>

int main()
{
    game.addCharacter(std::make_shared<Wizard>());
    game.addCharacter(std::make_shared<Warrior>());
    game.addCharacter(std::make_shared<Wizard>());
    game.run();

    return 0;
}