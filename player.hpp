//
//  player.hpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-26.
//  Copyright © 2017 马源浩. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <iostream>
#include <vector>
#include "minion.hpp"
#include "hand.hpp"

class Player{
    std::string name;
    int health = 20;
    int magic = 3;
    int turn = 0;
    Hand *hand;
public:
    std::string getName();
    int getHealth();
    int getMagic();
    std::vector<Card*>& getHand();
    Hand* get_hand();
    
    void gainMagic(int);
    void getAttacked(int);
    void init(std::string);
    void add_turn();
    void setName(std::string);
    void useMagic(int);
    void refresh();
    void draw();
    bool is_live();
    void remove_hand(int);
    void shuffle(int i);
    
    void show_hand();
    ~Player();
};

#endif /* player_hpp */
