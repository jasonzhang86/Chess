//
//  Knight.hpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-23.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight: public Piece {
    
public:
    Knight(Colour colour, PieceType Type, Point coordinate, Board *b);
    bool canMoveTo(Point dest) override;
    bool movePiece(Point dest) override;
};

#endif /* Knight_hpp */
