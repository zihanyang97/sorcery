//
//  hand.cpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-26.
//  Copyright © 2017 马源浩. All rights reserved.
//

#include "hand.hpp"


std::vector<Card*>& Hand::getHand(){
    return hand_card;
}

void Hand::draw(){
    if(!deck->isEmpty()){
        if(hand_card.size() < 5){
            std::string s = deck->getTop();
            deck->remove_card();
            Card *new_card = nullptr;
            if(s == "Air Elemental"){
                new_card = Air_Elemental;
                hand_card.emplace_back(new_card);
                return;
            }
            if(s == "Earth Elemental"){
                new_card = Earth_Elemental;
                hand_card.emplace_back(new_card);
                return;
            }
            if(s == "Fire Elemental"){
                new_card = Fire_Elemental;
                hand_card.emplace_back(new_card);
                return;
            }
            if(s == "Potion Seller"){
                new_card = Potion_Seller;
                hand_card.emplace_back(new_card);
                return;
            }
            if(s == "Novice Pyromancer"){
                new_card = Novice_Pyromancer;
                hand_card.emplace_back(new_card);
                return;
            }
            if(s == "Apprentice Summoner"){
                new_card = Apprentice_Summoner;
                hand_card.emplace_back(new_card);
                return;
            }
            if(s == "Master Summoner"){
                new_card = Master_Summoner;
                hand_card.emplace_back(new_card);
                return;
            }
            if(s == "Bone Golem"){
                new_card = Bone_Golem;
                hand_card.emplace_back(new_card);
                return;
            }
            if(s == "Banish"){
                new_card = Banish;
                hand_card.emplace_back(new_card);
                return;
            }
            if(s == "Unsummon"){
                new_card = Unsummon;
                hand_card.emplace_back(new_card);
                return;
            }
            if(s == "Recharge"){
                new_card = Recharge;
                hand_card.emplace_back(new_card);
                return;
            }
            if(s == "Disenchant"){
                new_card = Disenchant;
                hand_card.emplace_back(new_card);
                return;
            }
            if(s == "Raise Dead"){
                new_card = Raise_Dead;
                hand_card.emplace_back(new_card);
                return;
            }
            if(s == "Blizzard"){
                new_card = Blizzard;
                hand_card.emplace_back(new_card);
                return;
            }
            if(s == "Giant Strength"){
                new_card = Giant_Strength;
                hand_card.emplace_back(new_card);
                return;
            }
            if(s == "Silence"){
                new_card = Silence;
                hand_card.emplace_back(new_card);
                return;
            }
            if(s == "Dark Ritual"){
                new_card = Dark_Ritual;
                hand_card.emplace_back(new_card);
                return;
            }
            if(s == "Aura of Power"){
                new_card = Aura_of_Power;
                hand_card.emplace_back(new_card);
                return;
            }
            if(s == "Standstill"){
                new_card = Standstill;
                hand_card.emplace_back(new_card);
                return;
            }
            if(s == "Enrage"){
                new_card = Enrage;
                hand_card.emplace_back(new_card);
                return;
            }
        }else{
            std::string s = deck->getTop();
            deck->remove_card();
            std::cout << "Hand is full!" << std::endl;
            std::cout << s << " cannot be added to hand!" << std::endl;
            return;
        }
    }
}

bool Hand::isEmpty(){
    return hand_card.empty();
}

void Hand::init(std::string s){
    deck = new Deck();
    deck->init(s);
}

void Hand::removehand(int i){
    for(int j = i; j < hand_card.size() - 1; j++){
        hand_card[j] = hand_card[j+1];
    }
    hand_card.pop_back();
}

void Hand::Display(){
    card_template_t t[5];
    int i = 0;
    for(; i < hand_card.size(); ++i){
        t[i] = hand_card[i]->getDigit();
    }
    for(; i < 5; ++i){
        t[i] = CARD_TEMPLATE_EMPTY;
    }
    
    for(int j = 0; j < t[0].size(); ++j){
        for(int i = 0; i < 5; ++i){
            std::cout << t[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
}

void Hand::shuffle(int i){
    deck->shuffle(i);
}

Hand::~Hand(){
    delete deck;
    for(int i = 0; i < hand_card.size(); ++i){
        delete hand_card[i];
    }
}

