//
//  spell.hpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-29.
//  Copyright © 2017 马源浩. All rights reserved.
//

#ifndef spell_hpp
#define spell_hpp

#include "card.hpp"
#include "ability.hpp"
#include "ascii_graphics.h"
#include <string>
#include <vector>

class Spell: public Card {
    std::string type = "Spell";

public:
    Spell(std::string name, std::string info, int cost, Key key, Timer timer, int hit, int life, int effect, std::string sum);
    std::string getType();
    
    void Display();
    card_template_t getDigit();
};

#endif /* spell_hpp */
