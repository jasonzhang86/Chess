//
//  computerMove.h
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-28.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#ifndef COMPUTERMOVE_H
#define COMPUTERMOVE_H

#include "point.h"
class Piece;

struct computerMove {
    Piece * whichPiece;
    Point dest;
    int priority;
};

#endif /* computerMove_h */
