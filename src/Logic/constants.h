#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

//          STATES          //
enum GAME_STATES
{
    MainMenu,
    inRoom,
    WannaChangeRoomRight,
    WannaChangeRoomLeft,
    ChangingRoom,
    Battle,
    MExit,
    MenuVictory
};

enum CHARACTER_STATES
{
    CharacterStand,
    CharacterMoveRight,
    CharacterMoveLeft,
    CharacterAttack
};

enum PARTY_STATES
{
    Stand,
    MoveRigth,
    MoveLeft,
    PartyChangeRoomRight,
    PartyChangeRoomLeft,
    PartyEnteringRoomLeft,
    PartyEnteringRoomRight,
    Fighting
};

enum BATTLE_STATES
{
    PlayersMove,
    EnemiesMove,
    PlayerAttack,
    ComputerAttack,
    BattleEnd
};

//          WINDOW PARAMETERS               //
const unsigned int WINDOW_RESOLUTION_HORIZONTAL = 800;
const unsigned int WINDOW_RESOLUTION_VERTICAL = 600;

//          ANIMATONS PARAMETERS            //
const unsigned int MAX_ANIMATION_COUNTER = 7;
const unsigned int MAX_ANIMATION_COUNTER_WARRIOR_STAND = 2;
const unsigned int MAX_ANIMATION_COUNTER_WARRIOR_WALK = 8;
const unsigned int MAX_ANIMATION_COUNTER_WARRIOR_ATTACK = 7;

const unsigned int MAX_ANIMATION_COUNTER_WIZARD_STAND = 2;
const unsigned int MAX_ANIMATION_COUNTER_WIZARD_WALK = 6;
const unsigned int MAX_ANIMATION_COUNTER_WIZARD_ATTACK = 12;

const unsigned int MAX_ANIMATION_COUNTER_SKELETON_ATTACK = 5;
const unsigned int MAX_ANIMATION_COUNTER_SKELETON_STAND = 4;

const std::vector<sf::Vector2f> CHARACTER_VECTOR_RIGHT = {sf::Vector2f(1.5f, 0.f), sf::Vector2f(1.3f, 0.f), sf::Vector2f(1.f, 0.f)};
const std::vector<sf::Vector2f> CHARACTER_VECTOR_LEFT = {sf::Vector2f(-1.5f, 0.f), sf::Vector2f(-1.3f, 0.f), sf::Vector2f(-1.f, 0.f)};
const sf::Vector2f CHARACTER_SHIFT_RIGHT = sf::Vector2f(1.f, 0.f);
const sf::Vector2f CHARACTER_SHIFT_LEFT = sf::Vector2f(-1.3f, 0.f);

//          PATHS TO TEXTURES              //
const std::string TEXTURE_PATH_WIZARD = "Textures/heroes/wizard_sheet.png";
const std::string TEXTURE_PATH_WARRIOR = "Textures/heroes/warrior_sheet.png";
const std::string TEXTURE_PATH_SKELETON = "Textures/enemies/skeleton_sheet.png";
const std::string TEXTURE_PATH_SKULL_BOSS = "Textures/enemies/skull_boss_sheet.png";

//          TEXT TO DISPLAY             //
const std::string TXT_W_TO_RIGHT = "click W to go right";
const std::string TXT_W_TO_LEFT = "click W to go left";
const std::string TXT_YOURS_TURN = "your turn";
const std::string TXT_ENEMY_TURN = "enemies turn";
const std::string TXT_HEROS_LVL_UP = "heroes leveled up";
const int POS_TXT_W_TO_Y = 570;
const float OFFSET_TXT_PARAM_Y = 105.f;
const unsigned int ROOM_TEXT_SIZE = 28;
const unsigned int CHANGE_ROOM_TEXT_SIZE = 20;
const unsigned int CHARACTER_PARAMS_TEXT_SIZE = 18;
const unsigned int POS_TXT_CHANGE_RIGHT = 600;
const unsigned int POS_TXT_CHANGE_LEFT = 70;

//          OTHER VISUAL PARAMS         //
const float OFFSET_ARROW_Y = 55.f;
const float OFFSET_ARROW_X = 32.f;
const float VISUAL_CHAR_PTR_OFFSET = 30.f;

//          FIGHT PARAMS                //
const int DAMAGE_BONUS = 5;
const int HEALTH_BONUS_DISTRIBUTE = 60;

//          MENU            //
enum MENU_INDEXES
{
    Play,
    Exit
};
const unsigned int MAX_MENU_INDEX = 1;

//          MAP PARAMETERS              //
const int NUMBER_OF_CHAMBERS = 4;

//          STATUS_BAR PARAMETERS       //
//              dimensions              //
const float ST_BAR_MAX_HEIGHT = 26.f;
const float ST_BAR_MAX_WIDTH = 80.f;

const float ST_BAR_INNER_HEIGHT = 20.f;
const float ST_BAR_INNER_WIDTH = 70.f;

//                 HP_BAR               //
//                 colors               //
const sf::Color FULL_HP_GREEN = sf::Color(0, 213, 28, 200);
const sf::Color SCRATCHED_YELLOW = sf::Color(232, 180, 0, 200);
const sf::Color WOUNDED_ORANGE = sf::Color(222, 118, 0, 200);
const sf::Color CRITICAL_RED = sf::Color(141, 0, 0, 200);

const sf::Color BASIC_BACK = sf::Color(133, 128, 101, 200);

//              ATTACK_BAR            //
//              colors              //
const sf::Color FULL_ENERGY_VIOLET = sf::Color(105, 5, 255, 200);
const sf::Color BRISK_INDIGO = sf::Color(5, 55, 255, 200);
const sf::Color WEARY_CYAN = sf::Color(3, 83, 255, 200);
const sf::Color EXHAUSTED_TURQUOISE = sf::Color(4, 234, 255, 200);

//              GAME CONSTANTS           //
const unsigned int WINDOW_FRAME_LIMIT = 60;
const sf::IntRect BACKGROUND_FRAME_DIMENSIONS = sf::IntRect(0, 0, 800, 600);
const sf::Vector2f PARTY_START_POSITION = sf::Vector2f(50.f, 450.f);
const sf::Vector2f PARTY_POS_FIGHT_ENEMY = sf::Vector2f(500.f, 450.f);
const sf::Vector2f PARTY_END_POSITION = sf::Vector2f(800.f, 450.f);

const sf::Vector2f BACKGROUNT_VELOCITY_RIGHT = sf::Vector2f(3.f, 0.f);
const sf::Vector2f BACKGROUNT_VELOCITY_LEFT = sf::Vector2f(-3.f, 0.f);

#endif