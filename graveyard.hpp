//
//  graveyard.hpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-29.
//  Copyright © 2017 马源浩. All rights reserved.
//

#ifndef graveyard_hpp
#define graveyard_hpp

#include "minion.hpp"
#include <vector>

class Graveyard{
    std::vector<std::string> dead_list;
public:
    bool isEmpty();
    void add(std::string);
    std::string getTop();
    void remove();
};

#endif /* graveyard_hpp */
