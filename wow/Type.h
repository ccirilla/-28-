#ifndef __TYPE_H__
#define __TYPE_H__ 


#include <string>
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using std::map;
using std::vector;

enum Color { 
    MID=0,
    RED, 
    BLUE 
};

enum WarriorType { 
    DRAGON_TYPE, 
    NINJA_TYPE, 
    ICEMAN_TYPE, 
    LION_TYPE, 
    WOLF_TYPE 
};

enum WeaponType{ 
    SWORD_TYPE, 
    BOMB_TYPE, 
    ARROW_TYPE 
};

using std::string;
inline string toString(Color color) 
{
    return (color == RED) ? string("red"): string("blue");
}

inline string toString(WarriorType type)
{
    switch(type) {
    case DRAGON_TYPE: return "dragon";
    case NINJA_TYPE:  return "ninja";
    case ICEMAN_TYPE: return "iceman";
    case LION_TYPE:   return "lion";
    case WOLF_TYPE:   return "wolf";
    default:
                      return string();
    }

}

inline string toString(WeaponType type) 
{
    switch(type) {
    case SWORD_TYPE: return "sword";
    case BOMB_TYPE:  return "bomb";
    case ARROW_TYPE: return "arrow";
    default:
                     return string();

    }

}

class Warrior;
class WarriorView;
class City;
class Weapon;
class WeaponView;

using std::shared_ptr;

using WarriorPtr = shared_ptr<Warrior>;
using WarriorViewPtr = shared_ptr<WarriorView>;
using WeaponPtr = shared_ptr<Weapon>;
using WeaponViewPtr = shared_ptr<WeaponView>;



#endif
