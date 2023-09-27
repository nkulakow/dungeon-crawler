#include "../Characters/Character.h"
#include <vector>
#include <memory>

#ifndef PARTY_H
#define PARTY_H

class Party
{
private:
    std::vector<std::shared_ptr<Character>> characters;
    int current_state;

public:
    Party(std::vector<std::shared_ptr<Character>> characters = {});
    std::vector<std::shared_ptr<Character>> &getCharacters();
    void addCharacter(std::shared_ptr<Character> new_character);
    std::shared_ptr<Character> getCharacter(size_t index) const;
    const size_t getSize() const;
    const float getPartyLength() const;
    const sf::Vector2f &getPartyPosition() const { return this->characters[0]->getVisuals().getPosition(); }
    void removeCharacter(const std::shared_ptr<Character> &character);
    void removeFromPosition(size_t index);
    void pop();
    void changeState(const int new_state);
    const int getState() const { return this->current_state; }
    void charactersStand();
    void changeCharactersState(const int new_state);

    void setPartyPosition(const float position_x, const float position_y);
    void setCharacters(std::vector<std::shared_ptr<Character>> &new_characters) { this->characters = new_characters; }
    void setPartyPosition(const sf::Vector2f &new_position);
};

#endif