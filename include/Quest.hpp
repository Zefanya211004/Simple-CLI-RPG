#pragma once
#include <string>
#include <vector>
#include "Character.hpp"
#include "Item.hpp"

class Quest
{
private:
    std::string name;
    std::vector<Item> reward;
    int exp_reward;
    std::vector<Character> enemy_list;

public:
    Quest(std::string quest_name, std::vector<Item> quest_reward, int quest_exp_reward, std::vector<Character> enemy_list);
};