#pragma once
#include <string>
#include <vector>
#include "Character.hpp"
#include "Item.hpp"
#include "Quest.hpp"
#include "Utils.hpp"

enum class CombatOutcome
{
    PLAYER_WIN,
    PLAYER_LOSE,
    PLAYER_ESCAPE,
    UNKNOWN
};

enum class PlayerTurnOutcome
{
    ESCAPE,
    NORMAL
};

class GameEngine
{
private:
    Character player;
    std::vector<Quest> quest_list;
    int hitChance(Character &character, Character &enemy);
    int damageCalculation(Character &character, Character &enemy);
    void performAttack(Character &character, Character &enemy);
    PlayerTurnOutcome playerTurn(Character &character, Character &enemy);
    void enemyTurn(Character &enemy, Character &character);
    CombatOutcome combatLoop(Character &character, Character &enemy);

public:
    GameEngine(Character player_character);
    Character CharacterCreation();
};