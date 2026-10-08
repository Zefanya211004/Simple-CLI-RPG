#pragma once
#include <string>
#include <array>
#include <vector>
#include "Item.hpp"

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

// skillType::COUNT because we need the total count of skill and we want to convert it to int for the array

struct Skill
{
    std::array<int, static_cast<int>(skillType::COUNT)> values;
};

class Character
{
private:
    int health;
    int armor;
    int level = 1;
    int exp = 1;
    Stat stat;
    Skill skill;
    std::string name;
    std::vector<Item> inventory;
    Weapon equipped_weapon;

public:
    Character(std::string char_name, int char_health, int char_armor);

    void gainStat();
    void gainSkill();
    void levelUp();
    void gainExp(int exp);

    int getStat(statType type) const;
    int getSkill(const Stat &skill, statType type) const;
    int checkInventory(Character &Character) const;
    bool isDead() const;
};