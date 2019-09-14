//
//  minion.cpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-22.
//  Copyright © 2017 马源浩. All rights reserved.
//

#include "minion.hpp"
#include "enchantment.hpp"




Minion::Minion(bool triggle, std::string name, std::string info, int cost, int attack, int health, int ability_cost, Key key, Timer timer, int hit , int life, int effect, std::string sum): Card{name, info, cost, key, timer, hit, life, effect, sum}, triggle(triggle), attack{attack}, health{health}, ability_cost(ability_cost){
    max_health = health;
    o_attack = attack;
    o_health = health;
}

std::string Minion::getName(){
    return name;
}

std::string Minion::getType(){
    return type;
}

int Minion::getAttack(){
    return attack;
}

int Minion::getAction(){
    return action;
}

int Minion::getHealth(){
    return health;
}

Ability Minion::getAbility(){
    return ability;
}

int Minion::get_Abilitycost(){
    return ability_cost;
}

bool Minion::get_state(){
    return is_slience;
}



void Minion::Heal(int n){
    if(n + health < max_health){
        health += n;
    }else{
        health = max_health ;
    }
}

bool Minion::enchant_empty(){
    return enchant.empty();
}


bool Minion::is_live(){
    if(health <= 0){
        return false;
    }else{
        return true;
    }
}

bool Minion::has_triggle(){
    return triggle;
}



void Minion::get_attacked(int n){
    health -= n;
}

void Minion::setDefence(int n){
    health = n;
    max_health = n;
}

void Minion::increase_state(std::string s, int a, int h){
    if(s == "+"){
        attack += a;
        health += h;
    }
    if(s == "*"){
        attack *= a;
        health *= h;
    }
    if(s == "/"){
        attack /= a;
        health /= h;
    }
    if(s == "-"){
        attack -= a;
        health -= h;
    }
}

void Minion::move(){
    --action;
}

void Minion::refresh(){
    action = 1;
}

void Minion::change_slience(){
    if(is_slience){
        is_slience = false;
    }
    else{
        is_slience = true;
    }
}



void Minion::add_enchant(std::string s){
    enchant.push_back(s);
    if(s == "Silence"){
        if(!is_slience){
            change_slience();
        }
    }
    if(s == "Enrage"){
        increase_state("*", 2, 2);
    }
    if(s == "Giant Strength"){
        increase_state("+", 2, 2);
    }
}

void Minion::remove_attach(){
    std::string s = enchant.back();
    enchant.pop_back();
    if(s == "Silence"){
        if(is_slience){
            change_slience();
        }
        return;
    }
    if(s == "Enrage"){
        increase_state("/", 2, 2);
        return;
    }
    if(s == "Giant Strength"){
        increase_state("-", 2, 2);
        return;
    }
}

void Minion::show_enchant(){
    if(enchant.empty()){
        return;
    }
    Enchantment *s = Silence;
    Enchantment *e = Enrage;
    Enchantment *g = Giant_Strength;
    
    int size = (int)enchant.size();
    int row = (size / 5);
    int reminder = size % 5;
    card_template_t t[5];

    for(int i = 0; i < row; ++i){
        for(int j = 0; j < 5; ++j){
            std::string name = enchant[i*5 + j];
            if(name == "Silence"){
                t[j] = s->getDigit();
                continue;
            }
            if(name == "Enrage"){
                t[j] = e->getDigit();
                continue;
            }
            if(name == "Giant Strength"){
                t[j] = g->getDigit();
                continue;
            }
        }
        
        for(int m = 0; m < t[0].size(); ++m){
            for(int n = 0; n < 5; ++n){
                std::cout << t[n][m] << " ";
            }
            std::cout << std::endl;
        }
    }
    
    for(int i = 0; i < reminder; ++i){
        std::string name = enchant[row * 5 + i];
        if(name == "Silence"){
            t[i] = s->getDigit();
            continue;
        }
        if(name == "Enrage"){
            t[i] = e->getDigit();
            continue;
        }
        if(name == "Giant Strength"){
            t[i] = g->getDigit();
            continue;
        }
    }
    
    for(int m = 0; m < t[0].size(); ++m){
        for(int n = 0; n < reminder; ++n){
            std::cout << t[n][m] << " ";
        }
        std::cout << std::endl;
    }
    
    delete s;
    delete g;
    delete e;
    
}

void Minion::Display(){
    card_template_t t;
    if(showInfo() == ""){
        t = display_minion_no_ability(name, cost, attack, health);
    }
    else{
        if(triggle){
            t = display_minion_triggered_ability(name, cost, attack, health, showInfo());
        }
        else{
            t = display_minion_activated_ability(name, cost, attack, health, ability_cost, showInfo());
        }
    }
    for(int i = 0; i < t.size(); ++i){
        std::cout << t[i] << std::endl;
    }
}

card_template_t Minion::getDigit(){
    card_template_t t;
    if(showInfo() == ""){
        t = display_minion_no_ability(name, cost, attack, health);
    }
    else{
        if(triggle){
            t = display_minion_triggered_ability(name, cost, attack, health, showInfo());
        }
        else{
            t = display_minion_activated_ability(name, cost, attack, health, ability_cost, showInfo());
        }
    }
    return t;
}
