//
//  card.cpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-26.
//  Copyright © 2017 马源浩. All rights reserved.
//

#include "card.hpp"

Card::Card(std::string name, std::string info, int cost):name(name), info(info), cost(cost){}

Card::Card(std::string name, std::string info, int cost, Key k, Timer timer, int h, int l, int e, std::string sum): name(name), info(info), cost(cost){
    setAbility(k, timer, h, l, e, sum);
}

std::string Card::getName(){
    return name;
}

void Card::setAbility(Key k, Timer timer, int h, int l, int e, std::string sum){
    Ability a{k, timer, h, l, e, sum};
    ability = a;
}

std::string Card::showInfo(){
    return info;
}

int Card::getCost(){
    return cost;
}

Ability Card::getAbility(){
    return ability;
}
