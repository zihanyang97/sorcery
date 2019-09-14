//
//  enchantment.hpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-22.
//  Copyright © 2017 马源浩. All rights reserved.
//

#ifndef enchantment_hpp
#define enchantment_hpp

#include <string>
#include "ascii_graphics.h"
#include "card.hpp"
#include "minion.hpp"

class Minion;
class Card;


class Enchantment: public Card{
    std::string type = "Enchantment";
    std::string op;
public:
    Enchantment(std::string name, std::string info, int cost, std::string op);
    void add(Minion &);
    std::string getType();
    void Display();
    card_template_t getDigit();
};

#endif /* enchantment_hpp */

