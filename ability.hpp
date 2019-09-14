//
//  ability.hpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-23.
//  Copyright © 2017 马源浩. All rights reserved.
//

#ifndef ability_hpp
#define ability_hpp

#include <iostream>
#undef None


enum class Key {Kill, Return, Recharges, Remove, Resurrect, Magic, Alldamage, Addah, AllAddah, Damage, Sum, None};
enum class Timer {Start, End, Enter, Death, None};

struct Ability{
    Key key;
    Timer timer;
    int hit;
    int life;
    int effect;
    std::string name;
};

#endif /* ability_hpp */
