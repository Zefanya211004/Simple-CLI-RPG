# Simple-CLI-RPG


## Changes Log:
3/24/26
- Added delay after Skill & Stat assignment
- Slows the Skill & Stat display after assignment
- Added a 'delayText()' function

8/25/26
Progress:
- Seperate into header and source files
- Adjusting header files (Character.hpp & Utils.hpp)
    -- Modified Character.hpp to remove parameter that needed
        Character &character as it's redundant
    -- Change Utility from struct into namespace
- Created 2 source files (Character.cpp & Utils.cpp)