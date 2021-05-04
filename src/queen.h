//
//  queen.hpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-23.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen: public Piece {
    
public:
    Queen(Colour colour, PieceType Type, Point coordinate, Board *b);
    bool canMoveTo(Point dest) override;
    bool movePiece(Point dest) override;
};

#endif /* queen_hpp */
