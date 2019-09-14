//
//  main.cpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-22.
//  Copyright © 2017 马源浩. All rights reserved.
//



#include <iostream>
#include <cstdlib>
#include <time.h>
#include "window.h"
#include "player.hpp"
#include "hand.hpp"
#include "deck.hpp"
#include "graveyard.hpp"
#include "board.hpp"
#include "minion.hpp"
#include "cards.hpp"
#include "enchantment.hpp"
#include "spell.hpp"
#include "ritual.hpp"
#include "card.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


int main(int argc, char *argv[]) {
    Board b;
    int turn;
    string cmd;
    bool is_testing = false;
    bool is_graphic = false;
    string filename_1 = "default.deck";
    string filename_2 = "default.deck";
    string init_file = "";
    Xwindow *x = nullptr;
    Xwindow *hand = nullptr;
    
    if(argc >= 2){
        for(int i = 1; i < argc; ++i){
            std::string s = argv[i];
            if(s == "-testing"){
                is_testing = true;
                b.set_testing();
            }
            if(s == "-deck1"){
                ++i;
                if(i < argc){
                    filename_1 = argv[i];
                }else{
                    filename_1 = "default.deck";
                }
            }
            if(s == "-deck2"){
                ++i;
                if(i < argc){
                    filename_2 = argv[i];
                }else{
                    filename_2 = "default.deck";
                }
            }
            if(s == "-init"){
                ++i;
                if(i < argc){
                    init_file = argv[i];
                }else{
                    cout << "required a filename for -init" << endl;
                    return 0;
                }
            }
            if(s == "-graphics"){
                is_graphic = true;
            }
            
        }
    }
    
    
    if(init_file != ""){

        b.init(filename_1, filename_2, !is_testing);
  
        
        if(is_graphic){
            x = new Xwindow(1000, 1000);
            hand = new Xwindow(1000, 200);
            b.set_Board_Window(x, hand);
        }
        
        ifstream file;
        file.open(init_file);
        string line;
        
        
        if(file >> line){
            b.set_player_1_name(line);
        }
        else{
            cout << "Enter a name for Player 1: ";
            cin >> line;
            b.set_player_1_name(line);
        }
        if(file >> line){
            b.set_player_2_name(line);
        }
        else{
            cout << "Enter a name for Player 2: ";
            cin >> line;
            b.set_player_2_name(line);
        }
        
        
        while(!b.end() && getline(file, line)){
            stringstream ss;
            ss << line;
            ss >> cmd;
            turn = b.getTurn();
            cout << "CMD: " << cmd << endl;
            if(cmd == "help"){
                cout << "Commands: help -- Display this message." << endl;
                cout << "          end  -- End the current player's turn." << endl;
                cout << "          quit -- End the game." << endl;
                cout << "attack minion other-minion -- Orders minion to attack other-minion." << endl;
                cout << "attack minion -- Orders minion to attack the opponent." << endl;
                cout << "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl;
                cout << "use minion [target-player target-card] -- Use minion’s special ability,";
                cout << "optionally targeting target-card owned by target-player." << endl;
                cout << "inspect minion -- View a minion’s card and all enchantments on that minion." << endl;
                cout << "hand -- Describe all cards in your hand." << endl;
                cout << "board -- Describe all cards on the board." << endl;
                continue;
            }
            if(cmd == "end"){
                b.end_update();
                b.changeTurn();
                b.start_update();
            }
            if(cmd == "quit"){
                return 0;
            }
            if(cmd == "attack"){
                int i;
                int j;
                
                if(!ss.eof()){
                    ss >> i;
                }
                else{
                    continue;
                }
                if(!ss.eof()){
                    ss >> j;
                    b.attack(i - 1, j - 1);
                    continue;
                }else{
                    if(i > 5){
                        cout << "incorrect index" << endl;
                        continue;
                    }
                    b.attack(i - 1);
                    continue;
                }
            }
            if(cmd == "draw" && is_testing){
                b.draw();
            }
            if(cmd == "discard" && is_testing){
                int i;
                if(!ss.eof()){
                    ss >> i;
                }else{
                    continue;
                }
                b.remove_hand(i - 1);
            }
            if(cmd == "play"){
                int i;
                int p;
                string t;
                
                if(!ss.eof()){
                    ss >> i;
                    cout << "I:" << i << endl;
                }
                
                if(!ss.eof()){
                    ss >> p;
                    ss >> t;
                    b.play(i - 1, p, t);
                }else{
                    b.play(i - 1);
                }
            }
            if(cmd == "use"){
                int i;
                int p;
                int t;
                if(!ss.eof()){
                    ss >> i;
                }
                
                if(!ss.eof()){
                    ss >> p;
                    ss >> t;
                    b.use(i - 1, p, t - 1);
                }else{
                    b.use(i - 1);
                }
            }
            if(cmd == "inspect"){
                int i;
                if(!ss.eof()){
                    ss >> i;
                }
                else{
                    continue;
                }
                
                if(turn % 2 == 1){
                    b.inspect(i - 1, 1);
                }
                else{
                    b.inspect(i - 1, 2);
                }
            }
            if(cmd == "hand"){
                if(turn % 2 == 1){
                    b.Show_hand(1);
                }
                else{
                    b.Show_hand(2);
                }
            }
            if(cmd == "board"){
                b.Display();
            }
            
            
        }
        file.close();
        
    }
    else{
 
        b.init(filename_1, filename_2, !is_testing);
        
        
        if(is_graphic){
            x = new Xwindow(1000, 1000);
            hand = new Xwindow(1000, 200);
            b.set_Board_Window(x, hand);
        }
        
        cout << "Enter a name for Player 1: ";
        cin >> cmd;
        b.set_player_1_name(cmd);
        
        cout << "Enter a name for Player 2: ";
        cin >> cmd;
        b.set_player_2_name(cmd);
        
    }
    
    
     while(!b.end()){
        turn = b.getTurn();
        if(is_graphic){
            b.Draw_Board();
            b.Draw_Hand();
        }
        if(turn % 2 == 0){
            cout << "Player 2 turns" << endl;
        }else{
            cout << "Player 1 turns" << endl;
        }
        cin >> cmd;
        if(cmd == "help"){
            cout << "Commands: help -- Display this message." << endl;
            cout << "          end  -- End the current player's turn." << endl;
            cout << "          quit -- End the game." << endl;
            cout << "attack minion other-minion -- Orders minion to attack other-minion." << endl;
            cout << "attack minion -- Orders minion to attack the opponent." << endl;
            cout << "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl;
            cout << "use minion [target-player target-card] -- Use minion’s special ability,";
            cout << "optionally targeting target-card owned by target-player." << endl;
            cout << "inspect minion -- View a minion’s card and all enchantments on that minion." << endl;
            cout << "hand -- Describe all cards in your hand." << endl;
            cout << "board -- Describe all cards on the board." << endl;
            continue;
        }
        if(cmd == "end"){
            b.end_update();
            b.changeTurn();
            b.start_update();
        }
        if(cmd == "quit"){
            return 0;
        }
        if(cmd == "attack"){
            string s;
            stringstream ss;
            getline(cin, s);
            ss << s;
            int i;
            int j;
            if(!ss.eof()){
                ss >> i;
            }else{
                cout << "Please enter as follow format!" << endl;
                cout << "1. attack i j" << endl;
                cout << "2. attack i" << endl;
                continue;
            }
            if(!ss.eof()){
                ss >> j;
                b.attack(i - 1, j - 1);
                continue;
            }else{
                if(i > 5){
                    cout << "incorrect index" << endl;
                    continue;
                }
                b.attack(i - 1);
                continue;
            }
        }
        if(cmd == "draw" && is_testing){
            b.draw();
        }
        if(cmd == "discard" && is_testing){
            int i;
            cin >> i;
            b.remove_hand(i - 1);
        }
        if(cmd == "play"){
            string s;
            stringstream ss;
            getline(cin, s);
            ss << s;
            int i;
            int p;
            string t;
            if(!ss.eof()){
                ss >> i;
            }else{
                cout << "Please enter as follow format!" << endl;
                cout << "1. play i" << endl;
                cout << "2. play i p t" << endl;
                continue;
            }
            if(!ss.eof()){
                ss >> p;
                ss >> t;
                b.play(i - 1, p, t);
            }else{
                b.play(i - 1);
            }
        }
        if(cmd == "use"){
            string s;
            stringstream ss;
            getline(cin, s);
            ss << s;
            int i;
            int p;
            int t;
            if(!ss.eof()){
                ss >> i;
            }else{
                cout << "Please enter as follow format!" << endl;
                cout << "1. play i" << endl;
                cout << "2. play i p t" << endl;
                continue;
            }
            if(!ss.eof()){
                ss >> p;
                ss >> t;
                b.use(i - 1, p, t - 1);
            }else{
                b.use(i - 1);
            }
        }
        if(cmd == "inspect"){
            int i;
            cin >> i;
            if(turn % 2 == 1){
                b.inspect(i - 1, 1);
            }
            else{
                b.inspect(i - 1, 2);
            }
        }
        if(cmd == "hand"){
            if(turn % 2 == 1){
                b.Show_hand(1);
            }
            else{
                b.Show_hand(2);
            }
        }
        if(cmd == "board"){
            b.Display();
        }
    }
    

}



