//
//  ritual.hpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-29.
//  Copyright © 2017 马源浩. All rights reserved.
//

#ifndef ritual_hpp
#define ritual_hpp

#include "card.hpp"
#include "ability.hpp"
#include <string>
#include <vector>

class Ritual: public Card {
    std::string type = "Ritual";
    int charges_cost;
    int charges;
public:
    Ritual(std::string name, std::string info, int cost, Key key, Timer timer, int hit, int life, int effect, std::string sum, int charge_cost, int charges);
    std::string getType();
    int getCharge_cost();
    int getCharges();
    void reduceCharges(int reduce);
    void recharge(int charge);
    bool is_live();
    void Display();
    card_template_t getDigit();
};
#endif /* ritual_hpp */
