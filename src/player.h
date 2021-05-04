//
//  player.hpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-26.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "point.h"
#include "enum.h"
#include <string>

class Board;

class Player {
    Colour playerColour;
    std::string playerType;
    Board *theBoard;
    
public:
    Player(Colour colour, std::string playerType, Board *theBoard = nullptr);
    Colour getPlayerColour();
    std::string getPlayerType();
    Board * getBoard();
    void setBoard(Board *b);
    bool isCheck();
    bool isCheckmate();
    bool movePiece(Point ori, Point dest);
    bool moveComputer();
};

#endif /* player_hpp */
