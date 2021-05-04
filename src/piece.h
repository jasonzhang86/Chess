//
//  piece.hpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-23.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#ifndef piece_hpp
#define piece_hpp

#include <iostream>
#include "point.h"
#include "enum.h"

class Board;

class Piece {
    Colour colour;
    PieceType Type;
    Point coordinate;
    Board *b;
    bool captured = false;
    
public:
    Piece(Colour colour, PieceType Type, Point coordinate, Board *b);
    virtual ~Piece();
    Colour getColour();
    PieceType getType();
    Point getCoordinate();
    Board * getBoard();
    Direction whereIsDest(Point dest);
    void setCoordinate(Point dest);
    bool isCaptured();
    void capturePiece();
    
    virtual bool canMoveTo(Point dest) = 0;
    virtual bool movePiece(Point dest) = 0;
};

#endif /* piece_hpp */
