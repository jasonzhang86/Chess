//
//  Rook.hpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-23.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook: public Piece {
    bool moved = false;
    
public:
    Rook(Colour colour, PieceType Type, Point coordinate, Board *b);
    bool hasMoved();
    void setMoved();
    bool canMoveTo(Point dest) override;
    bool movePiece(Point dest) override;
};

#endif /* Rook_hpp */
