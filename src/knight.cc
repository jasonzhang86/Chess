//
//  Knight.cpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-23.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#include "knight.h"
#include "board.h"

using namespace std;

Knight::Knight(Colour colour, PieceType Type, Point coordinate, Board *b):
Piece(colour, Type, coordinate, b) {}

bool Knight::canMoveTo(Point dest) {
    //Information of the piece being moved
    Point myCoord = getCoordinate();
    Colour myColour = getColour();
    // Can't move to the current position
    if (dest.row == myCoord.row && dest.col == myCoord.col) {
        return false;
    }
    //Information of the piece at target location
    Piece * target = getBoard()->pieceAt(dest);
    if (target) {
        Colour destColour = target->getColour();
        if (destColour == myColour) {
            // cerr << "Can't capture your own piece" << endl;
            return false;
        }
    }
    
    // Check for knight's rules
    int vert_d = abs(myCoord.row - dest.row);
    int horiz_d = abs(myCoord.col - dest.col);
    if ((vert_d == 2 && horiz_d == 1) || (vert_d == 1 && horiz_d == 2)) {
        return true;
    } else {
        return false;
    }
    
}


bool Knight::movePiece(Point dest) {
    if (!this->canMoveTo(dest)) {
        return false;
    }
    Point myCoord = getCoordinate();
    Board * theBoard = getBoard();
    // Start moving the piece
    theBoard->takePiece(myCoord);
    // If piece at dest, clear the piece first
    if (theBoard->pieceAt(dest)) {
        theBoard->removePiece(dest);
    }
    // Place the piece at dest
    theBoard->landPiece(this, dest);
    setCoordinate(dest);
    theBoard->updateLastMoved(this);
    return true;
}
