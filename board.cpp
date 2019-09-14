//
//  board.cpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-29.
//  Copyright © 2017 马源浩. All rights reserved.
//
#include "board.hpp"
#include <cstdlib>

using namespace std;

void Board::init(std::string filename_1, std::string filename_2, bool s){
    player_1 = new Player();
    player_2 = new Player();
    graveyard_1 = new Graveyard();
    graveyard_2 = new Graveyard();
    
    player_1->init(filename_1);
    player_2->init(filename_2);
    if (s) {
        player_1->shuffle(rand());
        player_2->shuffle(rand());
    }
    for(int i = 0; i < 4; ++i){
        player_1->draw();
        player_2->draw();
    }
    player_1->draw();
}

void Board::set_player_1_name(std::string name){
    player_1->setName(name);
}
void Board::set_player_2_name(std::string name){
    player_2->setName(name);
}

void Board::draw(){
    if(turn % 2 == 1){
        player_1->draw();
    }
    else{
        player_2->draw();
    }
}

void Board::remove_hand(int i){
    if(turn % 2 == 1){
        delete player_1->getHand()[i];
        player_1->remove_hand(i);
    }
    else{
        delete player_2->getHand()[i];
        player_2->remove_hand(i);
    }
}

bool Board::end(){
    if(player_1 && player_2){
        if(player_1->is_live() && player_2->is_live()){
            return false;
        }else{
            return true;
        }
    }
    return false;
}

int Board::getTurn(){
    return turn;
}

void Board::changeTurn(){
    if(turn % 2 == 1){
        player_1->add_turn();
        player_1->refresh();
        for(int i = 0; i < minion_1.size(); ++i){
            minion_1[i]->refresh();
        }
    }
    else{
        player_2->add_turn();
        player_2->refresh();
        for(int i = 0; i < minion_2.size(); ++i){
            minion_2[i]->refresh();
        }
    }
    turn++;
}

void Board::attack(int i, int j){
    if(turn % 2 == 1){
        if(i >= minion_1.size() || i < 0 || j >= minion_2.size() || j < 0){
            cout << "Does not have that minion!" << endl;
            return;
        }
        if(minion_1[i]->getAction() < 1){
            cout << "This Minion cannot active now" << endl;
            return;
        }
        minion_1[i]->move();
        minion_2[j]->get_attacked(minion_1[i]->getAttack());
        minion_1[i]->get_attacked(minion_2[j]->getAttack());
        int death = 0;
        if(!minion_2[j]->is_live()){
            remove_minion(j, 2);
            ++death;
        }
        if(!minion_1[i]->is_live()){
            remove_minion(i, 1);
            ++death;
        }
        for(int k = 0; k < death; ++k){
            update(Timer::Death);
        }
        
    }
    else{
        if(j >= minion_1.size() || j < 0 || i >= minion_2.size() || i < 0){
            cout << "Does not have that minion!" << endl;
            return;
        }
        if(minion_2[i]->getAction() < 1){
            cout << "This Minion cannot active now" << endl;
            return;
        }
        minion_2[i]->move();
        minion_1[j]->get_attacked(minion_2[i]->getAttack());
        minion_2[i]->get_attacked(minion_1[j]->getAttack());
        int death = 0;
        if(!minion_1[j]->is_live()){
            remove_minion(j, 1);
            ++death;
        }
        if(!minion_2[i]->is_live()){
            remove_minion(i, 2);
            ++death;
        }
        for(int k = 0; k < death; ++k){
            update(Timer::Death);
        }
        
    }
}

void Board::attack(int i){
    if(turn % 2 == 1){
        if(i >= minion_1.size() || i < 0){
            cout << "Does not have that minion!" << endl;
            return;
        }
        if(minion_1[i]->getAction() < 1){
            cout << "This Minion cannot active now" << endl;
            return;
        }
        player_2->getAttacked(minion_1[i]->getAttack());
        minion_1[i]->move();
        return;
    }else{
        if(i >= minion_1.size() || i < 0){
            cout << "Does not have that minion!" << endl;
            return;
        }
        if(minion_2[i]->getAction() < 1){
            cout << "This Minion cannot active now" << endl;
            return;
        }
        player_1->getAttacked(minion_2[i]->getAttack());
        minion_2[i]->move();
        return;
    }
}

void Board::set_testing(){
    testing = true;
}

void Board::remove_minion(int i, int p){
    if(p == 1){
        graveyard_1->add(minion_1[i]->getName());
        delete minion_1[i];
        for(int k = i; k < minion_1.size() - 1; ++k){
            minion_1[k] = minion_1[k + 1];
        }
        minion_1.pop_back();
    }
    else {
        graveyard_2->add(minion_2[i]->getName());
        delete minion_2[i];
        for(int k = i; k < minion_2.size() - 1; ++k){
            minion_2[k] = minion_2[k + 1];
        }
        minion_2.pop_back();
    }
}


void Board::update(Timer t){
    for(int i = 0; i < minion_1.size(); ++i){
        Ability ability = minion_1[i]->getAbility();
        if(ability.timer == t){
            if(ability.key == Key::Addah){
                minion_1[i]->increase_state("+", ability.hit, ability.life);
                continue;
            }
            if(ability.key == Key::AllAddah){
                for(int j = 0; j < minion_1.size(); ++j){
                    minion_1[j]->increase_state("+", ability.hit, ability.life);
                }
                continue;
            }
        }
    }
    
    for(int i = 0; i < minion_2.size(); ++i){
        Ability ability = minion_2[i]->getAbility();
        if(ability.timer == t){
            if(ability.key == Key::Addah){
                minion_2[i]->increase_state("+", ability.hit, ability.life);
                continue;
            }
            if(ability.key == Key::AllAddah){
                for(int j = 0; j < minion_2.size(); ++j){
                    minion_2[j]->increase_state("+", ability.hit, ability.life);
                }
                continue;
            }
        }
    }
}



void Board::use(int i){
    if(turn % 2 == 1){
        if(minion_1[i]->showInfo() == ""){
            std::cout << "Minion does not have ability!" << std::endl;
            return;
        }
        if(minion_1[i]->get_state()){
            std::cout << "Minion has been slienced!" << std::endl;
            return;
        }
        if(player_1->getMagic() < minion_1[i]->get_Abilitycost()){
            if(!testing){
                std::cout << "Magic is not enough to active!" << std::endl;
                return;
            }
        }
        Ability ability = minion_1[i]->getAbility();
        if(ability.key == Key::Damage){
            std::cout << "two more argument needed!" << std::endl;
            std::cout << "command: use i p t" << std::endl;
            return;
        }
        if(ability.key == Key::Sum){
            for(int i = 0; i < ability.effect; ++i){
                if(minion_1.size() < 5){
                    if(ability.name == "Air Elemental"){
                        Minion *new_min = Air_Elemental;
                        minion_1.push_back(new_min);
                        enter_update(new_min, 1);
                    }
                }
            }
            if(!testing){
                player_1->useMagic(minion_1[i]->get_Abilitycost());
            }
            else{
                player_1->useMagic(player_1->getMagic());
            }
            
            minion_1[i]->move();
        }
        
    }
    else{
        if(minion_2[i]->showInfo() == ""){
            std::cout << "Minion does not have ability" << std::endl;
            return;
        }
        if(minion_2[i]->get_state()){
            std::cout << "Minion has been slineced" << std::endl;
            return;
        }
        if(player_2->getMagic() < minion_2[i]->get_Abilitycost()){
            if(!testing){
                std::cout << "Magic is not enough to active!" << std::endl;
                return;
            }
        }
        Ability ability = minion_2[i]->getAbility();
        if(ability.key == Key::Damage){
            std::cout << "two more argument needed!" << std::endl;
            std::cout << "command: use i p t" << std::endl;
            return;
        }
        if(ability.key == Key::Sum){
            for(int i = 0; i < ability.effect; ++i){
                if(minion_2.size() < 5){
                    if(ability.name == "Air Elemental"){
                        Minion *new_min = Air_Elemental;
                        minion_2.push_back(new_min);
                        enter_update(new_min, 2);                    }
                }
            }
            if(!testing){
                player_2->useMagic(minion_2[i]->get_Abilitycost());
            }
            else{
                player_2->useMagic(player_2->getMagic());
            }
            minion_2[i]->move();
        }
        
    }
    
}

void Board::use(int i, int p, int t){
    if(turn % 2 == 1){
        if(minion_1[i]->showInfo() == ""){
            std::cout << "Minion does not have ability" << std::endl;
            return;
        }
        if(minion_1[i]->get_state()){
            std::cout << "Minion has been slienced" << std::endl;
            return;
        }
        if(player_1->getMagic() < minion_1[i]->get_Abilitycost()){
            if(!testing){
                std::cout << "Magic is not enough to active!" << std::endl;
                return;
            }

        }
        
        Ability ability = minion_1[i]->getAbility();
        if(ability.key == Key::Damage){
            if(p == 1){
                minion_1[t]->get_attacked(ability.effect);
                if(!minion_1[t]->is_live()){
                    remove_minion(t, 1);
                    update(Timer::Death);
                }
                return;
            }
            if(p == 2){
                minion_2[t]->get_attacked(ability.effect);
                if(!minion_2[t]->is_live()){
                    remove_minion(t, 2);
                    update(Timer::Death);
                }
                return;
            }
            if(!testing){
                player_1->useMagic(minion_1[i]->get_Abilitycost());
            }else{
                player_1->useMagic(player_1->getMagic());
            }
            minion_1[i]->move();
        }
    }
    else{
        if(minion_2[i]->showInfo() == ""){
            std::cout << "Minion does not have ability" << std::endl;
            return;
        }
        if(minion_2[i]->get_state()){
            std::cout << "Minion has been slienced" << std::endl;
            return;
        }
        if(player_2->getMagic() < minion_2[i]->get_Abilitycost()){
            if(!testing){
                std::cout << "Magic is not enough to active!" << std::endl;
                return;
            }
        }
        Ability ability = minion_2[i]->getAbility();
        if(ability.key == Key::Damage){
            if(p == 1){
                minion_1[t]->get_attacked(ability.effect);
                if(!minion_1[t]->is_live()){
                    remove_minion(t, 1);
                    update(Timer::Death);
                }
                return;
            }
            if(p == 2){
                minion_2[t]->get_attacked(ability.effect);
                if(!minion_2[t]->is_live()){
                    remove_minion(t, 2);
                    update(Timer::Death);
                }
                return;
            }
            if(!testing){
                player_2->useMagic(minion_2[i]->get_Abilitycost());
            }
            else{
                player_2->useMagic(player_2->getMagic());
            }
            minion_2[i]->move();
        }
        
    }
}

void Board::inspect(int i, int p){
    if(p == 1){
        minion_1[i]->Display();
        minion_1[i]->show_enchant();
    }
    else{
        minion_2[i]->Display();
        minion_2[i]->show_enchant();
    }
}

void Board::Show_hand(int p){
    if(p == 1){
        player_1->show_hand();
    }
    else{
        player_2->show_hand();
    }
}

void Board::Display(){
    card_template_t r_1[5];
    card_template_t r_2[5];
    card_template_t m_1[5];
    card_template_t m_2[5];
    
    if(ritual_1 != nullptr){
        r_1[0] = ritual_1->getDigit();
    }
    else{
        r_1[0] = CARD_TEMPLATE_BORDER;
    }
    r_1[1] = CARD_TEMPLATE_EMPTY;
    r_1[2] = display_player_card(1,player_1->getName(), player_1->getHealth() , player_1->getMagic());  // change
    r_1[3] = CARD_TEMPLATE_EMPTY;
    
    if(graveyard_1 == nullptr || graveyard_1->isEmpty()){
        r_1[4] = CARD_TEMPLATE_BORDER;
    }
    else {
        Minion *m = create_minion(graveyard_1->getTop());
        r_1[4] = m->getDigit();
        delete m;
    }
    
    int i = 0;
    for(; i < minion_1.size(); ++i){
        m_1[i] = minion_1[i]->getDigit();
    }
    for(; i < 5; ++i){
        m_1[i] = CARD_TEMPLATE_BORDER;
    }
    
    i = 0;
    for(; i < minion_2.size(); ++i){
        m_2[i] = minion_2[i]->getDigit();
    }
    for(; i < 5; ++i){
        m_2[i] = CARD_TEMPLATE_BORDER;
    }
    
    if(ritual_2 != nullptr){
        r_2[0] = ritual_2->getDigit();
    }
    else{
        r_2[0] = CARD_TEMPLATE_BORDER;
    }
    
    r_2[1] = CARD_TEMPLATE_EMPTY;
    r_2[2] = display_player_card(2 , player_2->getName(), player_2->getHealth(), player_2->getMagic()); //change
    r_2[3] = CARD_TEMPLATE_EMPTY;
    
    if(graveyard_2 == nullptr || graveyard_2->isEmpty()){
        r_2[4] = CARD_TEMPLATE_BORDER;
    }
    else{
        Minion *m = create_minion(graveyard_2->getTop());
        r_2[4] = m->getDigit();
        delete m;
    }
    
    for(int j = 0; j < r_1[0].size(); ++j){
        for(int i = 0; i < 5; ++i){
            std::cout << r_1[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    for(int j = 0; j < m_1[0].size(); ++j){
        for(int i = 0; i < 5; ++i){
            std::cout << m_1[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    for(int j = 0; j < CENTRE_GRAPHIC.size(); ++j){
        std::cout << CENTRE_GRAPHIC[j] << std::endl;
    }
    
    for(int j = 0; j < m_2[0].size(); ++j){
        for(int i = 0; i < 5; ++i){
            std::cout << m_2[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    for(int j = 0; j < r_2[0].size(); ++j){
        for(int i = 0; i < 5; ++i){
            std::cout << r_2[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
}


Minion* Board::create_minion(std::string s){
    Minion *new_card = nullptr;
    if(s == "Air Elemental"){
        new_card = Air_Elemental;
    }
    if(s == "Earth Elemental"){
        new_card = Earth_Elemental;
    }
    if(s == "Fire Elemental"){
        new_card = Fire_Elemental;
    }
    if(s == "Potion Seller"){
        new_card = Potion_Seller;
    }
    if(s == "Novice Pyromancer"){
        new_card = Novice_Pyromancer;
    }
    if(s == "Apprentice Summoner"){
        new_card = Apprentice_Summoner;
    }
    if(s == "Master Summoner"){
        new_card = Master_Summoner;
    }
    if(s == "Bone Golem"){
        new_card = Bone_Golem;
    }
    return new_card;
}

void Board::play(int i){
    if(turn % 2 == 1){
        vector<Card *> hand = player_1->getHand();
        if(i >= hand.size()){
            cout << "Does not have that Card!" << endl;
            cout << "You only have" << hand.size() << " Cards!" << endl;
            return;
        }
        
        int magic = player_1->getMagic();
        int cost = hand[i]->getCost();
        Ability a = hand[i]->getAbility();
        
        //  check if enough magic
        if(cost > magic){
            if(!testing){
                cout << "No enough magic!" << endl;
                return;
            }
            else{
                cost = player_1->getMagic();
            }
        }
        
        if(hand[i]->getType() == "Spell"){   // the card player uses is spell
            if(a.key == Key::Recharges){
                if(ritual_1 == nullptr){
                    cout << "No ritual!" << endl;
                    return;
                }
   
                player_1->useMagic(cost);
                
                player_1->remove_hand(i);
                ritual_1->recharge(a.effect);
                return;
            }
            if(a.key == Key::Resurrect){
                if (graveyard_1->isEmpty()) {
                    cout << "No minion in graveyard!" << endl;
                    return;
                }
                if (minion_1.size() >= 5) {
                    cout << "Board is full!" << endl;
                    return;
                }
                // use card (cost magic)

                player_1->useMagic(cost);
                
                player_1->remove_hand(i);
                
                // get last minion in graveyard resurrect
                string name = graveyard_1->getTop();
                graveyard_1->remove();
                Minion *res = create_minion(name);
                res->setDefence(1);
                minion_1.emplace_back(res);
                enter_update(minion_1.back(), 1);
                return;
            }
            if (a.key == Key::Alldamage){   // the ability is do damage to all minions in board
                int death = 0;
                /// use card
                player_1->useMagic(cost);

                player_1->remove_hand(i);
                
                // do damage to opponent's minions
                for (int k = 0; k < minion_2.size(); ++k) {
                    minion_2[k]->get_attacked(a.effect);
                    // check is death
                    if (!minion_2[k]->is_live()) {
                        ++death;
                        remove_minion(k, 2);
                        --k;
                    }
                }
                
                // update death
                for (;death > 0; --death) {
                    update(Timer::Death);
                }
                
                // do damage to himself's minions
                for (int k = 0; k < minion_1.size(); ++k) {
                    minion_1[k]->get_attacked(a.effect);
                    // check is death
                    if (!minion_1[k]->is_live()) {
                        ++death;
                        remove_minion(k, 1);
                        --k;
                    }
                }
                
                // update death
                for (;death > 0; --death) {
                    update(Timer::Death);
                }
                return;
            }
        }
        if(hand[i]->getType() == "Ritual"){     // the card player uses is ritual
            
 
            player_1->useMagic(cost);

            if(ritual_1 != nullptr){
                delete ritual_1;
            }
            
            ritual_1 = dynamic_cast<Ritual*>(hand[i]);
            player_1->remove_hand(i);
            return;
        }
        if(hand[i]->getType() == "Minion") {  // the card player uses is minion
            
            // check if board is full
            if (minion_1.size() >= 5) {
                cout << "Board is full!" << endl;
                return;
            }
            
            // use card
            player_1->useMagic(cost);
            
            std::string name = hand[i]->getName();
            minion_1.push_back(create_minion(name));
            delete hand[i];
            enter_update(minion_1[minion_1.size() - 1], 1);
            player_1->remove_hand(i);
            
        }
        
    }
    else{
        vector<Card *> hand = player_2->getHand();
        if(i >= hand.size()){
            cout << "Does not have that Card!" << endl;
            cout << "You only have" << hand.size() << " Cards!" << endl;
            return;
        }
        
        int magic = player_2->getMagic();
        int cost = hand[i]->getCost();
        Ability a = hand[i]->getAbility();
        
        //  check if enough magic
        if(cost > magic){
            if(!testing){
                cout << "No enough magic!" << endl;
                return;
            }
            else{
                cost = player_2->getMagic();
            }
        }
        
        if(hand[i]->getType() == "Spell"){   // the card player uses is spell
            if(a.key == Key::Recharges){
                if(ritual_2 == nullptr){
                    cout << "No ritual!" << endl;
                    return;
                }
 
                player_2->useMagic(cost);
                
                player_2->remove_hand(i);
                ritual_2->recharge(a.effect);
                return;
            }
            if(a.key == Key::Resurrect){
                if (graveyard_2->isEmpty()) {
                    cout << "No minion in graveyard!" << endl;
                    return;
                }
                if (minion_2.size() >= 5) {
                    cout << "Board is full!" << endl;
                    return;
                }
                // use card (cost magic)
                player_2->useMagic(cost);
                
                player_2->remove_hand(i);
                
                // get last minion in graveyard resurrect
                string name = graveyard_2->getTop();
                graveyard_2->remove();
                Minion *res = create_minion(name);
                res->setDefence(1);
                minion_2.emplace_back(res);
                enter_update(minion_2.back(), 2);
                return;
            }
            if (a.key == Key::Alldamage){   // the ability is do damage to all minions in board
                int death = 0;
                /// use card

                player_2->useMagic(cost);
                
                player_2->remove_hand(i);
                
                // do damage to opponent's minions
                for (int k = 0; k < minion_1.size(); ++k) {
                    minion_1[k]->get_attacked(a.effect);
                    // check is death
                    if (!minion_1[k]->is_live()) {
                        ++death;
                        remove_minion(k, 1);
                        --k;
                    }
                }
                
                // update death
                for (;death > 0; --death) {
                    update(Timer::Death);
                }
                
                // do damage to himself's minions
                for (int k = 0; k < minion_2.size(); ++k) {
                    minion_2[k]->get_attacked(a.effect);
                    // check is death
                    if (!minion_2[k]->is_live()) {
                        ++death;
                        remove_minion(k, 2);
                        --k;
                    }
                }
                
                // update death
                for (;death > 0; --death) {
                    update(Timer::Death);
                }
                return;
            }
        }
        if(hand[i]->getType() == "Ritual"){     // the card player uses is ritual
            

            player_2->useMagic(cost);
            
            if(ritual_2 != nullptr){
                delete ritual_1;
            }
            
            ritual_2 = dynamic_cast<Ritual*>(hand[i]);
            player_2->remove_hand(i);
            return;
        }
        if(hand[i]->getType() == "Minion") {  // the card player uses is minion
            
            // check if board is full
            if (minion_2.size() >= 5) {
                cout << "Board is full!" << endl;
                return;
            }
            
            // use card
   
            player_2->useMagic(cost);
            
            std::string name = hand[i]->getName();
            minion_2.push_back(create_minion(name));
            delete hand[i];
            enter_update(minion_2[minion_2.size() - 1], 2);
            player_2->remove_hand(i);
            
        }
    }
}


void Board::enter_update(Minion* min, int p) {
    // Enter minion is player_1's
    if (p == 1){
        
        // my ritual
        if(ritual_1 != nullptr){
            Ability a = ritual_1->getAbility();
            
            if(a.timer == Timer::Enter){
                
                if (a.key == Key::Addah) {
                    
                    // check ritual charge
                    int char_cost = ritual_1->getCharge_cost();
                    ritual_1->reduceCharges(char_cost);
                    if (!ritual_1->is_live()) {
                        delete ritual_1;
                        ritual_1 = nullptr;
                    }
                    
                    min->increase_state("+", a.hit, a.life);
                }
            } else if(a.timer == Timer::Enter){
                // ability is kill
                if(a.key == Key::Kill){
                    
                    int char_cost = ritual_1->getCharge_cost();
                    ritual_1->reduceCharges(char_cost);
                    if(!ritual_1->is_live()){
                        delete ritual_1;
                        ritual_2 = nullptr;
                    }
                    
                    remove_minion(minion_1.size() - 1, 1);
                    update(Timer::Death);
                }
            }
        }
        // check AP minions (currently do not have that kind of minions need to check
        
        // check NAP minions
        for (int i = 0; i < minion_2.size(); ++i) {
            Ability a = minion_2[i]->getAbility();
            
            // ability is used when a minion enters
            if (a.timer == Timer::Enter && minion_2[i]->has_triggle()) {
                // ability is do damage to the minion enters
                if (a.key == Key::Damage) {
                    min->get_attacked(a.effect);
                    // check is live
                    if (!min->is_live()) {
                        remove_minion(minion_1.size() - 1, 1);
                        update(Timer::Death);
                    }
                }
            }
        }
        
        // enemy's ritual
        if(ritual_2 != nullptr){
            Ability a = ritual_2->getAbility();
            
            if(a.timer == Timer::Enter){
                // ability is kill
                if(a.key == Key::Kill){
                    
                    int char_cost = ritual_2->getCharge_cost();
                    ritual_2->reduceCharges(char_cost);
                    if(!ritual_2->is_live()){
                        delete ritual_2;
                        ritual_2 = nullptr;
                    }
                    
                    remove_minion(minion_1.size() - 1, 1);
                    update(Timer::Death);
                }
            }
        }
        
    }
    else{
        // my ritual
        if(ritual_2 != nullptr){
            Ability a = ritual_2->getAbility();
            
            if(a.timer == Timer::Enter){
                
                if (a.key == Key::Addah) {
                    
                    // check ritual charge
                    int char_cost = ritual_2->getCharge_cost();
                    ritual_2->reduceCharges(char_cost);
                    if (!ritual_2->is_live()) {
                        delete ritual_2;
                        ritual_2 = nullptr;
                    }
                    
                    min->increase_state("+", a.hit, a.life);
                }
            } else if(a.timer == Timer::Enter){
                // ability is kill
                if(a.key == Key::Kill){
                    
                    int char_cost = ritual_2->getCharge_cost();
                    ritual_2->reduceCharges(char_cost);
                    if(!ritual_2->is_live()){
                        delete ritual_2;
                        ritual_2 = nullptr;
                    }
                    
                    remove_minion(minion_2.size() - 1, 2);
                    update(Timer::Death);
                }
            }
        }
        // check AP minions (currently do not have that kind of minions need to check
        
        // check NAP minions
        for (int i = 0; i < minion_1.size(); ++i) {
            Ability a = minion_1[i]->getAbility();
            
            // ability is used when a minion enters
            if (a.timer == Timer::Enter && minion_1[i]->has_triggle()) {
                // ability is do damage to the minion enters
                if (a.key == Key::Damage) {
                    min->get_attacked(a.effect);
                    // check is live
                    if (!min->is_live()) {
                        remove_minion(minion_2.size() - 1, 2);
                        update(Timer::Death);
                    }
                }
            }
        }
        
        // enemy's ritual
        if(ritual_1 != nullptr){
            Ability a = ritual_1->getAbility();
            
            if(a.timer == Timer::Enter){
                // ability is kill
                if(a.key == Key::Kill){
                    
                    int char_cost = ritual_1->getCharge_cost();
                    ritual_1->reduceCharges(char_cost);
                    if(!ritual_1->is_live()){
                        delete ritual_1;
                        ritual_1 = nullptr;
                    }
                    
                    remove_minion(minion_2.size() - 1, 2);
                    update(Timer::Death);
                }
            }
        }
        
        
    }
    
}


void Board::play(int i, int p, string s){
    if(turn % 2 == 1){
        vector<Card*>& hand = player_1->getHand();
        int magic = player_1->getMagic();
        int cost = hand[i]->getCost();
        
        if(cost > magic){
            if(!testing){
                cout << "No enough magic!" << endl;
                return;
            }else{
                cost = player_1->getMagic();
            }
        }
        
        
        if(i >= hand.size()){
            cout << "Does not have that card!" << endl;
            return;
        }
        
        int t;
        
        if(s != "r"){
            stringstream ss;
            ss << s;
            ss >> t;
            --t;
        }
        
        Ability a = hand[i]->getAbility();
        
        if(hand[i]->getType() == "Spell"){  // the card player uses is spell
            
            if(a.key == Key::Kill){ // the ability is kill a minion or ritual
                
                // check if there is target
                if (p == 1) {
                    // target is ritual
                    if (s == "r") {
                        if (ritual_1 == nullptr) {
                            cout << "No ritual to destroy" << endl;
                            return;
                        }
                        else{
                            delete ritual_1;
                            ritual_1 = nullptr;
                            player_1->useMagic(cost);
                            delete hand[i];
                            player_1->remove_hand(i);
                            return;
                        }
                    }
                    // target is minion
                    if (t >= minion_1.size()) {
                        cout << "No minion to destroy" << endl;
                        return;
                    }
                    else{
                        player_1->useMagic(cost);
                        remove_minion(t, p);
                        delete hand[i];
                        player_1->remove_hand(i);
                        update(Timer::Death);
                    }
                }
                
                if(p == 2){
                    // target is ritual
                    if (s == "r") {
                        if (ritual_2 == nullptr) {
                            cout << "No ritual to destroy" << endl;
                            return;
                        }
                        else{
                            delete ritual_2;
                            ritual_2 = nullptr;
                            player_1->useMagic(cost);
                            delete hand[i];
                            player_1->remove_hand(i);
                            return;
                        }
                    }
                    // target is minion
                    if (minion_2.size() <= t) {
                        cout << "No minion to destroy" << endl;
                        return;
                    }
                    else{
                        player_1->useMagic(cost);
                        remove_minion(t, p);
                        delete hand[i];
                        player_1->remove_hand(i);
                        update(Timer::Death);
                        
                    }
                    
                }
            } // end for kill
            
            if(a.key == Key::Return){
                // check if wrong target
                if (s == "r") {
                    cout << "Wrong target!" << endl;
                    return;
                }
                
                // check if there is target
                if (p == 1) {
                    if (minion_1.size() <= t) {
                        cout << "No minion to return" << endl;
                        return;
                    }
                    else {
                        if(player_1->getHand().size() < 5){
                            player_1->useMagic(cost);
                            delete hand[i];
                            player_1->remove_hand(i);
                            hand.push_back(create_minion(minion_1[t]->getName()));
                            remove_minion(t, p);
                            graveyard_1->remove();
                            return;
                        }
                        else{
                            cout << "Hand card is Full!" << endl;
                            return;
                        }
                    }
                }
                
                if (p == 2) {
                    if (minion_2.size() <= t) {
                        cout << "No minion to return" << endl;
                        return;
                    }
                    else {
                        // hand isn't full
                        if (player_2->getHand().size() < 5) {
                            player_1->useMagic(cost);
                            delete hand[i];
                            player_1->remove_hand(i);
                            player_2->getHand().push_back(create_minion(minion_2[t]->getName()));
                            remove_minion(t, p);
                            graveyard_2->remove();
                            return;
                        }
                        else {
                            cout << "Hand card is Full!" << endl;
                            return;
                            
                        }
                        
                    }
                }
                
            } // end for return
            
            if (a.key == Key::Remove){
                // check if wrong target
                if (s == "r") {
                    cout << "Wrong target!" << endl;
                    return;
                }
                
                // check if there is target
                if (p == 1) {
                    if (minion_1.size() < t) {
                        cout << "No minion on target position" << endl;
                        return;
                    }
                    if (minion_1[t]->enchant_empty()) {
                        cout << "No enchantment on target minion" << endl;
                        return;
                    }
                    
                    // use card
                    player_1->useMagic(cost);
                    delete hand[i];
                    player_1->remove_hand(i);
                    
                    // remove player 1's minion's enchantment
                    minion_1[t]->remove_attach();
                    return;
                }
                
                if (p == 2){
                    if (minion_2.size() <= t) {
                        cout << "No minion on target position" << endl;
                    }
                    if (minion_2[t]->enchant_empty()) {
                        cout << "No enchantment on target minion" << endl;
                        return;
                    }
                    
                    // use card
                    player_1->useMagic(cost);
                    delete hand[i];
                    player_1->remove_hand(i);
                    
                    // remove player 1's minion's enchantment
                    minion_2[t]->remove_attach();
                    return;
                }
            } // end of remove
        } // end of spell
        
        if(hand[i]->getType() == "Enchantment"){
            if (p == 1) {
                
                // check if target minion exist
                if (minion_1.size() < t) {
                    cout << "Target minion does not exist!" << endl;
                    return;
                }
                
                // use card
                player_1->useMagic(cost);
                minion_1[t]->add_enchant(hand[i]->getName());
                delete hand[i];
                player_1->remove_hand(i);
                return;
            }
            
            if(p == 2) {
                // check if target minion exist
                if (minion_2.size() < t) {
                    cout << "Target minion does not exist!" << endl;
                    return;
                }
                
                // use card
                player_1->useMagic(cost);
                minion_2[t]->add_enchant(hand[i]->getName());
                delete hand[i];
                player_1->remove_hand(i);
                return;
            }
            
        } // end of Enchantment
    }
    // end of turn 1
    
    // turn 2
    else{
        vector<Card*>& hand = player_2->getHand();
        int magic = player_1->getMagic();
        int cost = hand[i]->getCost();
        
        if(cost > magic){
            if(!testing){
                cout << "No enough magic!" << endl;
                return;
            }
            else{
                cost = player_2->getMagic();
            }
        }
        
        
        if(i >= hand.size()){
            cout << "Does not have that card!" << endl;
            return;
        }
        
        int t;
        
        if(s != "r"){
            stringstream ss;
            ss << s;
            ss >> t;
            --t;
        }
        
        Ability a = hand[i]->getAbility();
        
        if(hand[i]->getType() == "Spell"){  // the card player uses is spell
            
            if(a.key == Key::Kill){ // the ability is kill a minion or ritual
                
                // check if there is target
                if (p == 1) {
                    // target is ritual
                    if (s == "r") {
                        if (ritual_1 == nullptr) {
                            cout << "No ritual to destroy" << endl;
                            return;
                        }
                        else{
                            delete ritual_1;
                            ritual_1 = nullptr;
                            player_2->useMagic(cost);
                            delete hand[i];
                            player_2->remove_hand(i);
                            return;
                        }
                    }
                    // target is minion
                    if (minion_1.size() <= t) {
                        cout << "No minion to destroy" << endl;
                        return;
                    }
                    else{
                        player_2->useMagic(cost);
                        delete hand[i];
                        player_2->remove_hand(i);
                        remove_minion(t, p);
                        update(Timer::Death);
                    }
                }
                
                if(p == 2){
                    // target is ritual
                    if (s == "r") {
                        if (ritual_2 == nullptr) {
                            cout << "No ritual to destroy" << endl;
                            return;
                        }
                        else{
                            delete ritual_2;
                            ritual_2 = nullptr;
                            player_2->useMagic(cost);
                            delete hand[i];
                            player_2->remove_hand(i);
                            return;
                        }
                    }
                    // target is minion
                    if (minion_2.size() <= t) {
                        cout << "No minion to destroy" << endl;
                        return;
                    }
                    else{
                        player_2->useMagic(cost);
                        delete hand[i];
                        player_2->remove_hand(i);
                        remove_minion(t, p);
                        update(Timer::Death);
                        
                    }
                    
                }
            } // end for kill
            
            if(a.key == Key::Return){
                // check if wrong target
                if (s == "r") {
                    cout << "Wrong target!" << endl;
                    return;
                }
                
                // check if there is target
                if (p == 1) {
                    if (minion_1.size() <= t) {
                        cout << "No minion to return" << endl;
                        return;
                    }
                    else {
                        if(player_1->getHand().size() < 5){
                            player_2->useMagic(cost);
                            delete hand[i];
                            player_2->remove_hand(i);
                            player_1->getHand().push_back(create_minion(minion_1[t]->getName()));
                            remove_minion(t, p);
                            graveyard_1->remove();
                            return;
                        }
                        else{
                            cout << "Hand card is Full!" << endl;
                            return;
                        }
                    }
                }
                
                if (p == 2) {
                    if (minion_2.size() <= t) {
                        cout << "No minion to return" << endl;
                        return;
                    }
                    else {
                        
                        // hand isn't full
                        if (player_2->getHand().size() < 5) {
                            player_2->useMagic(cost);
                            delete hand[i];
                            player_2->remove_hand(i);
                            player_2->getHand().push_back(create_minion(minion_1[t]->getName()));
                            remove_minion(t, p);
                            graveyard_2->remove();
                            return;
                        }
                        else {
                            cout << "Hand card is Full!" << endl;
                            return;
                            
                        }
                        
                    }
                }
                
            } // end for return
            
            if (a.key == Key::Remove){
                // check if wrong target
                if (s == "r") {
                    cout << "Wrong target!" << endl;
                    return;
                }
                
                // check if there is target
                if (p == 1) {
                    if (minion_1.size() < t) {
                        cout << "No minion on target position" << endl;
                        return;
                    }
                    if (minion_1[t]->enchant_empty()) {
                        cout << "No enchantment on target minion" << endl;
                        return;
                    }
                    
                    // use card
                    player_2->useMagic(cost);
                    delete hand[i];
                    player_2->remove_hand(i);
                    
                    // remove player 1's minion's enchantment
                    minion_1[t]->remove_attach();
                    return;
                }
                
                if (p == 2){
                    if (minion_2.size() <= t) {
                        cout << "No minion on target position" << endl;
                    }
                    if (minion_2[t]->enchant_empty()) {
                        cout << "No enchantment on target minion" << endl;
                        return;
                    }
                    
                    // use card
                    player_2->useMagic(cost);
                    delete hand[i];
                    player_2->remove_hand(i);
                    
                    // remove player 1's minion's enchantment
                    minion_2[t]->remove_attach();
                    return;
                }
            } // end of remove
        } // end of spell
        
        if(hand[i]->getType() == "Enchantment"){
            if (p == 1) {
                
                // check if target minion exist
                if (minion_1.size() < t) {
                    cout << "Target minion does not exist!" << endl;
                    return;
                }
                
                // use card
                player_2->useMagic(cost);
                minion_1[t]->add_enchant(hand[i]->getName());
                delete hand[i];
                player_2->remove_hand(i);
                return;
            }
            
            if(p == 2) {
                // check if target minion exist
                if (minion_2.size() < t) {
                    cout << "Target minion does not exist!" << endl;
                    return;
                }
                
                // use card
                player_2->useMagic(cost);
                minion_2[t]->add_enchant(hand[i]->getName());
                delete hand[i];
                player_2->remove_hand(i);
                return;
            }
            
        } // end of Enchantment
    }
}





void Board::start_update() {
    // only ritual has ability is used when a round start
    
    // player 1
    if (turn % 2 == 1) {
        player_1->draw();
        
        // add here if add himself's minion with ability used when a round start
        
        if (ritual_1 != nullptr) {
            
            Ability ra = ritual_1->getAbility();
            
            // ability is used when a round start
            if (ra.timer == Timer::Start) {
                
                // ability is magic
                if (ra.key == Key::Magic) {
                    
                    // check ritual charge
                    int char_cost = ritual_1->getCharge_cost();
                    ritual_1->reduceCharges(char_cost);
                    if (!ritual_1->is_live()) {
                        delete ritual_1;
                        ritual_1 = nullptr;
                    }
                    
                    player_1->gainMagic(ra.effect);
                }
            }
        }
        // add here if add opponent's minion and ritual with ability used when a round start
    }
    
    // player 2
    else {
        player_2->draw();
        // add here if add himself's minion with ability used when a round start
        
        if (ritual_2 != nullptr) {
            
            Ability ra = ritual_2->getAbility();
            
            // ability is used when a round start
            if (ra.timer == Timer::Start) {
                
                // ability is magic
                if (ra.key == Key::Magic) {
                    
                    // check ritual charge
                    int char_cost = ritual_2->getCharge_cost();
                    ritual_2->reduceCharges(char_cost);
                    if (!ritual_2->is_live()) {
                        delete ritual_2;
                        ritual_2 = nullptr;
                    }
                    
                    player_2->gainMagic(ra.effect);
                }
            }
        }
        // add here if add opponent's minion and ritual with ability used when a round start
    }
}




void Board::end_update() {
    // only minion has ability when a round end
    
    // player 1
    if (turn % 2 == 1) {
        
        for (int i = 0; i < minion_1.size(); ++i) {
            
            Ability ma = minion_1[i]->getAbility();
            
            // ability is used when a round end
            if (ma.timer == Timer::End) {
                
                // ability is add attack and defence
                if (ma.key == Key::AllAddah) {
                    
                    // add attack and defence for all minions
                    for (int j = 0; j < minion_1.size(); ++j) {
                        minion_1[j]->increase_state("+", ma.hit, ma.life);
                    }
                }
            }
        }
        // add here if add himself's ritual or opponent's minions and ritual with ability used when a round stard
    }
    
    else {
        for (int i = 0; i < minion_2.size(); ++i) {
            
            Ability ma = minion_2[i]->getAbility();
            
            // ability is used when a round end
            if (ma.timer == Timer::End) {
                
                // ability is add attack and defence
                if (ma.key == Key::AllAddah) {
                    
                    // add attack and defence for all minions
                    for (int j = 0; j < minion_2.size(); ++j) {
                        minion_2[j]->increase_state("+", ma.hit, ma.life);
                    }
                }
            }
        }
        // add here if add himself's ritual or opponent's minions and ritual with ability used when a round stard
    }
}



void Board::Draw_Board(){
    //row
    main_board->fillRectangle(0, 0, 1000, 1000,Xwindow::White);
    main_board->fillRectangle(0, 0, 200, 4);
    main_board->fillRectangle(400, 0, 200, 4);
    main_board->fillRectangle(800, 0, 200, 4);
    main_board->fillRectangle(0, 196, 1000, 8);
    main_board->fillRectangle(0, 396, 1000, 8);
    main_board->fillRectangle(0, 596, 1000, 8);
    main_board->fillRectangle(0, 796, 1000, 8);
    main_board->fillRectangle(0, 996, 200, 4);
    main_board->fillRectangle(400, 996, 200, 4);
    main_board->fillRectangle(800, 996, 200, 4);
    
    main_board->drawBigString(350, 540, "SORCERY", Xwindow::Red);
    //col
    main_board->fillRectangle(0, 0, 8, 1000);
    main_board->fillRectangle(200, 0, 8, 400);
    main_board->fillRectangle(200, 600, 8, 400);
    main_board->fillRectangle(400, 0, 8, 400);
    main_board->fillRectangle(400, 600, 8, 400);
    main_board->fillRectangle(600, 0, 8, 400);
    main_board->fillRectangle(600, 600, 8, 400);
    main_board->fillRectangle(800, 0, 8, 400);
    main_board->fillRectangle(800, 600, 8, 400);
    main_board->fillRectangle(992, 0, 8, 1000);
    
    // draw player
    main_board->drawString(450, 100, player_1->getName(), Xwindow::Black);
    main_board->drawString(420, 180, to_string(player_1->getHealth()), Xwindow::Black);
    main_board->drawString(580, 180, to_string(player_1->getMagic()), Xwindow::Black);
    main_board->drawString(450, 850, player_2->getName(), Xwindow::Blue);
    main_board->drawString(420, 980, to_string(player_2->getHealth()), Xwindow::Blue);
    main_board->drawString(580, 980, to_string(player_2->getMagic()), Xwindow::Blue);
    
    if(ritual_1){
        main_board->drawString(185, 20, to_string(ritual_1->getCost()), Xwindow::Black);
        main_board->drawString(20, 20, ritual_1->getName(), Xwindow::Black);
        main_board->fillRectangle(170, 0, 2, 40);
        main_board->fillRectangle(0, 40, 200, 2);
        main_board->drawString(140, 60, ritual_1->getType(), Xwindow::Black);
        main_board->fillRectangle(0, 80, 200, 2);
        main_board->drawString(20, 100, to_string(ritual_1->getCharge_cost()), Xwindow::Black);
        if(ritual_1->showInfo().length() > 24){
            main_board->drawString(45, 100, ritual_1->showInfo().substr(0, 24), Xwindow::Black);
            if (ritual_1->showInfo().length() > 48) {
                main_board->drawString(15 , 930, ritual_1->showInfo().substr(24, 24), Xwindow::Blue);
                main_board->drawString(15 , 960, ritual_1->showInfo().substr(48), Xwindow::Blue);
            } else {
                main_board->drawString(15 , 930, ritual_1->showInfo().substr(24), Xwindow::Blue);
            }
        }
        else{
            main_board->drawString(45 , 100, ritual_1->showInfo().substr(0));
        }
        main_board->drawString(180, 185, to_string(ritual_1->getCharges()), Xwindow::Black);
        
    }
    if(ritual_2) {
        main_board->drawString(185, 820, to_string(ritual_2->getCost()), Xwindow::Blue);
        main_board->drawString(20, 820, ritual_1->getName(), Xwindow::Blue);
        main_board->fillRectangle(170, 800, 2, 40);
        main_board->fillRectangle(0, 840, 200, 2);
        main_board->drawString(140, 860, ritual_1->getType(), Xwindow::Blue);
        main_board->fillRectangle(0, 880, 200, 2);
        main_board->drawString(20, 900, to_string(ritual_2->getCharge_cost()), Xwindow::Blue);
        if(ritual_2->showInfo().length() > 24){
            main_board->drawString(45 , 900, ritual_2->showInfo().substr(0, 24), Xwindow::Blue);
            if (ritual_2->showInfo().length() > 48) {
                main_board->drawString(15 , 930, ritual_2->showInfo().substr(24, 24), Xwindow::Blue);
                main_board->drawString(15 , 960, ritual_2->showInfo().substr(48), Xwindow::Blue);
            } else {
                main_board->drawString(15 , 930, ritual_2->showInfo().substr(24), Xwindow::Blue);
            }
        }
        else{
            main_board->drawString(45, 900, ritual_2->showInfo().substr(0));
        }
        main_board->drawString(180, 985, to_string(ritual_2->getCharges()), Xwindow::Blue);
    }
    if(graveyard_1 && !graveyard_1->isEmpty()){
        Minion *m = create_minion(graveyard_1->getTop());
        main_board->drawString(985, 20, to_string(m->getCost()));
        main_board->drawString(820, 20, m->getName());
        main_board->fillRectangle(970, 0, 2, 40);
        main_board->fillRectangle(800, 40, 200, 2);
        main_board->drawString(940, 60, m->getType());
        main_board->fillRectangle(800, 80, 200, 2);
        if(m->showInfo() != "" && !m->has_triggle()){
            main_board->drawString(820, 100, to_string(m->get_Abilitycost()));
            if(m->showInfo().length() > 24){
                main_board->drawString(845, 100, m->showInfo().substr(0, 24));
                if (m->showInfo().length() > 48) {
                    main_board->drawString(815, 130, m->showInfo().substr(24, 24));
                    main_board->drawString(815, 160, m->showInfo().substr(48));
                } else {
                    main_board->drawString(815, 130, m->showInfo().substr(24));
                }
            }
            else{
                main_board->drawString(845, 100, m->showInfo().substr(0));
            }
        } else if (m->showInfo() != "" && m->has_triggle()) {
            if(m->showInfo().length() > 24){
                main_board->drawString(815, 100, m->showInfo().substr(0, 24));
                if (m->showInfo().length() > 48) {
                    main_board->drawString(815, 130, m->showInfo().substr(24, 24));
                    main_board->drawString(815, 160, m->showInfo().substr(48));
                } else {
                    main_board->drawString(815, 130, m->showInfo().substr(24));
                }
            }
            else{
                main_board->drawString(815, 100, m->showInfo().substr(0));
            }
        }
        main_board->drawString(820, 185, to_string(m->getAttack()));
        main_board->drawString(980, 185, to_string(m->getHealth()));
        delete m;
        
    }
    if(graveyard_2 && !graveyard_2->isEmpty()){
        Minion *m = create_minion(graveyard_2->getTop());
        main_board->drawString(985, 820, to_string(m->getCost()));
        main_board->drawString(820, 820, m->getName());
        main_board->fillRectangle(970, 800, 2, 40);
        main_board->fillRectangle(800, 840, 200, 2);
        main_board->drawString(940, 860, m->getType());
        main_board->fillRectangle(800, 880, 200, 2);
        if(m->showInfo() != "" && !m->has_triggle()){
            main_board->drawString(820, 900, to_string(m->get_Abilitycost()));
            if(m->showInfo().length() > 24){
                main_board->drawString(845, 900, m->showInfo().substr(0, 24));
                if (m->showInfo().length() > 48) {
                    main_board->drawString(815, 930, m->showInfo().substr(24, 24));
                    main_board->drawString(815, 960, m->showInfo().substr(48));
                } else {
                    main_board->drawString(815, 930, m->showInfo().substr(24));
                }
            }
            else{
                main_board->drawString(845, 900, m->showInfo().substr(0));
            }
        } else if (m->showInfo() != "" && m->has_triggle()) {
            if(m->showInfo().length() > 24){
                main_board->drawString(815, 900, m->showInfo().substr(0, 24));
                if (m->showInfo().length() > 48) {
                    main_board->drawString(815, 930, m->showInfo().substr(24, 24));
                    main_board->drawString(815, 960, m->showInfo().substr(48));
                } else {
                    main_board->drawString(815, 930, m->showInfo().substr(24));
                }
            }
            else{
                main_board->drawString(815, 900, m->showInfo().substr(0));
            }
        }
        main_board->drawString(820, 985, to_string(m->getAttack()));
        main_board->drawString(980, 985, to_string(m->getHealth()));
        delete m;
    }
    
    for(int i = 0; i < minion_1.size(); ++i){
        Minion *m = minion_1[i];
        main_board->drawString(180 + i * 200, 220, to_string(m->getCost()));
        main_board->drawString(15 + i * 200, 220, m->getName());
        main_board->fillRectangle(170 + i * 200, 200, 2, 40);
        main_board->fillRectangle(0 + i * 200, 240, 200, 2);
        main_board->drawString(140 + i * 200, 260, m->getType());
        main_board->fillRectangle(0 + i * 200, 280, 200, 2);
        if(m->showInfo() != "" && !m->has_triggle()){
            main_board->drawString(20 + i * 200, 300, to_string(m->get_Abilitycost()));
            if(m->showInfo().length() > 24){
                main_board->drawString(45 + i * 200, 300, m->showInfo().substr(0, 24));
                if (m->showInfo().length() > 48) {
                    main_board->drawString(15 + i * 200, 330, m->showInfo().substr(24, 24));
                    main_board->drawString(15 + i * 200, 360, m->showInfo().substr(48));
                } else {
                    main_board->drawString(15 + i * 200, 330, m->showInfo().substr(24));
                }
            }
            else{
                main_board->drawString(45 + i * 200, 300, m->showInfo().substr(0));
            }
        } else if  (m->showInfo() != "" && m->has_triggle()) {
            if(m->showInfo().length() > 24){
                main_board->drawString(15 + i * 200, 300, m->showInfo().substr(0, 24));
                if (m->showInfo().length() > 48) {
                    main_board->drawString(15 + i * 200, 330, m->showInfo().substr(24, 24));
                    main_board->drawString(15 + i * 200, 360, m->showInfo().substr(48));
                } else {
                    main_board->drawString(15 + i * 200, 330, m->showInfo().substr(24));
                }
            }
            else{
                main_board->drawString(15 + i * 200, 300, m->showInfo().substr(0));
            }
        }
        main_board->drawString(20 + i * 200, 385, to_string(m->getAttack()));
        main_board->drawString(180 + i * 200, 385, to_string(m->getHealth()));
        
    }
    
    for(int i = 0; i < minion_2.size(); ++i){
        Minion *m = minion_2[i];
        main_board->drawString(180 + i * 200, 620, to_string(m->getCost()));
        main_board->drawString(15 + i * 200, 620, m->getName());
        main_board->fillRectangle(170 + i * 200, 600, 2, 40);
        main_board->fillRectangle(0 + i * 200, 640, 200, 2);
        main_board->drawString(140 + i * 200, 660, m->getType());
        main_board->fillRectangle(0 + i * 200, 680, 200, 2);
        if(m->showInfo() != "" && !m->has_triggle()){
            main_board->drawString(20 + i * 200, 700, to_string(m->get_Abilitycost()));
            if(m->showInfo().length() > 24){
                main_board->drawString(45 + i * 200, 700, m->showInfo().substr(0, 24));
                if (m->showInfo().length() > 48) {
                    main_board->drawString(15 + i * 200, 730, m->showInfo().substr(24, 24));
                    main_board->drawString(15 + i * 200, 760, m->showInfo().substr(48));
                } else {
                    main_board->drawString(15 + i * 200, 730, m->showInfo().substr(24));
                }
            }
            else{
                main_board->drawString(45 + i * 200, 700, m->showInfo().substr(0));
            }
        } else if (m->showInfo() != "" && m->has_triggle()) {
            if(m->showInfo().length() > 24){
                main_board->drawString(15 + i * 200, 700, m->showInfo().substr(0, 24));
                if (m->showInfo().length() > 48) {
                    main_board->drawString(15 + i * 200, 730, m->showInfo().substr(24, 24));
                    main_board->drawString(15 + i * 200, 760, m->showInfo().substr(48));
                } else {
                    main_board->drawString(15 + i * 200, 730, m->showInfo().substr(24));
                }
            }
            else{
                main_board->drawString(15 + i * 200, 700, m->showInfo().substr(0));
            }
        }
        main_board->drawString(20 + i * 200, 785, to_string(m->getAttack()));
        main_board->drawString(180 + i * 200, 785, to_string(m->getHealth()));
        
    }

}

void Board::Draw_Hand(){
    if(turn % 2 == 1){
        hand->fillRectangle(0, 0, 1000, 200,Xwindow::White);
        vector<Card*> &h_1 = player_1->getHand();
        for(int i = 0; i < h_1.size(); ++i){
            Card *m = h_1[i];
            hand->fillRectangle(i * 200, 0, 2, 200, Xwindow::Black);
            hand->fillRectangle(200 + i * 200, 0, 2, 200, Xwindow::Black);
            hand->fillRectangle(0 + i * 200, 0, 200, 2, Xwindow::Black);
            hand->fillRectangle(0 + i * 200, 200, 200, 2, Xwindow::Black);
            if(m->getType() == "Spell"){
                hand->drawString(185 + i * 200, 20, to_string(m->getCost()), Xwindow::Black);
                hand->drawString(20 + i * 200, 20, m->getName(), Xwindow::Black);
                hand->fillRectangle(170 + i * 200, 0, 2, 40);
                hand->fillRectangle(0 + i * 200, 40, 200, 2);
                hand->drawString(140 + i * 200, 60, m->getType(), Xwindow::Black);
                hand->fillRectangle(0 + i * 200, 80, 200, 2);
                if (m->showInfo().length() > 24){
                    hand->drawString(15 + i * 200, 100, m->showInfo().substr(0, 24), Xwindow::Black);
                    if (m->showInfo().length() > 48) {
                        hand->drawString(15 + i * 200, 130, m->showInfo().substr(24,48), Xwindow::Black);
                        hand->drawString(15 + i * 200, 160, m->showInfo().substr(48), Xwindow::Black);
                    } else {
                        hand->drawString(15 + i * 200, 130, m->showInfo().substr(24), Xwindow::Black);
                    }
                }
                else{
                    hand->drawString(15 + i * 200, 100, m->showInfo().substr(0));
                }

            }
            if(m->getType() == "Minion"){
                Minion* ma = dynamic_cast<Minion*>(m);
                hand->drawString(180 + i * 200, 20, to_string(ma->getCost()));
                hand->drawString(15 + i * 200, 20, ma->getName());
                hand->fillRectangle(170 + i * 200, 0, 2, 40);
                hand->fillRectangle(0 + i * 200, 40, 200, 2);
                hand->drawString(140 + i * 200, 60, ma->getType());
                hand->fillRectangle(0 + i * 200, 80, 200, 2);
                if(ma->showInfo() != "" && !ma->has_triggle()){
                    hand->drawString(20 + i * 200, 100, to_string(ma->get_Abilitycost()));
                    if(m->showInfo().length() > 24){
                        hand->drawString(45 + i * 200, 100, ma->showInfo().substr(0, 24));
                        if (ma->showInfo().length() > 48) {
                            hand->drawString(15 , 130, ma->showInfo().substr(24, 24));
                            hand->drawString(15 , 160, ma->showInfo().substr(48));
                        } else {
                            hand->drawString(15 , 130, ma->showInfo().substr(24));
                        }
                    }
                    else{
                        hand->drawString(45 + i * 200, 100, ma->showInfo().substr(0));
                    }
                } else if (ma->showInfo() != "" && ma->has_triggle()) {
                    if(m->showInfo().length() > 24){
                        hand->drawString(15 + i * 200, 100, ma->showInfo().substr(0, 24));
                        if (ma->showInfo().length() > 48) {
                            hand->drawString(15 , 130, ma->showInfo().substr(24, 24));
                            hand->drawString(15 , 160, ma->showInfo().substr(48));
                        } else {
                            hand->drawString(15 , 130, ma->showInfo().substr(24));
                        }
                    }
                    else{
                        hand->drawString(15 + i * 200, 100, ma->showInfo().substr(0));
                    }
                }
                hand->drawString(20 + i * 200, 185, to_string(ma->getAttack()));
                hand->drawString(180 + i * 200, 185, to_string(ma->getHealth()));
            }
            if(m->getType() == "Ritual"){
                Ritual* ma = dynamic_cast<Ritual*>(m);
                hand->drawString(185 + i * 200, 20, to_string(ma->getCost()));
                hand->drawString(20 + i * 200, 20, ma->getName());
                hand->fillRectangle(170 + i * 200, 0, 2, 40);
                hand->fillRectangle(0 + i * 200, 40, 200, 2);
                hand->drawString(140 + i * 200, 60, ma->getType());
                hand->fillRectangle(0 + i * 200, 80, 200, 2);
                hand->drawString(20 + i * 200, 100, to_string(ma->getCharge_cost()));
                if(ma->showInfo().length() > 24){
                    hand->drawString(45 + i * 200 , 100, ma->showInfo().substr(0, 24));
                    if (ma->showInfo().length() > 48) {
                        hand->drawString(15 + i * 200, 130, ma->showInfo().substr(24, 24));
                        hand->drawString(15 + i * 200, 160, ma->showInfo().substr(48));
                    } else {
                        hand->drawString(15 + i * 200, 130, ma->showInfo().substr(24));
                    }
                }
                else{
                    hand->drawString(45 + i * 200, 100, ma->showInfo().substr(0));
                }
                hand->drawString(180 + i * 200, 185, to_string(ma->getCharges()));
            }
            if(m->getType() == "Enchantment"){
                hand->drawString(180 + i * 200, 20, to_string(m->getCost()));
                hand->drawString(15 + i * 200, 20, m->getName());
                hand->fillRectangle(170 + i * 200, 0, 2, 40);
                hand->fillRectangle(0 + i * 200, 40, 200, 2);
                hand->drawString(140 + i * 200, 60, m->getType());
                hand->fillRectangle(0 + i * 200, 80, 200, 2);
                if(m->showInfo().length() > 24){
                    hand->drawString(15 + i * 200, 100, m->showInfo().substr(0, 24));
                    if (m->showInfo().length() > 48) {
                        hand->drawString(15 + i * 200, 130, m->showInfo().substr(24, 24));
                        hand->drawString(15 + i * 200, 160, m->showInfo().substr(48));
                    } else {
                        hand->drawString(15 + i * 200, 130, m->showInfo().substr(24));
                    }
                }
                else{
                    hand->drawString(15 + i * 200, 100, m->showInfo().substr(0));
                }
                if(m->getName() != "Silence"){
                    if(m->getName() == "Enrage"){
                        hand->drawString(20 + i * 200, 185, "*2");
                        hand->drawString(180 + i * 200, 185, "*2");
                    }
                    else{
                        hand->drawString(20 + i * 200, 185, "+2");
                        hand->drawString(180 + i * 200, 185, "+2");
                    }
                }
            
            }
        }
    }
    
    else{
  
        hand->fillRectangle(0, 0, 1000, 200,Xwindow::White);
        vector<Card*> &h_2 = player_2->getHand();
        for(int i = 0; i < h_2.size(); ++i){
            Card *m = h_2[i];
            hand->fillRectangle(i * 200, 0, 2, 200, Xwindow::Black);
            hand->fillRectangle(200 + i * 200, 0, 2, 200, Xwindow::Black);
            hand->fillRectangle(0 + i * 200, 0, 200, 2, Xwindow::Black);
            hand->fillRectangle(0 + i * 200, 200, 200, 2, Xwindow::Black);
            if(m->getType() == "Spell"){
                hand->drawString(185 + i * 200, 20, to_string(m->getCost()), Xwindow::Black);
                hand->drawString(20 + i * 200, 20, m->getName(), Xwindow::Black);
                hand->fillRectangle(170 + i * 200, 0, 2, 40);
                hand->fillRectangle(0 + i * 200, 40, 200, 2);
                hand->drawString(140 + i * 200, 60, m->getType(), Xwindow::Black);
                hand->fillRectangle(0 + i * 200, 80, 200, 2);
                if(m->showInfo().length() > 24){
                    hand->drawString(15 + i * 200, 100, m->showInfo().substr(0, 24), Xwindow::Black);
                    if (m->showInfo().length() > 48) {
                        hand->drawString(15 + i * 200, 130, m->showInfo().substr(24, 24), Xwindow::Black);
                        hand->drawString(15 + i * 200, 160, m->showInfo().substr(48), Xwindow::Black);
                    } else {
                        hand->drawString(15 + i * 200, 130, m->showInfo().substr(24), Xwindow::Black);
                    }
                }
                else{
                    hand->drawString(15 + i * 200, 100, m->showInfo().substr(0));
                }
            
            }
            if(m->getType() == "Minion"){
                Minion* ma = dynamic_cast<Minion*>(m);
                hand->drawString(180 + i * 200, 20, to_string(ma->getCost()));
                hand->drawString(15 + i * 200, 20, ma->getName());
                hand->fillRectangle(170 + i * 200, 0, 2, 40);
                hand->fillRectangle(0 + i * 200, 40, 200, 2);
                hand->drawString(140 + i * 200, 60, ma->getType());
                hand->fillRectangle(0 + i * 200, 80, 200, 2);
                if(ma->showInfo() != "" && !ma->has_triggle()){
                    hand->drawString(20 + i * 200, 100, to_string(ma->get_Abilitycost()));
                    if(ma->showInfo().length() > 24){
                        hand->drawString(15 + i * 200, 100, ma->showInfo().substr(0, 24));
                        if (ma->showInfo().length() > 48) {
                            hand->drawString(15 + i * 200, 130, ma->showInfo().substr(24, 24));
                            hand->drawString(15 + i * 200, 160, ma->showInfo().substr(48));
                        } else {
                            hand->drawString(15 + i * 200, 130, ma->showInfo().substr(24));
                        }
                    }
                    else{
                        hand->drawString(45 + i * 200, 100, ma->showInfo().substr(0));
                    }
                } else if (ma->showInfo() != "" && ma->has_triggle()) {
                    if(ma->showInfo().length() > 24){
                        hand->drawString(15 + i * 200, 100, ma->showInfo().substr(0, 24));
                        if (ma->showInfo().length() > 48) {
                            hand->drawString(15 + i * 200, 130, ma->showInfo().substr(24, 24));
                            hand->drawString(15 + i * 200, 160, ma->showInfo().substr(48));
                        } else {
                            hand->drawString(15 + i * 200, 130, ma->showInfo().substr(24));
                        }
                    }
                    else{
                        hand->drawString(15 + i * 200, 100, ma->showInfo().substr(0));
                    }
                }
                hand->drawString(20 + i * 200, 185, to_string(ma->getAttack()));
                hand->drawString(180 + i * 200, 185, to_string(ma->getHealth()));
            }
            if(m->getType() == "Ritual"){
                Ritual* ma = dynamic_cast<Ritual*>(m);
                hand->drawString(185 + i * 200, 20, to_string(ma->getCost()));
                hand->drawString(20 + i * 200, 20, ma->getName());
                hand->fillRectangle(170 + i * 200, 0, 2, 40);
                hand->fillRectangle(0 + i * 200, 40, 200, 2);
                hand->drawString(140 + i * 200, 60, ma->getType());
                hand->fillRectangle(0 + i * 200, 80, 200, 2);
                hand->drawString(20 + i * 200, 100, to_string(ma->getCharge_cost()));
                if(ma->showInfo().length() > 24){
                    hand->drawString(45 + i * 200 , 100, ma->showInfo().substr(0, 24));
                    if (ma->showInfo().length() > 48) {
                        hand->drawString(15 + i * 200, 130, ma->showInfo().substr(24, 24));
                        hand->drawString(15 + i * 200, 160, ma->showInfo().substr(48));
                    } else {
                        hand->drawString(15 + i * 200, 130, ma->showInfo().substr(24));
                    }
                }
                else{
                    hand->drawString(45 + i * 200, 100, ma->showInfo().substr(0));
                }
                hand->drawString(180 + i * 200, 185, to_string(ma->getCharges()));
            }
            if(m->getType() == "Enchantment"){
                hand->drawString(180 + i * 200, 20, to_string(m->getCost()));
                hand->drawString(15 + i * 200, 20, m->getName());
                hand->fillRectangle(170 + i * 200, 0, 2, 40);
                hand->fillRectangle(0 + i * 200, 40, 200, 2);
                hand->drawString(140 + i * 200, 60, m->getType());
                hand->fillRectangle(0 + i * 200, 80, 200, 2);
                if(m->showInfo().length() > 24){
                    hand->drawString(15 + i * 200, 100, m->showInfo().substr(0, 24));
                    if (m->showInfo().length() > 48) {
                        hand->drawString(15 + i * 200, 130, m->showInfo().substr(24, 24));
                        hand->drawString(15 + i * 200, 160, m->showInfo().substr(48));
                    } else {
                        hand->drawString(15 + i * 200, 130, m->showInfo().substr(24));
                    }
                }
                else{
                    hand->drawString(15 + i * 200, 100, m->showInfo().substr(0));
                }
                if(m->getName() != "Silence"){
                    if(m->getName() == "Enrage"){
                        hand->drawString(20 + i * 200, 185, "*2");
                        hand->drawString(180 + i * 200, 185, "*2");
                    }
                    else{
                        hand->drawString(20 + i * 200, 185, "+2");
                        hand->drawString(180 + i * 200, 185, "+2");
                    }
                }
            
            }
        }
    }

}

void Board::set_Board_Window(Xwindow *x, Xwindow *h){
    main_board = x;
    hand = h;
}



Board::~Board(){
    delete player_1;
    delete player_2;
    delete ritual_1;
    delete ritual_2;
    delete graveyard_1;
    delete graveyard_2;
    for(int i = 0; i < minion_1.size(); ++i){
        delete minion_1[i];
    }
    for(int i = 0; i < minion_2.size(); ++i){
        delete minion_2[i];
    }
    
    delete main_board;
    delete hand;
}

