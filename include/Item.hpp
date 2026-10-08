#pragma once
#include <string>
#include <variant>

enum class weapon_type
{
    GUNS,
    ENERGY,
    MELEE,
    UNARMED
};

struct Consumable
{
    std::string name;
    int value = 0;
};

struct Weapon
{
    std::string name;
    weapon_type type;
    int damage = 0;
    int accuracy = 100;
};

struct Misc
{
    std::string name;
    std::string description;
};

using Item = std::variant<Weapon, Consumable, Misc>;
