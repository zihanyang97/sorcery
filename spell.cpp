//
//  spell.cpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-29.
//  Copyright © 2017 马源浩. All rights reserved.
//

#include "spell.hpp"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

Spell::Spell(string name, string info, int cost, Key key, Timer timer, int hit, int life, int effect, std::string sum): Card{name, info, cost, key, timer, hit, life, effect, sum}{

}

string Spell::getType() {
    return type;
}

void Spell::Display(){
    card_template_t t = display_spell(name, cost, showInfo());
    for(int i = 0; i < t.size(); ++i){
        std::cout << t[i] << std::endl;
    }
}

card_template_t Spell::getDigit(){
    card_template_t t = display_spell(name, cost, showInfo());
    return t;
}
