#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <vector>

#include "Direction.h"

class Snake{
    public:
        std::pair <int, int> head;
        std::vector <std::pair<int,int>> body; //.size() = length of body
        std::pair <int, int> posInit;
        Direction dir = Direction::INITIAL;
    private:

};

#endif