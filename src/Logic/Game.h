#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "../Characters/Character.h"
#include "../Characters/Enemies/Enemy.h"
#include "../Characters/Enemies/Skeleton.h"
#include "../Characters/Enemies/Skull_Boss.h"
#include "../Characters/Heros/Hero.h"
#include "../Characters/Heros/Wizard.h"
#include "../Characters/Heros/Warrior.h"
#include "../Map/Map.h"
#include "../VisualAdditions/StatusBar.h"
#include "Party.h"
#include "../Menu/Menu.h"
#include "../Menu/Game_Over.h"
#include "../Menu/Victory.h"
#include "Fight.h"
#include "constants.h"

#ifndef GAME_H
#define GAME_H

class Game
{
public:
    Game();
    ~Game();
    void run();
    void draw();
    void addCharacter(std::shared_ptr<Character> new_character);

private:
    //     VISUALS AND ANIMATIONS     //
    sf::RenderWindow *window;
    sf::Clock frame_counter_animations;
    sf::Clock frame_counter_movement;
    sf::Texture backgroundTexture;
    sf::Sprite background;
    sf::Texture arrowTexture;
    sf::Sprite arrowSprite;
    sf::Font mainFont;
    sf::Font paramsFont;
    sf::Text roomText;
    sf::Text whoseTurnText;
    sf::Text changeRoomText;
    sf::Text characterParamsText;
    sf::Text heroesLvlUpText;
    unsigned int background_anim_counter;
    sf::Vector2f speed_right;
    sf::Vector2f speed_left;
    unsigned int backgroundAnimMax;

    //      LOGIC       //
    sf::Event event;
    Party characters;
    int current_state;
    Map map;
    Menu main_menu;
    GameOver exit_menu;
    Victory victory_menu;
    std::shared_ptr<Fight> current_fight;

    //      MOUSE      //
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //      MUSIC       //
    sf::Music mainMusic;
    sf::Music fightMusic;
    sf::Music winMusic;
    sf::Music retreatMusic;

    //  SOUND EFFECTS   //
    sf::SoundBuffer hero_attack_buffer;
    sf::SoundBuffer enemy_attack_buffer;
    sf::SoundBuffer critical_hit_buffer;
    sf::SoundBuffer flawless_victory_buffer;
    sf::SoundBuffer battle_win_buffer;
    sf::SoundBuffer game_over_buffer;
    sf::Sound hero_attack_sound;
    sf::Sound enemy_attack_sound;
    sf::Sound critical_hit_sound;
    sf::Sound flawless_victory_sound;
    sf::Sound battle_win_sound;
    sf::Sound game_over_sound;

    //      INITIALIZING        //
    void initWindow();
    void initBackground();
    void initVariables();
    void initAnimations();
    void initText();
    void initMusic();
    void initSoundEffects();
    void initArrow();
    void initAnimVariables();

    void pollEvents();

    //      STATES      //
    void menuOptions();
    void exitMenuOptions();
    void victoryOptions();
    void inRoom();
    void changingRoomRight();
    void changingRoomLeft();
    void charactersChangingRoom();
    void playerChoseOption();
    void startBattle();
    void battle();

    //      UPDATING        //
    void update();
    void updateBackground();
    void updateCharacters();
    void updateText();
    void updateBackgroundRight();
    void updateBackgroundLeft();
    void updateMenu();
    void updateExitMenu();
    void updateVictory();
    void updateMousePos();
    void updateBattle();
    void updateMusic();
    void updateSoundEffects();
    void updateArrow();

    //      MOVEMENT        //
    void stand();
    void moveRight();
    void moveLeft();
    void moveCharactersToRight();
    void moveCharactersFromLeft();
    void moveCharactersToLeft();
    void moveCharactersFromRight();

    //      DRAWING     //
    void drawText();
    void drawArrow();

    //      FIGHT       //
    Party makeEnemies();
    Party makeBoss();
    void playersMove();
    void enemiesMove();
    void playerAttack();
    void computerAttack();
    void fight();
    void endBattle();
};

#endif