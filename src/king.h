//
//  King.hpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-23.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#ifndef KING_H
#define KING_H

#include "piece.h"

class King: public Piece {
    bool moved = false;
    
public:
    King(Colour colour, PieceType Type, Point coordinate, Board *b);
    bool hasMoved();
    void setMoved();
    bool canMoveTo(Point dest) override;
    bool canCastleTo(Point dest);
    void CastleTo(Point dest);
    bool movePiece(Point dest) override;
};

#endif /* King_hpp */
