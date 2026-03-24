#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <variant>
#include <unistd.h>
#include <thread>

enum class itemType
{
    CONSUMABLE,
    WEAPON,
    MISC
};

enum class weaponType
{
    GUNS,
    ENERGY,
    MELEE,
    UNARMED
};

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

struct Consumable
{
    std::string name;
    int value;
};

struct Weapon
{
    std::string name;
    weaponType type;
    int damage;
    int accuracy;
};

struct Misc
{
    std::string name;
    std::string description;
};

using Item = std::variant<Weapon, Consumable, Misc>;

enum class statType
{
    Strength,
    Perception,
    Endurance,
    Charisma,
    Intelligence,
    Agility,
    Luck,
    COUNT
};

struct Stat
{
    std::array<int, static_cast<int>(statType::COUNT)> values;
};

enum class skillType
{
    Guns,
    Energy,
    Unarmed,
    Melee,
    Throwing,
    Medic,
    Sneak,
    Lockpick,
    Traps,
    Survival,
    Science,
    Repair,
    Speech,
    Barter,
    Gambling,
    COUNT
};

struct Skill
{
    std::array<int, static_cast<int>(skillType::COUNT)> values;
};

// skillType::COUNT because we need the total count of skill and we want to convert it to int for the array

struct Character
{
    int health = 100;
    int level = 1;
    int exp = 0;
    int armor = 10;
    Stat stat;
    Skill skill;
    std::string name;
    std::vector<Item> inventory;
    Weapon equipped_weapon;
};

struct EncounterEnemy
{
    Character enemy;
};

struct Quest
{
    std::string quest_name;
    std::vector<Item> reward;
    int exp_reward;
    std::vector<EncounterEnemy> enemy_list;
};

int getInput(int min, int max)
{
    int input;

    while (true)
    {
        std::cout << "Choose a number between " << min << " - " << max << "..." << std::endl;

        if (std::cin >> input)
        {
            if (input >= min && input <= max)
            {
                return input;
            }
        }
        else
        {
            std::cout << "Invalid Input, Try again" << std::endl;
            std::cin.clear();
            std::cin.ignore(1000);
        }
    }
}

void delayText(int x) {
    std::this_thread::sleep_for(std::chrono::milliseconds(x)); //1 second is 1000 ms
}

int getStat(const Stat &stat, statType type)
{
    return stat.values[static_cast<int>(type)];
}

int getSkill(const Skill &skill, skillType type)
{
    return skill.values[static_cast<int>(type)];
}

std::string statTypeToString(statType s)
{
    switch (s)
    {
    case statType::Strength:
        return "Strength";
    case statType::Perception:
        return "Perception";
    case statType::Endurance:
        return "Endurance";
    case statType::Charisma:
        return "Charisma";
    case statType::Intelligence:
        return "Intelligence";
    case statType::Agility:
        return "Agility";
    case statType::Luck:
        return "Luck";
    default:
        return "Unknown";
    }
}

std::string skillTypeToString(skillType s)
{
    switch (s)
    {
    case skillType::Guns:
        return "Guns";
    case skillType::Energy:
        return "Energy";
    case skillType::Unarmed:
        return "Unarmed";
    case skillType::Melee:
        return "Melee";
    case skillType::Throwing:
        return "Throwing";
    case skillType::Medic:
        return "Medic";
    case skillType::Sneak:
        return "Sneak";
    case skillType::Lockpick:
        return "Lockpick";
    case skillType::Traps:
        return "Traps";
    case skillType::Survival:
        return "Survival";
    case skillType::Science:
        return "Science";
    case skillType::Repair:
        return "Repair";
    case skillType::Speech:
        return "Speech";
    case skillType::Barter:
        return "Barter";
    case skillType::Gambling:
        return "Gambling";
    default:
        return "Unknown";
    }
}

Character CharacterCreation()
{
    Character player;

    std::cout << "Welcome to Character Creation!" << std::endl;
    std::cout << "What's your name?" << std::endl;
    std::cout << "Type your name: ";
    std::cin >> player.name;
    std::cout << "Hello " << player.name << "!" << std::endl;

    // Stat assignment
    std::cout << "Assign your Stats!" << std::endl;
    for (int i = 0; i < static_cast<int>(statType::COUNT); i++) // loop to print stat string and assign the points
    {
        auto st = static_cast<statType>(i);
        std::cout << statTypeToString(st) << ": ";
        std::cin >> player.stat.values[i];
    }

    std::cout << "Stat assignment done!" << std::endl;

    delayText(1000);

    for (int i = 0; i < static_cast<int>(statType::COUNT); i++) // loop to print stat string after done
    {
        auto st = static_cast<statType>(i);
        std::cout << statTypeToString(st) << ": " << player.stat.values[i] << std::endl;
        delayText(500);
    }

    // Skill assignment
    std::cout << "Assign your Skills!" << std::endl;
    for (int i = 0; i < static_cast<int>(skillType::COUNT); i++)
    {
        auto st = static_cast<skillType>(i);
        std::cout << skillTypeToString(st) << ": ";
        std::cin >> player.skill.values[i];
    }

    std::cout << "Skill Assignment Done!" << std::endl;

    delayText(1000);

    for (int i = 0; i < static_cast<int>(skillType::COUNT); i++)
    {
        auto st = static_cast<skillType>(i);
        std::cout << skillTypeToString(st) << ": " << player.skill.values[i] << std::endl;
        delayText(500);
    }

    return player;
}

void gainStat(Character &character)
{
    std::cout << "Choose Stat to Allocate 1 point" << std::endl;

    for (int i = 0; i < static_cast<int>(statType::COUNT); i++)
    {
        std::cout << i << ". " << statTypeToString(static_cast<statType>(i)) << " : " << character.stat.values[i] << std::endl;
    }

    int choice = getInput(0, static_cast<int>(statType::COUNT) - 1);

    character.stat.values[choice] += 1;
}

void gainSkill(Character &character)
{
    std::cout << "Choose Skill to Allocate points with" << std::endl;

    for (int i = 0; i < static_cast<int>(skillType::COUNT); i++)
    {
        std::cout << i << ". " << skillTypeToString(static_cast<skillType>(i)) << " : " << character.skill.values[i] << std::endl;
    }

    int choice = getInput(0, static_cast<int>(skillType::COUNT) - 1);

    character.skill.values[choice] += 20; // To do: Improve the skill points gained
}

void levelUp(Character &character)
{
    character.level++;
    std::cout << "You're now Level " << character.level << "!" << std::endl;
    gainStat(character);
    gainSkill(character);
}

void gainExp(int exp, Character &character)
{
    character.exp += exp;
    int expReq = 21 * (3 * character.level + 2) * (character.level - 1);
    if (character.exp >= expReq)
    {
        levelUp(character);
    }
}

int hitChance(Character &character, Character &enemy)
{
    int chance = 0;

    auto &weapon = character.equipped_weapon; // use auto to automatically detect the variable type

    switch (weapon.type)
    {
    case (weaponType::GUNS):
        chance = getSkill(character.skill, skillType::Guns) +
                 round(getStat(character.stat, statType::Perception) * 0.5f); // round is used to round the value from float to integer
        break;
    case (weaponType::ENERGY):
        chance = getSkill(character.skill, skillType::Energy) +
                 round(getStat(character.stat, statType::Perception) * 0.5f);
        break;
    case (weaponType::MELEE):
        chance = getSkill(character.skill, skillType::Melee) +
                 round(getStat(character.stat, statType::Strength) * 0.5f);
        break;
    case (weaponType::UNARMED):
        chance = getSkill(character.skill, skillType::Unarmed) +
                 round(getStat(character.stat, statType::Strength) * 0.5f);
        break;
    default:
        chance = 0;
        break;
    }

    // Weapon Accuracy affects hit chance
    chance += weapon.accuracy;

    // Enemy Agility Stat affects hit chance(To do: Rework)
    chance -= (getStat(enemy.stat, statType::Agility));

    if (chance > 95)
        chance = 95; // chance max cap at 95

    if (chance < 15)
        chance = 15; // chance min cap at 15

    return chance;
}

int damageCalculation(Character &character, Character &enemy)
{
    int damage = character.equipped_weapon.damage;

    bool isCritical = (rand() % 100) < getStat(character.stat, statType::Luck);

    if (isCritical)
    {
        damage += round(damage * 0.7f); // crit is 70% more damage;
    }

    damage -= enemy.armor;

    if (damage < 0)
        damage = 0;

    return damage;
}

void performAttack(Character &character, Character &enemy)
{
    int cth = hitChance(character, enemy); // cth = chance to hit

    bool diceRoll = (rand() % 100) <= cth;

    if (diceRoll)
    {
        int attackDamage = damageCalculation(character, enemy);

        enemy.health -= attackDamage;
        std::cout << "You hit the enemy for " << attackDamage << " points!" << std::endl;
    }
    else
    {
        std::cout << "Your Attack Missed!" << std::endl;
    }
}

bool isDead(Character &character)
{
    if (character.health <= 0)
    {
        return 1;
    }
    else
        return 0;
}

int checkInventory(Character &character)
{
    std::cout << "Checking Inventory..." << std::endl;

    for (std::size_t i = 0; i < character.inventory.size(); i++)
    {
        auto &slot = character.inventory[i];

        std::visit([i](auto &item)
                   { std::cout << i << ". Name: " << item.name << std::endl; }, slot);

        if (std::holds_alternative<Weapon>(slot))
        {
            Weapon &w = std::get<Weapon>(slot);
            std::cout << "Damage: " << w.damage << "\nAccuracy: " << w.accuracy << std::endl;
        }

        if (std::holds_alternative<Consumable>(slot))
        {
            Consumable &c = std::get<Consumable>(slot);
            std::cout << "Health Points: " << c.value << std::endl;
            // character.inventory.erase(slot);
        }

        if (std::holds_alternative<Misc>(slot))
        {
            Misc &m = std::get<Misc>(slot);
            std::cout << "Description: " << m.description << std::endl;
        }
    }

    std::cout << "What do you want to do?\n"
              << "1. Use Item\n"
              << "2. Exit Inventory" << std::endl;
    int choice = getInput(1, 2);

    switch (choice)
    {
    case 1:
    {
        std::cout << "Type the index of item that you want to use..." << std::endl;

        int index;
        std::cin >> index;

        if (index < 0 || index >= static_cast<int>(character.inventory.size()))
        {
            std::cout << "Invalid Item Index..." << std::endl;
            break;
        }

        auto &slot = character.inventory[index];

        if (std::holds_alternative<Weapon>(slot))
        {
            character.equipped_weapon = std::get<Weapon>(slot);
        }
        else if (std::holds_alternative<Consumable>(slot))
        {
            Consumable &c = std::get<Consumable>(slot);
            character.health += c.value;
        }
        else if (std::holds_alternative<Misc>(slot))
        {
            std::cout << "*Implement Misc Item usage later" << std::endl;
        }
    }
    break;
    case 2:
        return 1;
    default:
        break;
    }

    return 0;
}

PlayerTurnOutcome playerTurn(Character &character, Character &enemy)
{
    std::cout << "Choose an action!\n"
              << "1. Attack\n"
              << "2. Open Inventory\n"
              << "3. Talk your way\n"
              << std::endl;
    int choice = getInput(1, 3);

    switch (choice)
    {
    case 1:
        performAttack(character, enemy);
        return PlayerTurnOutcome::NORMAL;
    case 2:
        checkInventory(character);
        return PlayerTurnOutcome::NORMAL;
    case 3:
        if (getSkill(character.skill, skillType::Speech) >= rand() % 100)
        {
            std::cout << "You managed to talk your way out";
            return PlayerTurnOutcome::ESCAPE;
        }
        else
        {
            std::cout << "You failed to talk your way out..." << std::endl;
            return PlayerTurnOutcome::NORMAL;
        }
    default:
        break;
    }

    return PlayerTurnOutcome::NORMAL;
}

void enemyTurn(Character &enemy, Character &character)
{
    performAttack(enemy, character);
}

CombatOutcome combatLoop(Character &character, Character &enemy)
{
    while (character.health > 0 && enemy.health > 0)
    {
        std::cout << "Your Health : " << character.health << "\n"
                  << "Enemy Health : " << enemy.health << std::endl;

        if (getStat(character.stat, statType::Agility) >= getStat(enemy.stat, statType::Agility)) // See who gets the first turn
        {
            auto result = playerTurn(character, enemy);

            if (result == PlayerTurnOutcome::ESCAPE)
                return CombatOutcome::PLAYER_ESCAPE;

            if (isDead(enemy))
                break;

            enemyTurn(enemy, character);
        }
        else
        {
            enemyTurn(enemy, character);

            if (isDead(character))
                break;

            auto result = playerTurn(character, enemy);

            if (result == PlayerTurnOutcome::ESCAPE)
                return CombatOutcome::PLAYER_ESCAPE;
        }

        if (isDead(character))
        {
            std::cout << "You're dead..., with no one knowing your story" << std::endl;
            return CombatOutcome::PLAYER_LOSE;
        }
        else if (isDead(enemy))
        {
            std::cout << "You won..., you delayed your time today" << std::endl;
            gainExp(enemy.level * 100, character);
            return CombatOutcome::PLAYER_WIN;
        }
    }

    return CombatOutcome::UNKNOWN;
}

int main()
{
    std::cout << "Welcome to RPG!" << std::endl;
    std::cout << "1. Play game\n"
              << "2. Exit" << std::endl;
    int main_menu = getInput(1, 2);
    switch (main_menu)
    {
    case 1:
    {
        std::cout << "Playing Game..." << std::endl;
        Character player = CharacterCreation();
        break;
    }

    case 2:
        std::cout << "Exiting Game..." << std::endl;
        break;

    default:
        break;
    }
}
