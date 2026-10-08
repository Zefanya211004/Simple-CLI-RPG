#include "Character.hpp"
#include "Utils.hpp"
#include <iostream>

Character::Character(std::string char_name, int char_health, int char_armor)
    : health(char_health), armor(char_armor), name(char_name)
{
}

bool Character::isDead() const
{
    return health <= 0;
}

int Character::getStat(const statType type) const
{
    return stat.values[static_cast<int>(type)];
}

void Character::gainStat()
{
    std::cout << "Choose Stat to Allocate 1 point to" << std::endl;

    for (int i = 0; i < static_cast<int>(statType::COUNT); i++)
    {
        std::cout << i << ". " << Utility::statTypeToString(static_cast<statType>(i)) << " : " << stat.values[i] << std::endl;
    }

    int choice = Utility::getInput(0, static_cast<int>(statType::COUNT) - 1);

    stat.values[choice] += 1;
}

void Character::levelUp()
{
    level++;
    std::cout << "You're now Level " << level << "!." << std::endl;
    gainStat();
    gainSkill();
}

void Character::gainExp(int amount)
{
    exp += amount;
    int expReq = 21 * (3 * level + 2) * (level - 1);
    if (exp >= expReq)
    {
        levelUp();
    }
}