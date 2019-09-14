//
//  player.cpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-26.
//  Copyright © 2017 马源浩. All rights reserved.
//

#include "player.hpp"

void Player::setName(std::string s){
    name = s;
}

void Player::getAttacked(int n){
    health -= n;
}

void Player::useMagic(int n){
    magic -= n;
}

void Player::refresh(){
    if(turn + 3 <= 10){
        magic = turn + 3;
    }else{
        magic = 10;
    }
}

std::vector<Card*>& Player::getHand(){
    return hand->getHand();
}

Hand* Player::get_hand(){
    return hand;
}

void Player::draw(){
    hand->draw();
}

bool Player::is_live(){
    if(health <= 0){
        return  false;
    }else{
        return true;
    }
}

void Player::shuffle(int i){
    hand->shuffle(i);
}

std::string Player::getName(){
    return name;
}

int Player::getHealth(){
    return health;
}

void Player::add_turn(){
    turn++;
}

int Player::getMagic(){
    return magic;
}

void Player::gainMagic(int n){
    magic += n;
}

void Player::init(std::string filename){
    hand = new Hand();
    hand->init(filename);
}

void Player::remove_hand(int i){
    hand->removehand(i);
}

void Player::show_hand(){
    hand->Display();
}

Player::~Player(){
    delete hand;
}


