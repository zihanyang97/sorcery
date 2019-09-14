//
//  graveyard.cpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-29.
//  Copyright © 2017 马源浩. All rights reserved.
//

#include "graveyard.hpp"


bool Graveyard::isEmpty(){
    return dead_list.empty();
}

void Graveyard::add(std::string s){
    dead_list.push_back(s);
}

std::string Graveyard::getTop(){
    return dead_list.back();
}

void Graveyard::remove(){
    dead_list.pop_back();
}
