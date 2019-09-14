//
//  hand.hpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-26.
//  Copyright © 2017 马源浩. All rights reserved.
//

#ifndef hand_hpp
#define hand_hpp

#include <vector>
#include "deck.hpp"
#include "card.hpp"
#include "cards.hpp"

class Hand{
    std::vector<Card*> hand_card;
    Deck *deck = nullptr;
public:
    void init(std::string);
    std::vector<Card*>&getHand();
    void draw();
    bool isEmpty();
    void removehand(int);
    void Display();
    void shuffle(int i);
    ~Hand();
};

#endif /* hand_hpp */
