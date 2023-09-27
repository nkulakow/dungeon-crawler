#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <memory>
#include "../src/Characters/Character.cpp"
#include "../src/Characters/Heros/Hero.cpp"
#include "../src/Characters/Heros/Warrior.cpp"
#include "../src/Characters/Heros/Wizard.cpp"
#include "../src/Characters/Enemies/Enemy.cpp"
#include "../src/Characters/Enemies/Skeleton.cpp"
#include "../src/Characters/Enemies/Skull_Boss.cpp"
#include "../src/Map/Map.cpp"
#include "../src/Map/Room.cpp"
#include "../src/Map/Chamber.cpp"
#include "../src/Map/Corridor.cpp"
#include "../src/Logic/Fight.cpp"
#include "../src/Logic/Party.cpp"
#include "../src/Logic/constants.h"

//              CHARACTERS TESTS                //

TEST_CASE("Warrior creates properly", "[hero],[warrior]")
{
    Warrior warrior;
    REQUIRE(warrior.getHealth() == 30);
    REQUIRE(warrior.getDamage() == 10);
    REQUIRE(warrior.getMaxAttackFrame() == 7);
    REQUIRE(warrior.getState() == CHARACTER_STATES::CharacterStand);
    REQUIRE(!warrior.ifMoved());
    REQUIRE(warrior.getAnimCounter() == 0);
}

TEST_CASE("Wizard creates properly", "[hero],[wizard]")
{
    Wizard wizard;
    REQUIRE(wizard.getHealth() == 25);
    REQUIRE(wizard.getDamage() == 15);
    REQUIRE(wizard.getMaxAttackFrame() == 11);
    REQUIRE(wizard.getState() == CHARACTER_STATES::CharacterStand);
    REQUIRE(!wizard.ifMoved());
    REQUIRE(wizard.getAnimCounter() == 0);
}

TEST_CASE("Warrior's health changes properly", "[hero],[warrior]")
{
    Warrior warrior;
    int health1 = warrior.getHealth();
    warrior.increaseHealth(5);
    REQUIRE(warrior.getHealth() == health1 + 5);
    warrior.takeDamage(4);
    REQUIRE(warrior.getHealth() == health1 + 1);
}

TEST_CASE("Wizard's health changes properly", "[hero],[wizard]")
{
    Wizard wizard;
    int health1 = wizard.getHealth();
    wizard.increaseHealth(3);
    REQUIRE(wizard.getHealth() == health1 + 3);
    wizard.takeDamage(5);
    REQUIRE(wizard.getHealth() == health1 - 2);
}

TEST_CASE("Warrior's damage changes properly", "[hero],[warrior]")
{
    Warrior warrior;
    int dmg1 = warrior.getDamage();
    warrior.increaseDamage(2);
    REQUIRE(warrior.getDamage() == dmg1 + 2);
}

TEST_CASE("Wizard's damage changes properly", "[hero],[wizard]")
{
    Wizard wizard;
    int dmg1 = wizard.getDamage();
    wizard.increaseDamage(6);
    REQUIRE(wizard.getDamage() == dmg1 + 6);
}

TEST_CASE("Skeleton creates properly", "[enemy],[skeleton]")
{
    Skeleton skeleton;
    REQUIRE(skeleton.getMaxAttackFrame() == 5);
    REQUIRE(skeleton.getState() == CHARACTER_STATES::CharacterStand);
    REQUIRE(!skeleton.ifMoved());
    REQUIRE(skeleton.getAnimCounter() == 0);
}

TEST_CASE("Skull Boss creates properly", "[enemy],[skull boss]")
{
    Skull_Boss skullboss;
    REQUIRE(skullboss.getMaxAttackFrame() == 9);
    REQUIRE(skullboss.getState() == CHARACTER_STATES::CharacterStand);
    REQUIRE(!skullboss.ifMoved());
    REQUIRE(skullboss.getAnimCounter() == 0);
}

TEST_CASE("Skeleton's health changes properly", "[enemy],[skeleton]")
{
    Skeleton skeleton;
    int health1 = skeleton.getHealth();
    skeleton.takeDamage(4);
    REQUIRE(skeleton.getHealth() == health1 - 4);
}

TEST_CASE("Skull Boss's health changes properly", "[enemy],[skull boss]")
{
    Skull_Boss skullboss;
    int health1 = skullboss.getHealth();
    skullboss.takeDamage(5);
    REQUIRE(skullboss.getHealth() == health1 - 5);
}

TEST_CASE("Character setters works", "[character]")
{
    Wizard somebody;
    somebody.setIfMoved(true);
    REQUIRE(somebody.ifMoved());
    somebody.setIfMoved(false);
    REQUIRE_FALSE(somebody.ifMoved());

    somebody.setAnimCounter(3);
    REQUIRE(somebody.getAnimCounter() == 3);

    somebody.changeState(CHARACTER_STATES::CharacterAttack);
    REQUIRE(somebody.getState() == CHARACTER_STATES::CharacterAttack);
}

// TODO: enemies, fight (attack target and it takes damage)
//              PARTY TESTS              //

TEST_CASE("Party works properly")
{
    Party heros;
    heros.addCharacter(std::make_shared<Warrior>());
    heros.addCharacter(std::make_shared<Wizard>());
    REQUIRE(int(heros.getSize() == 2));
    REQUIRE(heros.getPartyLength() == 192.f);
    heros.removeFromPosition(1);
    REQUIRE(int(heros.getSize() == 1));
    heros.changeState(PARTY_STATES::MoveLeft);
    REQUIRE(heros.getState() == PARTY_STATES::MoveLeft);
}
//              FIGHT TESTS              //
TEST_CASE("Fight creates properly", "[fight]")
{
    Party heros;
    heros.addCharacter(std::make_shared<Warrior>());
    heros.addCharacter(std::make_shared<Wizard>());
    Party skeletons;
    skeletons.addCharacter(std::make_shared<Skeleton>());
    skeletons.addCharacter(std::make_shared<Skeleton>());
    Fight fight(heros, skeletons);
    REQUIRE(fight.getHeroes().getCharacters() == heros.getCharacters());
    REQUIRE(fight.getEnemies().getCharacters() == skeletons.getCharacters());
    REQUIRE(fight.getRound() == 1);
    REQUIRE(fight.getMovingHeroIndex() == 0);
    REQUIRE(fight.getState() == BATTLE_STATES::PlayersMove);
    REQUIRE(fight.getAttackerIndex() == fight.getTargetndex());
}

TEST_CASE("Fight works properly", "[fight]")
{
    Party heros;
    heros.addCharacter(std::make_shared<Warrior>());
    heros.addCharacter(std::make_shared<Wizard>());
    Party skeletons;
    skeletons.addCharacter(std::make_shared<Skeleton>());
    skeletons.addCharacter(std::make_shared<Skeleton>());
    Fight fight(heros, skeletons);
    fight.incrementMoveIndex();
    REQUIRE(fight.getMovingHeroIndex() == 1);
    fight.incrementTargetIndex();
    REQUIRE(fight.getTargetndex() == 1);
    fight.updateAttacker();
    fight.updateTarget();
    REQUIRE(fight.getAttacker() == heros.getCharacter(0));
    REQUIRE(fight.getTarget() == skeletons.getCharacter(1));
    fight.changeState(BATTLE_STATES::EnemiesMove);
    REQUIRE(fight.getState() == BATTLE_STATES::EnemiesMove);
    fight.updateAttacker();
    fight.updateTarget();
    REQUIRE(fight.getAttacker() == skeletons.getCharacter(0));
    REQUIRE(fight.getTarget() == heros.getCharacter(1));
}
//              MAP TESTS                //

TEST_CASE("Chamber creates properly", "[chamber]")
{
    Chamber chamber;
    REQUIRE(chamber.getName() == "Chamber");
    REQUIRE(chamber.isFight());
    REQUIRE(chamber.getMaxAnimCounter() == 400U);
}

TEST_CASE("Corridor creates properly", "[corridor]")
{
    Corridor corridor;
    REQUIRE(corridor.getName() == "Corridor");
    REQUIRE_FALSE(corridor.isFight());
    REQUIRE(corridor.getMaxAnimCounter() == 600U);
}

TEST_CASE("Chamber setters work properly", "[chamber]")
{
    Chamber chamber;
    chamber.setName("aa");
    REQUIRE(chamber.getName() == "aa");
    chamber.setIsFight(false);
    REQUIRE_FALSE(chamber.isFight());
    chamber.setIsLvlHard(false);
    REQUIRE_FALSE(chamber.getIsLvlHard());
}

TEST_CASE("Corridor setters work properly", "[corridor]")
{
    Corridor corridor;
    corridor.setName("ab");
    REQUIRE(corridor.getName() == "ab");
    corridor.setIsFight(false);
    REQUIRE_FALSE(corridor.isFight());
}

TEST_CASE("Map creates properly", "[map]")
{
    Map map;
    REQUIRE(map.getCurrentRoomNumber() == 0);
    REQUIRE(map.getNumberOfRooms() == 2 * NUMBER_OF_CHAMBERS - 1);
}

TEST_CASE("Decrement/Increment room number works properly", "[map]")
{
    Map map;
    map.incrementRoomNumber();
    REQUIRE(map.getCurrentRoomNumber() == 1);
    map.decrementRoomNumber();
    REQUIRE(map.getCurrentRoomNumber() == 0);
}