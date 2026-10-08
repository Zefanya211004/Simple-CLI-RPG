#pragma once
#include <string>
#include "Character.hpp"

namespace Utility
{
    int getInput(int min, int max);
    void delayText(int x);
    std::string statTypeToString(statType s);
    std::string skillTypeToString(skillType s);
};