//
//  deck.hpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-26.
//  Copyright © 2017 马源浩. All rights reserved.
//

#ifndef deck_hpp
#define deck_hpp

#include <vector>
#include <cstdlib>
#include <time.h>
#include "card.hpp"

class Deck{
    std::vector<std::string > card_list;
    int num = 0;
public:
    void init(std::string);
    void add_card(std::string);
    void remove_card();
    void shuffle(int i);
    std::string getTop();
    bool isEmpty();
};
#endif /* deck_hpp */
