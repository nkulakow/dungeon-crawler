#include "Fight.h"

Fight::Fight(const Party &fheroes, const Party &fenemies)
{
    this->heroes = fheroes;
    this->enemies = fenemies;
    this->round_counter = 1;
    this->end_of_round = false;
    this->current_state = BATTLE_STATES::PlayersMove;
    this->moving_hero_index = 0;
    this->target_index = 0;
    this->attacker_index = 0;
    this->attacker = this->heroes.getCharacters()[attacker_index];
    this->target = this->enemies.getCharacters()[target_index];
    this->getQueue();
    for (auto character : this->heroes.getCharacters())
        character->changeState(CHARACTER_STATES::CharacterStand);

    for (auto character : this->enemies.getCharacters())
        character->changeState(CHARACTER_STATES::CharacterStand);
}

void Fight::changeState(const int new_state)
{
    this->current_state = new_state;
}

void Fight::getQueue()
{
    for (auto hero : this->heroes.getCharacters())
        this->heroes_queue.push_back(hero);

    for (auto enemy : this->enemies.getCharacters())
        this->enemies_queue.push_back(enemy);
}

void Fight::incrementTargetIndex()
{
    unsigned int max_index;
    if (this->current_state == BATTLE_STATES::PlayersMove)
        max_index = this->enemies.getSize();
    else
        max_index = this->heroes.getSize();

    --max_index;

    if (this->target_index >= max_index)
        this->target_index = 0;
    else
        this->target_index++;
}

void Fight::updateTarget()
{
    if (this->current_state == BATTLE_STATES::PlayerAttack || this->current_state == BATTLE_STATES::PlayersMove)
        this->target = this->enemies.getCharacter(this->target_index);

    else if (this->current_state == BATTLE_STATES::ComputerAttack || this->current_state == BATTLE_STATES::EnemiesMove)
        this->target = this->heroes.getCharacter(this->target_index);
}

void Fight::updateAttacker()
{
    if (this->current_state == BATTLE_STATES::ComputerAttack || this->current_state == BATTLE_STATES::EnemiesMove)
        this->attacker = this->enemies.getCharacter(this->attacker_index);

    else if (this->current_state == BATTLE_STATES::PlayerAttack || this->current_state == BATTLE_STATES::PlayersMove)
        this->attacker = this->heroes.getCharacter(this->attacker_index);
}

void Fight::updateAfterAttack()
{
    if (this->heroes.getSize() == 0 || this->enemies.getSize() == 0)
    {
        this->current_state = BATTLE_STATES::BattleEnd;
        return;
    }

    int index = 0;
    if (this->current_state == BATTLE_STATES::ComputerAttack)
    {
        while (index < this->heroes.getSize() && heroes.getCharacters()[index]->ifMoved())
        {
            ++index;
        }
        if (index < this->heroes.getSize())
        {
            this->current_state = BATTLE_STATES::PlayersMove;
            this->attacker_index = index;
            this->target_index = 0;
            this->updateAttacker();
            this->updateTarget();
            return;
        }
        index = 0;
        while (index < this->enemies.getSize() && enemies.getCharacters()[index]->ifMoved())
        {
            ++index;
        }
        if (index < this->enemies.getSize())
        {
            this->current_state = BATTLE_STATES::EnemiesMove;
            this->attacker_index = index;
            this->target_index = rand() % int(this->heroes.getSize());
            this->updateAttacker();
            this->updateTarget();
            return;
        }
        for (auto character : this->heroes.getCharacters())
        {
            character->setIfMoved(false);
        }
        for (auto character : this->enemies.getCharacters())
        {
            character->setIfMoved(false);
        }
        this->current_state = BATTLE_STATES::PlayersMove;
        this->attacker_index = 0;
        this->target_index = 0;
        this->updateAttacker();
        this->updateTarget();
        return;
    }
    else if (this->current_state == BATTLE_STATES::PlayerAttack)
    {
        index = 0;
        while (index < this->enemies.getSize() && enemies.getCharacters()[index]->ifMoved())
        {
            ++index;
        }

        if (index < this->enemies.getSize())
        {
            this->current_state = BATTLE_STATES::EnemiesMove;
            this->attacker_index = index;
            this->target_index = rand() % int(this->heroes.getSize());
            this->updateAttacker();
            this->updateTarget();
            return;
        }
        index = 0;
        while (index < this->heroes.getSize() && heroes.getCharacters()[index]->ifMoved())
        {
            ++index;
        }

        if (index < this->heroes.getSize())
        {
            this->current_state = BATTLE_STATES::PlayersMove;
            this->attacker_index = index;
            this->target_index = 0;
            this->updateAttacker();
            this->updateTarget();
            return;
        }
        for (auto character : this->heroes.getCharacters())
        {
            character->setIfMoved(false);
        }
        for (auto character : this->enemies.getCharacters())
        {
            character->setIfMoved(false);
        }
        this->current_state = BATTLE_STATES::PlayersMove;
        this->attacker_index = 0;
        this->target_index = 0;
        this->updateAttacker();
        this->updateTarget();
        return;
    }
}