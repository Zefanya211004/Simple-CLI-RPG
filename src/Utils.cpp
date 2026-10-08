#include "Utils.hpp"
#include <iostream>
#include <thread>
#include <cstdlib>
#

namespace Utility
{
    int getInput(int min, int max)
    {
        int input;

        while (true)
        {
            std::cout << "Choose a number between " << min << " and " << max << std::endl;

            if (std::cin >> input)
            {
                if (input >= min && input <= max)
                {
                    return input;
                }

                else
                {
                    std::cout << "Invalid input, try again!" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(1000);
                }
            }
        }
    }

    void delayText(int x)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(x));
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
}
