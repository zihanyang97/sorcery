//
//  deck.cpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-26.
//  Copyright © 2017 马源浩. All rights reserved.
//

#include "deck.hpp"
#include <fstream>

void Deck::add_card(std::string s){
    card_list.push_back(s);
}

void Deck::remove_card(){
    card_list.pop_back();
}

bool Deck::isEmpty(){
    if(card_list.empty()){
        return true;
    }else{
        return false;
    }
}

std::string Deck::getTop(){
    return card_list.back();
}

void Deck::shuffle(int i){
    srand((unsigned) i);
    int t = rand() % 30 + 11;
    while(t > 0){
        int i = rand() % num;
        int j = rand() % num;
        std::string temp = card_list[i];
        card_list[i] = card_list[j];
        card_list[j] = temp;
        t--;
    }
}


void Deck::init(std::string filename){
    std::ifstream file;
    file.open(filename);
    std::string s;
    while(!file.eof() && getline(file, s)){
        num++;
        add_card(s);
    }
    file.close();
}
