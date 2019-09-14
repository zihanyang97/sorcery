//
//  board.hpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-29.
//  Copyright © 2017 马源浩. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

#include "window.h"
#include "player.hpp"
#include "graveyard.hpp"
#include "ascii_graphics.h"
#include "ritual.hpp"
#include "minion.hpp"
#include "cards.hpp"
#include "enchantment.hpp"
#include "ability.hpp"
#include <vector>
#include <sstream>

enum class Key;
class Minion;

class Board{
    Player *player_1 = nullptr;
    Player *player_2 = nullptr;
    std::vector<Minion*> minion_1;
    std::vector<Minion*> minion_2;
    Graveyard *graveyard_1 = nullptr;
    Graveyard *graveyard_2 = nullptr;
    Ritual *ritual_1 = nullptr;
    Ritual *ritual_2 = nullptr;
    Xwindow *hand = nullptr;

    Xwindow *main_board = nullptr;
    int turn = 1;
    bool testing = false;
    
    Minion* create_minion(std::string);
    void remove_minion(int, int);
    void update(Timer);
    void update(Timer, Minion*);
    void enter_update(Minion* min, int p);

public:
    void init(std::string, std::string, bool);
    bool end();
    void draw();
    void set_player_1_name(std::string);
    void set_player_2_name(std::string);
    void attack(int, int);
    void attack(int);
    void use(int);
    void use(int, int, int);
    int getTurn();
    void changeTurn();
    void play(int);
    void play(int, int, std::string);
    void set_testing();
    void remove_hand(int i);

    
    void start_update();
    void end_update();
    
    void Draw_Board();
    void Draw_Hand();
    void set_Board_Window(Xwindow *x, Xwindow *h);
    
    void Display();
    void Show_hand(int p);
    void inspect(int i, int p);

    ~Board();
};

#endif /* board_hpp */
