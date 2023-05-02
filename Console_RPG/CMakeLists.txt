cmake_minimum_required(VERSION 3.23)
project(Console_RPG)

set(CMAKE_CXX_STANDARD 23)

add_executable(Console_RPG main.cpp Game.cpp Game.h Character.cpp Character.h Item.cpp Item.h Inventory.cpp Inventory.h Weapon.cpp Weapon.h Armor.cpp Armor.h Enemy.cpp Enemy.h Events.cpp Events.h Puzzle.cpp Puzzle.h dArray.cpp dArray.h Helmet.cpp Helmet.h Gauntlet.cpp Gauntlet.h Torso.cpp Torso.h Legs.cpp Legs.h)
