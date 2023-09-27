#include "Party.h"

Party::Party(std::vector<std::shared_ptr<Character>> characters) : characters(characters) {}

std::vector<std::shared_ptr<Character>> &Party::getCharacters()
{
    return this->characters;
}

void Party::addCharacter(std::shared_ptr<Character> new_character)
{
    this->characters.push_back(new_character);
    // this->setPartyPosition(this->getPartyPosition().x, this->getPartyPosition().y);
}

std::shared_ptr<Character> Party::getCharacter(size_t index) const
{
    if (index < this->getSize())
    {
        return this->characters[index];
    }
    else
    {
        throw std::invalid_argument("Index out of rangefffffff");
    }
}

const size_t Party::getSize() const
{
    return this->characters.size();
}

const float Party::getPartyLength() const
{
    float length = 0;
    for (auto character : this->characters)
    {
        length += 128.f;
    }
    length -= 64.f;
    return length;
}

void Party::removeFromPosition(size_t index)
{
    if (index < this->getSize())
    {
        this->characters.erase(this->characters.begin() + index);
    }
    else
    {
        throw std::invalid_argument("Index out of range");
    }
}

void Party::removeCharacter(const std::shared_ptr<Character> &character)
{
    auto checked = this->characters.begin();
    while (checked != this->characters.end())
    {
        if (*checked == character)
        {
            this->characters.erase(checked);
        }
        else
        {
            checked++;
        }
    }
}

void Party::pop()
{
    this->characters.pop_back();
}

void Party::changeState(const int new_state)
{
    this->current_state = new_state;
}

void Party::charactersStand()
{
    for (auto character : this->characters)
    {
        character->stand();
    }
}

void Party::changeCharactersState(const int new_state)
{
    for (auto character : this->characters)
    {
        character->changeState(new_state);
    }
}

void Party::setPartyPosition(const float position_x, const float position_y)
{
    float dislocation = 0.f;
    for (auto character : this->characters)
    {
        character->setPosition(position_x + dislocation, position_y);
        dislocation += 85.f;
    }
}

void Party::setPartyPosition(const sf::Vector2f &new_position)
{
    this->setPartyPosition(new_position.x, new_position.y);
}
