//
//  queen.cpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-23.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#include "queen.h"
#include "board.h"
using namespace std;

Queen::Queen(Colour colour, PieceType Type, Point coordinate, Board *b):
Piece(colour, Type, coordinate, b) {}

bool Queen::canMoveTo(Point dest) {
    //Information of the piece being moved
    Colour myColour = getColour();
    Point myCoord = getCoordinate();
    // Can't move to the current position
    if (dest.row == myCoord.row && dest.col == myCoord.col) {
        return false;
    }
    int vert_d = abs(myCoord.row - dest.row);
    int horiz_d = abs(myCoord.col - dest.col);
    //Information of the piece at target location
    Piece * target = getBoard()->pieceAt(dest);
    if (target) {
        Colour destColour = target->getColour();
        if (destColour == myColour) {
            // cerr << "Can't capture your own piece" << endl;
            return false;
        }
    }
    
    Direction targetDirection = whereIsDest(dest);
    if (targetDirection == Direction::NW || targetDirection == Direction::NE ||
        targetDirection == Direction::SW || targetDirection == Direction::SE) {
        if (vert_d != horiz_d) {
            // cerr << "Vertical and Horizontal distance are different" << endl;
            return false;
        }
    }
            
    Board * theBoard = getBoard();
    if (theBoard->noPieceBetween(myCoord, dest, targetDirection)) {
        return true;
    } else {
        // cerr << "A piece blocking the way when trying to move a Queen" << endl;
        return false;
    }
}


bool Queen::movePiece(Point dest) {
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
