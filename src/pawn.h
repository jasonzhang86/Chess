//
//  pawn.hpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-23.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn: public Piece {
    bool moved = false;
    bool jumped = false; // True if the pawn moved two squares last move
    
public:
    Pawn(Colour colour, PieceType Type, Point coordinate, Board *b);
    bool hasMoved();
    void setMoved();
    bool hasJumped();
    void setJumped(bool b);
    bool canEnPassant();
    bool canMoveTo(Point dest) override;
    void pawnPromotion(Point dest);
    bool canEnPassant(Point dest);
    void EnPassant(Point dest);
    bool movePiece(Point dest) override;
};

#endif /* pawn_hpp */
