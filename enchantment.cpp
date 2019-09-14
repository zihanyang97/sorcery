//
//  enchantment.cpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-22.
//  Copyright © 2017 马源浩. All rights reserved.
//

#include "enchantment.hpp"


Enchantment::Enchantment(std::string name, std::string info, int cost, std::string op): Card(name, info, cost), op(op){}

std::string Enchantment::getType(){
    return type;
}

void Enchantment::add(Minion& min){
    min.add_enchant(name);
}

void Enchantment::Display(){
    card_template_t t;
    if(name == "Silence"){
        t = display_enchantment(name, cost, showInfo());
    }else{
        t = display_enchantment_attack_defence(name, cost, showInfo(), op + "2", op + "2");
    }
    for(int i = 0; i < t.size(); ++i){
        std::cout << t[i] << std::endl;
    }
}

card_template_t Enchantment::getDigit(){
    card_template_t t;
    if(name == "Silence"){
        t = display_enchantment(name, cost, showInfo());
    }else{
        t = display_enchantment_attack_defence(name, cost, showInfo(), op + "2", op + "2");
    }
    return t;
}
