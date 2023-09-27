#include "Game.h"
#include <random>

Game::Game()
{
    this->initWindow();
    this->initVariables();
    this->initBackground();
    this->initAnimations();
    this->initText();
    this->initMusic();
    this->initSoundEffects();
    this->initArrow();
}

Game::~Game()
{
    delete this->window;
}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_RESOLUTION_HORIZONTAL, WINDOW_RESOLUTION_VERTICAL), "Game");
    this->window->setFramerateLimit(WINDOW_FRAME_LIMIT);
}

void Game::initBackground()
{
    this->backgroundTexture.loadFromFile(this->main_menu.getBackgroundPath());
    this->background.setTexture(backgroundTexture);
    this->background.setTextureRect(BACKGROUND_FRAME_DIMENSIONS);
}

void Game::initAnimations()
{
    this->background_anim_counter = 0;
    this->frame_counter_animations.restart();
    this->frame_counter_movement.restart();
}

void Game::addCharacter(std::shared_ptr<Character> new_character)
{
    this->characters.addCharacter(new_character);
    this->characters.setPartyPosition(PARTY_START_POSITION);
}

void Game::initVariables()
{
    this->current_state = GAME_STATES::MainMenu;
    this->current_fight = std::shared_ptr<Fight>(nullptr);
}

void Game::initText()
{
    this->mainFont.loadFromFile("fonts/Beyond-Wonderland.ttf");
    this->paramsFont.loadFromFile("fonts/Dosis-Light.ttf");
    this->roomText.setFont(mainFont);
    this->roomText.setCharacterSize(ROOM_TEXT_SIZE);
    this->roomText.setFillColor(sf::Color::White);
    this->roomText.setOutlineColor(sf::Color::Black);
    this->roomText.setOutlineThickness(2.f);
    this->roomText.setString("");
    this->changeRoomText = this->roomText;
    this->changeRoomText.setCharacterSize(CHANGE_ROOM_TEXT_SIZE);
    this->characterParamsText = this->changeRoomText;
    this->characterParamsText.setCharacterSize(CHARACTER_PARAMS_TEXT_SIZE);
    this->characterParamsText.setFont(paramsFont);
    this->whoseTurnText = this->roomText;
    this->whoseTurnText.setCharacterSize(48);
    this->heroesLvlUpText = this->whoseTurnText;
    this->whoseTurnText.setPosition(sf::Vector2f(float(WINDOW_RESOLUTION_HORIZONTAL / 2) - 100.f, 40.f));
    this->heroesLvlUpText.setPosition(sf::Vector2f(float(WINDOW_RESOLUTION_HORIZONTAL / 2) - 170.f, 40.f));
}

void Game::initMusic()
{
    this->mainMusic.openFromFile("Soundtrack/threatened.ogg");
    this->mainMusic.setLoop(true);
    this->mainMusic.play();
    this->fightMusic.openFromFile("Soundtrack/epic_choir_of_the_damned.ogg");
    this->fightMusic.setLoop(true);
    this->fightMusic.setVolume(70);
    this->winMusic.openFromFile("Soundtrack/endings.wav");
    this->winMusic.setLoop(true);
    this->winMusic.setVolume(70);
    this->retreatMusic.openFromFile("Soundtrack/falling.ogg");
    this->retreatMusic.setLoop(true);
    this->retreatMusic.setVolume(70);
}

void Game::initSoundEffects()
{
    this->hero_attack_buffer.loadFromFile("Soundtrack/sound_effects/hero_attack.wav");
    this->hero_attack_sound.setBuffer(this->hero_attack_buffer);
    this->hero_attack_sound.setVolume(80);

    this->enemy_attack_buffer.loadFromFile("Soundtrack/sound_effects/enemy_attack.wav");
    this->enemy_attack_sound.setBuffer(this->enemy_attack_buffer);
    this->enemy_attack_sound.setVolume(90);

    this->critical_hit_buffer.loadFromFile("Soundtrack/sound_effects/critical_hit.ogg");
    this->critical_hit_sound.setBuffer(this->critical_hit_buffer);
    this->critical_hit_sound.setVolume(80);

    this->flawless_victory_buffer.loadFromFile("Soundtrack/sound_effects/flawless_victory.wav");
    this->flawless_victory_sound.setBuffer(this->flawless_victory_buffer);
    this->flawless_victory_sound.setVolume(90);

    this->battle_win_buffer.loadFromFile("Soundtrack/sound_effects/battle_win.wav");
    this->battle_win_sound.setBuffer(this->battle_win_buffer);
    this->battle_win_sound.setVolume(70);

    this->game_over_buffer.loadFromFile("Soundtrack/sound_effects/game_over.wav");
    this->game_over_sound.setBuffer(this->game_over_buffer);
}

void Game::initArrow()
{
    this->arrowTexture.loadFromFile("Textures/arrow.png");
    this->arrowSprite.setTexture(this->arrowTexture);
}

void Game::initAnimVariables()
{
    this->speed_left = CHARACTER_VECTOR_LEFT[int(this->characters.getSize()) - 1];
    this->speed_right = CHARACTER_VECTOR_RIGHT[int(this->characters.getSize()) - 1];
    this->backgroundAnimMax = 400;
}

void Game::run()
{
    while (window->isOpen())
    {
        this->pollEvents();
        this->update();
        this->window->clear();
        this->draw();
        this->window->display();
    }
}

void Game::pollEvents()
{
    while (window->pollEvent(this->event))
    {
        if (this->event.type == sf::Event::Closed)
            this->window->close();

        if (this->current_state == GAME_STATES::MainMenu)
            this->menuOptions();
        else if (this->current_state == GAME_STATES::inRoom)
            this->inRoom();
        else if (this->current_state == GAME_STATES::WannaChangeRoomRight)
            this->changingRoomRight();
        else if (this->current_state == GAME_STATES::WannaChangeRoomLeft)
            this->changingRoomLeft();
        else if (this->current_state == GAME_STATES::Battle)
            this->battle();
        if (this->current_state == GAME_STATES::MExit)
            this->exitMenuOptions();
        if (this->current_state == GAME_STATES::MenuVictory)
            this->victoryOptions();
    }
}

//          GAME STATES         //
void Game::menuOptions()
{
    if (this->event.type == sf::Event::TextEntered)
        this->event.type = sf::Event::KeyPressed;

    if (this->event.type == sf::Event::KeyPressed)
    {
        if (this->event.key.code == sf::Keyboard::Escape)
            this->window->close();

        if (this->event.key.code == sf::Keyboard::Up)
            this->main_menu.selectOptionUp();

        else if (this->event.key.code == sf::Keyboard::Down)
            this->main_menu.selectOptionDown();

        else if (this->event.key.code == sf::Keyboard::Enter)
            this->playerChoseOption();
    }
}
void Game::exitMenuOptions()
{
    if (this->event.type == sf::Event::TextEntered)
        this->event.type = sf::Event::KeyPressed;

    if (this->event.type == sf::Event::KeyPressed)
    {
        if (this->event.key.code == sf::Keyboard::Escape || this->event.key.code == sf::Keyboard::Enter)
            this->window->close();
    }
}

void Game::victoryOptions()
{
    if (this->event.type == sf::Event::TextEntered)
        this->event.type = sf::Event::KeyPressed;

    if (this->event.type == sf::Event::KeyPressed)
    {
        if (this->event.key.code == sf::Keyboard::Escape || this->event.key.code == sf::Keyboard::Enter)
            this->window->close();
    }
}
void Game::playerChoseOption()
{
    if (this->main_menu.getSelectedOptionIndex() == 1)
        this->window->close();
    if (this->main_menu.getSelectedOptionIndex() == 0)
    {
        this->current_state = GAME_STATES::inRoom;
        this->backgroundTexture.loadFromFile(this->map.getCurrentRoom()->getBackFile());
        this->background.setTextureRect(BACKGROUND_FRAME_DIMENSIONS);
        this->initAnimVariables();
    }
}

void Game::inRoom()
{
    if (this->event.type == sf::Event::TextEntered)
        this->event.type = sf::Event::KeyPressed;

    if (this->event.type != sf::Event::KeyPressed)
    {
        this->characters.changeState(PARTY_STATES::Stand);
        this->characters.changeCharactersState(CHARACTER_STATES::CharacterStand);
        return;
    }

    if (this->event.key.code == sf::Keyboard::Escape)
        this->current_state = GAME_STATES::MainMenu;
    else if (this->event.key.code == sf::Keyboard::D)
    {
        if (this->background_anim_counter < this->backgroundAnimMax)
        {
            if (this->map.getCurrentRoom()->isFight())
            {
                this->startBattle();
            }
            else
            {
                this->characters.changeState(PARTY_STATES::MoveRigth);
                this->characters.changeCharactersState(CHARACTER_STATES::CharacterMoveRight);
            }
        }
        else
        {
            if (this->map.getCurrentRoomNumber() != this->map.getNumberOfRooms() - 1)
                this->current_state = GAME_STATES::WannaChangeRoomRight;
            this->characters.changeState(PARTY_STATES::Stand);
            this->characters.changeCharactersState(CHARACTER_STATES::CharacterStand);
        }
    }
    else if (this->event.key.code == sf::Keyboard::A)
    {
        if (this->background_anim_counter > 0)
        {
            this->characters.changeState(PARTY_STATES::MoveLeft);
            this->characters.changeCharactersState(CHARACTER_STATES::CharacterMoveLeft);
        }
        else
        {
            if (this->map.getCurrentRoomNumber() != 0)
                this->current_state = GAME_STATES::WannaChangeRoomLeft;
            this->characters.changeState(PARTY_STATES::Stand);
            this->characters.changeCharactersState(CHARACTER_STATES::CharacterStand);
        }
    }
}

//          BATTLE          //
Party Game::makeEnemies()
{
    int bonus = this->map.getCurrentRoomNumber() / 2;
    std::vector<std::shared_ptr<Character>> enemies_vec;
    enemies_vec.push_back(std::make_shared<Skeleton>(bonus * 20, bonus * 40));
    enemies_vec.push_back(std::make_shared<Skeleton>(bonus * 30 + 20, bonus * 30 + 10));
    enemies_vec.push_back(std::make_shared<Skeleton>(bonus * 20, bonus * 30));
    Party enemies = Party(enemies_vec);
    enemies.setPartyPosition(500.f, 450.f);

    return enemies;
}

Party Game::makeBoss()
{
    int bonus = this->map.getCurrentRoomNumber() / 2;
    std::vector<std::shared_ptr<Character>> enemies_vec;
    enemies_vec.push_back(std::make_shared<Skull_Boss>(bonus * 20, bonus * 45));
    Party enemies = Party(enemies_vec);
    enemies.setPartyPosition(500.f, 400.f);

    return enemies;
}

void Game::startBattle()
{
    if (this->map.getCurrentRoom()->getIsLvlHard())
        this->current_fight = std::make_shared<Fight>(this->characters, this->makeBoss());
    else
        this->current_fight = std::make_shared<Fight>(this->characters, this->makeEnemies());
    this->current_state = GAME_STATES::Battle;
    this->characters.changeState(PARTY_STATES::Fighting);
    srand(time(NULL));
}

void Game::battle()
{
    if (this->current_fight->getState() == BATTLE_STATES::PlayersMove)
        this->playersMove();
}

void Game::playersMove()
{
    if (this->event.type == sf::Event::KeyPressed)
    {
        switch (this->event.key.code)
        {
        case sf::Keyboard::Enter:
            this->current_fight->savePreviousAttackerPosition();
            this->current_fight->getAttacker()->setPosition(sf::Vector2f(320.f, 450.f)); // middle - character size - 16 pixels space
            this->current_fight->getAttacker()->changeState(CHARACTER_STATES::CharacterAttack);
            this->current_fight->savePreviousTargetPosition();
            this->current_fight->getTarget()->setPosition(sf::Vector2f(416.f, this->current_fight->getTarget()->getVisuals().getPosition().y)); // middle + 16 pixels space
            this->current_fight->getAttacker()->setAnimCounter(0);
            this->current_fight->changeState(BATTLE_STATES::PlayerAttack);
            break;

        case sf::Keyboard::Right:
            this->current_fight->incrementTargetIndex();
            break;

        default:
            break;
        }
    }
}

void Game::enemiesMove()
{
    this->current_fight->changeState(BATTLE_STATES::ComputerAttack);
    this->current_fight->getAttacker()->changeState(CHARACTER_STATES::CharacterAttack);
    this->current_fight->getAttacker()->setAnimCounter(0);
    this->current_fight->savePreviousAttackerPosition();
    this->current_fight->savePreviousTargetPosition();
    this->current_fight->getAttacker()->setPosition(sf::Vector2f(416.f, this->current_fight->getAttacker()->getVisuals().getPosition().y));
    this->current_fight->getTarget()->setPosition(sf::Vector2f(320.f, 450.f));
}

void Game::playerAttack()
{
    if (this->frame_counter_animations.getElapsedTime().asSeconds() < 0.1f)
        return;

    if (this->current_fight->getAttacker()->getAnimCounter() == this->current_fight->getAttacker()->getMaxAttackFrame())
    {
        this->current_fight->getAttacker()->setIfMoved(true);
        this->current_fight->getAttacker()->setPosition(this->current_fight->getPreviousAttackerPosition());
        this->current_fight->getAttacker()->setAnimCounter(0);
        this->current_fight->getTarget()->setPosition(this->current_fight->getPreviousTargetPosition());
        this->current_fight->getAttacker()->changeState(CHARACTER_STATES::CharacterStand);
        if (this->current_fight->getTarget()->getHealth() == 0)
        {
            this->current_fight->getEnemies().removeCharacter(this->current_fight->getTarget());
            this->current_fight->getEnemies().setPartyPosition(PARTY_POS_FIGHT_ENEMY);
        }
        this->current_fight->updateAfterAttack();
    }
    else
    {
        this->current_fight->getAttacker()->attack(this->current_fight->getTarget());
        this->frame_counter_animations.restart();
    }
}

void Game::computerAttack()
{
    if (this->frame_counter_animations.getElapsedTime().asSeconds() < 0.1f)
        return;

    if (this->current_fight->getAttacker()->getAnimCounter() == this->current_fight->getAttacker()->getMaxAttackFrame())
    {
        this->current_fight->getAttacker()->setIfMoved(true);
        this->current_fight->getAttacker()->setPosition(this->current_fight->getPreviousAttackerPosition());
        this->current_fight->getAttacker()->setAnimCounter(0);
        this->current_fight->getTarget()->setPosition(this->current_fight->getPreviousTargetPosition());
        this->current_fight->getAttacker()->changeState(CHARACTER_STATES::CharacterStand);
        if (this->current_fight->getTarget()->getHealth() == 0)
        {
            this->characters.removeCharacter(this->current_fight->getTarget());
            this->current_fight->getHeroes().removeCharacter(this->current_fight->getTarget());
            this->characters.setPartyPosition(PARTY_START_POSITION);
        }
        this->current_fight->updateAfterAttack();
    }
    else
    {
        this->current_fight->getAttacker()->attack(this->current_fight->getTarget());
    }
    this->frame_counter_animations.restart();
}

void Game::endBattle()
{
    if (this->frame_counter_animations.getElapsedTime().asSeconds() < 1.f)
        return;

    if (this->characters.getSize() == 0)
    {
        this->current_state = GAME_STATES::MExit;
        return;
    }
    else if ((this->current_fight->getEnemies().getSize() == 0) && (this->map.getCurrentRoomNumber() == this->map.getNumberOfRooms() - 1))
    {
        this->current_state = GAME_STATES::MenuVictory;
        return;
    }
    this->current_state = GAME_STATES::inRoom;
    this->map.getCurrentRoom()->setIsFight(false);
    int size = this->characters.getSize();
    for (auto character : this->characters.getCharacters())
    {
        character->setIfMoved(false);
        character->increaseDamage(DAMAGE_BONUS);
        character->increaseHealth(HEALTH_BONUS_DISTRIBUTE / size);
    }
    this->speed_left = CHARACTER_VECTOR_LEFT[int(this->characters.getSize()) - 1];
    this->speed_right = CHARACTER_VECTOR_RIGHT[int(this->characters.getSize()) - 1];
    this->frame_counter_animations.restart();
}

void Game::fight()
{
    if (this->frame_counter_movement.getElapsedTime().asSeconds() >= 0.5f)
    {
        for (auto character : this->characters.getCharacters())
        {
            if (character->getState() == CHARACTER_STATES::CharacterStand)
                character->stand();
        }

        for (auto character : this->current_fight->getEnemies().getCharacters())
        {
            if (character->getState() == CHARACTER_STATES::CharacterStand)
                character->stand();
        }
        this->frame_counter_movement.restart();
    }

    if (this->current_fight->getState() == BATTLE_STATES::PlayerAttack)
        this->playerAttack();

    else if (this->current_fight->getState() == BATTLE_STATES::ComputerAttack)
    {
        this->computerAttack();
    }
}

//************************************//

void Game::changingRoomRight()
{
    if (this->event.type == sf::Event::TextEntered)
        this->event.type = sf::Event::KeyPressed;

    if (this->event.type == sf::Event::KeyPressed)
    {
        if (this->event.key.code == sf::Keyboard::Escape)
            this->current_state = GAME_STATES::MainMenu;
        else if (this->event.key.code == sf::Keyboard::W)
        {
            this->current_state = GAME_STATES::ChangingRoom;
            this->characters.changeState(PARTY_STATES::PartyChangeRoomRight);
        }
        else if (this->event.key.code == sf::Keyboard::A)
            this->current_state = GAME_STATES::inRoom;
    }
    else
    {
        this->characters.changeState(PARTY_STATES::Stand);
        this->characters.changeCharactersState(CHARACTER_STATES::CharacterStand);
    }
}

void Game::changingRoomLeft()
{
    if (this->event.type == sf::Event::TextEntered)
        this->event.type = sf::Event::KeyPressed;

    if (this->event.type == sf::Event::KeyPressed)
    {
        if (this->event.key.code == sf::Keyboard::Escape)
            this->current_state = GAME_STATES::MainMenu;
        else if (this->event.key.code == sf::Keyboard::W)
        {
            this->current_state = GAME_STATES::ChangingRoom;
            this->characters.changeState(PARTY_STATES::PartyChangeRoomLeft);
        }
        else if (this->event.key.code == sf::Keyboard::D)
            this->current_state = GAME_STATES::inRoom;
    }
    else
    {
        this->characters.changeState(PARTY_STATES::Stand);
        this->characters.changeCharactersState(CHARACTER_STATES::CharacterStand);
    }
}

void Game::draw()
{
    this->window->draw(background);
    if (this->current_state == GAME_STATES::MainMenu)
    {
        for (auto option : this->main_menu.getOptions())
            this->window->draw(option);
    }
    else if (this->current_state == GAME_STATES::MExit)
    {
        for (auto option : this->exit_menu.getOptions())
            this->window->draw(option);
    }
    else if (this->current_state == GAME_STATES::MenuVictory)
    {
        for (auto option : this->victory_menu.getOptions())
            this->window->draw(option);
    }
    else
    {
        for (auto character : this->characters.getCharacters())
        {
            this->window->draw(character->getVisuals());
        }
        if (this->current_state == GAME_STATES::Battle)
        {
            for (auto enemy : this->current_fight->getEnemies().getCharacters())
                this->window->draw(enemy->getVisuals());
        }

        this->drawText();
        this->drawArrow();
    }
}

/*          MOVE            */
void Game::stand()
{
    if (this->frame_counter_movement.getElapsedTime().asSeconds() >= 0.5)
    {
        this->characters.charactersStand();
        this->frame_counter_movement.restart();
    }
}

void Game::moveRight()
{
    if (this->background_anim_counter < this->backgroundAnimMax)
    {
        if (this->frame_counter_animations.getElapsedTime().asSeconds() >= 0.1f)
        {
            for (auto character : this->characters.getCharacters())
            {
                character->walkRigth();
            }
            this->frame_counter_animations.restart();
        }
        if (this->frame_counter_movement.getElapsedTime().asMilliseconds() >= 10.f)
        {
            this->background_anim_counter++;
            for (auto character : this->characters.getCharacters())
            {
                character->move(speed_right);
            }
            this->frame_counter_movement.restart();
        }
    }
}

void Game::moveLeft()
{
    if (this->background_anim_counter > 0)
    {
        if (this->frame_counter_animations.getElapsedTime().asSeconds() >= 0.1f)
        {
            for (auto character : this->characters.getCharacters())
            {
                character->walkLeft();
            }
            this->frame_counter_animations.restart();
        }
        if (this->frame_counter_movement.getElapsedTime().asMilliseconds() >= 10.f)
        {
            this->background_anim_counter--;
            for (auto character : this->characters.getCharacters())
            {
                character->move(speed_left);
            }
            this->frame_counter_movement.restart();
        }
    }
}

void Game::moveCharactersToRight()
{
    if (this->characters.getPartyPosition().x < WINDOW_RESOLUTION_HORIZONTAL)
    {
        if (this->frame_counter_animations.getElapsedTime().asSeconds() >= 0.1f)
        {
            for (auto character : this->characters.getCharacters())
            {
                character->walkRigth();
            }
            this->frame_counter_animations.restart();
        }
        if (this->frame_counter_movement.getElapsedTime().asMilliseconds() >= 10.f)
        {
            for (auto character : this->characters.getCharacters())
            {
                character->move(BACKGROUNT_VELOCITY_RIGHT);
            }
            this->frame_counter_movement.restart();
        }
    }
    else if (this->map.getCurrentRoomNumber() != this->map.getNumberOfRooms() - 1)
    {
        this->backgroundAnimMax = this->map.updateBackgrountAnimationCounter();
        this->background_anim_counter = 0;
        this->updateBackgroundRight();
        this->characters.setPartyPosition(-this->characters.getPartyLength(), 450.f);
        this->current_state = GAME_STATES::ChangingRoom;
        this->characters.changeState(PARTY_STATES::PartyEnteringRoomLeft);
    }
}

void Game::moveCharactersFromLeft()
{
    if (this->characters.getPartyPosition().x < 50.f)
    {
        if (this->frame_counter_animations.getElapsedTime().asSeconds() >= 0.1f)
        {
            for (auto character : this->characters.getCharacters())
            {
                character->walkRigth();
            }
            this->frame_counter_animations.restart();
        }
        if (this->frame_counter_movement.getElapsedTime().asMilliseconds() >= 10.f)
        {
            for (auto character : this->characters.getCharacters())
                character->move(BACKGROUNT_VELOCITY_RIGHT);
            this->frame_counter_movement.restart();
        }
    }
    else
    {
        this->characters.changeState(PARTY_STATES::Stand);
        this->characters.changeCharactersState(CHARACTER_STATES::CharacterStand);
        this->characters.charactersStand();
        this->characters.setPartyPosition(PARTY_START_POSITION);
        this->current_state = GAME_STATES::inRoom;
        this->speed_left = CHARACTER_VECTOR_LEFT[int(this->characters.getSize()) - 1];
        this->speed_right = CHARACTER_VECTOR_RIGHT[int(this->characters.getSize()) - 1];
        if (this->map.getCurrentRoomNumber() % 2 == 1) // slower for corridors
        {
            this->speed_left.x *= 0.7f;
            this->speed_right.x *= 0.7f;
        }
    }
}

void Game::moveCharactersToLeft()
{
    if (this->characters.getPartyPosition().x > -this->characters.getPartyLength())
    {
        if (this->frame_counter_animations.getElapsedTime().asSeconds() >= 0.1f)
        {
            for (auto character : this->characters.getCharacters())
            {
                character->walkLeft();
            }
            this->frame_counter_animations.restart();
        }
        if (this->frame_counter_movement.getElapsedTime().asMilliseconds() >= 10.f)
        {
            for (auto character : this->characters.getCharacters())
            {
                character->move(BACKGROUNT_VELOCITY_LEFT);
            }
            this->frame_counter_movement.restart();
        }
    }
    else if (this->map.getCurrentRoomNumber() != this->map.getNumberOfRooms() - 1)
    {
        this->backgroundAnimMax = this->map.updateBackgrountAnimationCounter();
        this->background_anim_counter = this->backgroundAnimMax;
        this->updateBackgroundLeft();
        this->characters.setPartyPosition(800.f, 450.f);
        this->current_state = GAME_STATES::ChangingRoom;
        this->characters.changeState(PARTY_STATES::PartyEnteringRoomRight);
    }
}

void Game::moveCharactersFromRight()
{
    if (this->characters.getPartyPosition().x > 736.f - this->characters.getPartyLength())
    {
        if (this->frame_counter_animations.getElapsedTime().asSeconds() >= 0.1f)
        {
            for (auto character : this->characters.getCharacters())
            {
                character->walkLeft();
            }
            this->frame_counter_animations.restart();
        }
        if (this->frame_counter_movement.getElapsedTime().asMilliseconds() >= 10.f)
        {
            for (auto character : this->characters.getCharacters())
                character->move(BACKGROUNT_VELOCITY_LEFT);
            this->frame_counter_movement.restart();
        }
    }
    else
    {
        this->characters.setPartyPosition(736.f - this->characters.getPartyLength(), 450.f);
        this->characters.changeState(PARTY_STATES::Stand);
        this->characters.changeCharactersState(CHARACTER_STATES::CharacterStand);
        this->characters.charactersStand();
        this->current_state = GAME_STATES::inRoom;
        this->speed_left = CHARACTER_VECTOR_LEFT[int(this->characters.getSize()) - 1];
        this->speed_right = CHARACTER_VECTOR_RIGHT[int(this->characters.getSize()) - 1];
        if (this->map.getCurrentRoomNumber() % 2 == 1) // slower for corridors
        {
            this->speed_left.x *= 0.7f;
            this->speed_right.x *= 0.7f;
        }
    }
}

//          UPDATING            //
void Game::update()
/*
updates current game state
*/
{
    if (this->current_state == GAME_STATES::MainMenu)
    {
        this->updateMenu();
        return;
    }
    if (this->current_state == GAME_STATES::Battle)
    {
        this->updateBattle();
    }
    if (this->current_state == GAME_STATES::MExit)
    {
        this->updateExitMenu();
    }
    if (this->current_state == GAME_STATES::MenuVictory)
    {
        this->updateVictory();
    }
    this->updateCharacters();
    this->updateBackground();
    this->updateText();
    this->updateMousePos();
    this->updateMusic();
    this->updateSoundEffects();
}

void Game::updateMenu()
{
    this->backgroundTexture.loadFromFile(this->main_menu.getBackgroundPath());
    this->background.setTextureRect(sf::IntRect(0, 0, 800, 600));
    for (int index = 0; index <= MAX_MENU_INDEX; ++index)
    {
        if (index == this->main_menu.getSelectedOptionIndex())
            this->main_menu.getOptions()[index].setFillColor(sf::Color::Red);
        else
            this->main_menu.getOptions()[index].setFillColor(sf::Color::White);
    }
}

void Game::updateExitMenu()
{
    this->backgroundTexture.loadFromFile(this->exit_menu.getBackgroundPath());
    this->background.setTextureRect(sf::IntRect(0, 0, 800, 600));
    this->main_menu.getOptions()[0].setFillColor(sf::Color::Red);
}

void Game::updateVictory()
{
    this->backgroundTexture.loadFromFile(this->exit_menu.getBackgroundPath());
    this->background.setTextureRect(sf::IntRect(0, 0, 800, 600));
    this->main_menu.getOptions()[0].setFillColor(sf::Color::Red);
}

void Game::updateBackground()
{
    if (this->current_state != GAME_STATES::MainMenu && this->current_state != GAME_STATES::MExit)
        this->background.setTextureRect(sf::IntRect(background_anim_counter * 2, 0, 800, 600));
}

void Game::updateCharacters()
{
    switch (this->characters.getState())
    {
    case PARTY_STATES::MoveRigth:
        this->moveRight();
        break;

    case PARTY_STATES::MoveLeft:
        this->moveLeft();
        break;

    case PARTY_STATES::PartyChangeRoomRight:
        this->moveCharactersToRight();
        break;

    case PARTY_STATES::PartyChangeRoomLeft:
        this->moveCharactersToLeft();
        break;

    case PARTY_STATES::PartyEnteringRoomLeft:
        this->moveCharactersFromLeft();
        break;

    case PARTY_STATES::PartyEnteringRoomRight:
        this->moveCharactersFromRight();
        break;

    case PARTY_STATES::Fighting:
        this->fight();
        break;

    default:
        this->stand();
        break;
    }
}

void Game::updateBattle()
{
    if (this->frame_counter_animations.getElapsedTime().asSeconds() >= 1.f)
    {
        if (this->current_fight->getState() == BATTLE_STATES::EnemiesMove)
            this->enemiesMove();
        else if (this->current_fight->getState() == BATTLE_STATES::BattleEnd)

            this->endBattle();
        this->frame_counter_animations.restart();
    }
    this->updateArrow();
    this->current_fight->updateAttacker();
    this->current_fight->updateTarget();
}

void Game::updateBackgroundRight()
{
    if (this->map.getCurrentRoomNumber() != map.getNumberOfRooms() - 1)
    {
        this->map.incrementRoomNumber();
        this->backgroundTexture.loadFromFile(this->map.getCurrentRoom()->getBackFile());
        this->background.setTexture(backgroundTexture);
        this->background.setTextureRect(sf::IntRect(0, 0, 800, 600));
    }
}

void Game::updateBackgroundLeft()
{
    if (this->map.getCurrentRoomNumber() != 0)
    {
        this->map.decrementRoomNumber();
        this->backgroundTexture.loadFromFile(this->map.getCurrentRoom()->getBackFile());
        this->background.setTexture(backgroundTexture);
        this->background.setTextureRect(sf::IntRect(this->backgroundAnimMax * 2, 0, 800, 600));
    }
}

void Game::updateText()
{
    if (this->current_state == GAME_STATES::MExit)
        this->roomText.setString("");
    else
        this->roomText.setString(this->map.getCurrentRoom()->getName());

    if (this->current_state == GAME_STATES::WannaChangeRoomLeft)
    {
        this->changeRoomText.setString(TXT_W_TO_LEFT);
        this->changeRoomText.setPosition(sf::Vector2f(float(POS_TXT_CHANGE_LEFT), float(POS_TXT_W_TO_Y)));
    }
    else if (this->current_state == GAME_STATES::WannaChangeRoomRight)
    {
        this->changeRoomText.setString(TXT_W_TO_RIGHT);
        this->changeRoomText.setPosition(sf::Vector2f(float(POS_TXT_CHANGE_RIGHT), float(POS_TXT_W_TO_Y)));
    }
    else
    {
        this->changeRoomText.setString("");
    }
    this->characterParamsText.setString("");
    for (auto character : this->characters.getCharacters())
    {
        if (character->getVisuals().getGlobalBounds().contains(this->mousePosView))
        {
            this->characterParamsText.setString("HP: " + std::to_string(character->getHealth()) + "\nDMG: " + std::to_string(character->getDamage()));
            this->characterParamsText.setPosition(sf::Vector2f(character->getVisuals().getPosition().x + VISUAL_CHAR_PTR_OFFSET, character->getVisuals().getPosition().y - OFFSET_TXT_PARAM_Y));
            break;
        }
    }
    if (this->characterParamsText.getString() == "" && this->current_state == GAME_STATES::Battle)
    {
        for (auto enemy : this->current_fight->getEnemies().getCharacters())
        {
            if (enemy->getVisuals().getGlobalBounds().contains(this->mousePosView))
            {
                this->characterParamsText.setString("HP: " + std::to_string(enemy->getHealth()) + "\nDMG: " + std::to_string(enemy->getDamage()));
                float offset_x = enemy->getVisuals().getLocalBounds().width * enemy->getVisuals().getScale().x / 2;

                this->characterParamsText.setPosition(sf::Vector2f(enemy->getVisuals().getPosition().x + offset_x - 20.f, enemy->getVisuals().getPosition().y - OFFSET_TXT_PARAM_Y));
                break;
            }
        }
    }
    this->whoseTurnText.setString("");
    if (this->current_state == GAME_STATES::Battle)
    {
        if (this->current_fight->getState() == BATTLE_STATES::PlayersMove)
            this->whoseTurnText.setString(TXT_YOURS_TURN);
        else if (this->current_fight->getState() == BATTLE_STATES::EnemiesMove)
            this->whoseTurnText.setString(TXT_ENEMY_TURN);
    }

    this->heroesLvlUpText.setString("");
    if (this->current_state == GAME_STATES::Battle)
    {
        if (this->current_fight->getState() == BATTLE_STATES::BattleEnd && this->characters.getSize() > 0)
            this->heroesLvlUpText.setString(TXT_HEROS_LVL_UP);
    }
}

void Game::updateMousePos()
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateMusic()
{
    if (this->current_state == GAME_STATES::Battle)
    {
        if (this->fightMusic.getStatus() != sf::SoundSource::Status::Playing)
        {
            this->mainMusic.pause();
            this->fightMusic.play();
        }
    }
    else if (this->current_state == GAME_STATES::MenuVictory)
    {
        if (this->winMusic.getStatus() != sf::SoundSource::Status::Playing)
        {
            this->mainMusic.pause();
            this->fightMusic.pause();
            this->winMusic.play();
        }
    }
    else if (this->current_state == GAME_STATES::MExit)
    {
        if (this->retreatMusic.getStatus() != sf::SoundSource::Status::Playing)
        {
            this->mainMusic.pause();
            this->fightMusic.pause();
            this->retreatMusic.play();
        }
    }
    else if (this->mainMusic.getStatus() != sf::SoundSource::Status::Playing)
    {
        this->fightMusic.stop();
        this->mainMusic.play();
    }
}

void Game::updateSoundEffects()
{
    if (this->current_state == GAME_STATES::Battle)
    {
        switch (this->current_fight->getState())
        {
        case BATTLE_STATES::PlayerAttack:
            if (this->hero_attack_sound.getStatus() != sf::SoundSource::Status::Playing)
            {
                this->hero_attack_sound.play();
            }
            break;
        case BATTLE_STATES::ComputerAttack:
            if (this->enemy_attack_sound.getStatus() != sf::SoundSource::Status::Playing)
            {
                this->enemy_attack_sound.play();
            }
            break;
        case BATTLE_STATES::BattleEnd:
            if ((this->map.getCurrentRoomNumber() != this->map.getNumberOfRooms() - 1) && (this->current_fight->getHeroes().getSize() != 0))
            {
                if (this->battle_win_sound.getStatus() != sf::SoundSource::Status::Playing)
                {
                    this->battle_win_sound.play();
                }
            }
            break;
        }
    }
    switch (this->current_state)
    {
    case GAME_STATES::MExit:
        if (this->game_over_sound.getStatus() != sf::SoundSource::Status::Playing)
        {
            this->game_over_sound.play();
            if (this->game_over_buffer.getDuration().asSeconds() == this->game_over_sound.getPlayingOffset().asSeconds())
            {
                this->flawless_victory_sound.stop();
            }
        }
        break;
    case GAME_STATES::MenuVictory:
        if (this->flawless_victory_sound.getStatus() != sf::SoundSource::Status::Playing)
        {
            this->flawless_victory_sound.play();
            if (this->flawless_victory_buffer.getDuration().asSeconds() == this->flawless_victory_sound.getPlayingOffset().asSeconds())
            {
                this->flawless_victory_sound.stop();
            }
        }
        break;
    }
}

void Game::updateArrow()
{

    if (this->current_fight->getState() != BATTLE_STATES::PlayersMove)
        return;

    auto pos_vec = this->current_fight->getTarget()->getVisuals().getPosition();
    float offset_x = (this->current_fight->getTarget()->getVisuals().getLocalBounds().width * this->current_fight->getTarget()->getVisuals().getScale().x / 2) - OFFSET_ARROW_X;

    this->arrowSprite.setPosition(sf::Vector2f(pos_vec.x + offset_x, pos_vec.y - OFFSET_ARROW_Y));
}

void Game::drawText()
{
    if (roomText.getString() != "")
        this->window->draw(roomText);

    if (this->changeRoomText.getString() != "")
        this->window->draw(changeRoomText);

    if (this->characterParamsText.getString() != "")
        this->window->draw(characterParamsText);

    if (this->whoseTurnText.getString() != "")
        this->window->draw(whoseTurnText);

    if (this->heroesLvlUpText.getString() != "")
        this->window->draw(heroesLvlUpText);
}

void Game::drawArrow()
{
    if (this->current_state == GAME_STATES::Battle)
    {
        if (this->current_fight->getState() == BATTLE_STATES::PlayersMove)
            this->window->draw(this->arrowSprite);
    }
}