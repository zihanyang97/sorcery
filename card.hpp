//
//  card.hpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-22.
//  Copyright © 2017 马源浩. All rights reserved.
//

#ifndef card_hpp
#define card_hpp

#include <iostream>
#include "ability.hpp"
#include "ascii_graphics.h"

class Card{
protected:
    std::string name;
    std::string info;
    int cost;
    Ability ability;
    
    void setAbility(Key, Timer, int, int, int, std::string);
public:
    Card(std::string name, std::string info, int cost);
    Card(std::string, std::string, int, Key, Timer, int, int, int, std::string);
    std::string getName();
    std::string showInfo();
    int getCost();
    Ability getAbility();
    virtual std::string getType() = 0;
    virtual void Display() = 0;
    virtual card_template_t getDigit() = 0;
    virtual ~Card(){};
};

#endif /* card_hpp */
