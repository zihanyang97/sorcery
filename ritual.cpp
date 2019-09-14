//
//  ritual.cpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-29.
//  Copyright © 2017 马源浩. All rights reserved.
//

#include "ritual.hpp"
#include <string>
#include <vector>


Ritual::Ritual(std::string name, std::string info, int cost, Key key, Timer timer, int hit, int life, int effect, std::string sum, int charge_cost, int charges): Card{name, info, cost, key, timer, hit, life, effect, sum}, charges_cost{charge_cost}, charges{charges} {

}

std::string Ritual::getType() {
    return type;
}

int Ritual::getCharge_cost() {
    return charges_cost;
}

int Ritual::getCharges() {
    return charges;
}

void Ritual::reduceCharges(int reduce) {
    charges -= reduce;
}

void Ritual::recharge(int charge) {
    charges += charge;
}

bool Ritual::is_live() {
    if (getCharges() > 0) {
        return true;
    }
    return false;
}

void Ritual::Display(){
    card_template_t t = display_ritual(name, cost, charges_cost, showInfo(), charges);
    for(int i = 0; i < t.size(); ++i){
        std::cout << t[i] << std::endl;
    }
}

card_template_t Ritual::getDigit(){
    card_template_t t = display_ritual(name, cost, charges_cost, showInfo(), charges);
    return t;
}
