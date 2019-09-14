//
//  minion.hpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-22.
//  Copyright © 2017 马源浩. All rights reserved.
//

#ifndef minion_hpp
#define minion_hpp

#include <vector>
#include "card.hpp"
#include "cards.hpp"

#include "ability.hpp"
#include "ascii_graphics.h"

class Minion: public Card{
    std::string type = "Minion";
    bool is_slience = false;
    bool triggle;
    int attack;
    int health;
    int max_health;
    int ability_cost;
    int o_attack;
    int o_health;
    int action = 0;

    std::vector<std::string> enchant;

public:
    Minion(bool, std::string, std::string, int, int, int, int, Key, Timer, int, int, int, std::string);
    
    std::string getName();
    std::string getType();
    int getAttack();
    int getHealth();
    int getAction();
    int get_Abilitycost();
    bool get_state();
    Ability getAbility();
    
    bool is_live();
    bool has_triggle();
    bool enchant_empty();
    
    void Heal(int n);
    void get_attacked(int n);
    void setDefence(int);
    void change_slience();
    void increase_state(std::string s, int a, int h);
    void add_enchant(std::string s);
    void remove_attach();
    void move();
    void refresh();
    
    void show_enchant();
    void Display();
    card_template_t getDigit();
};

#endif /* minion_hpp */
