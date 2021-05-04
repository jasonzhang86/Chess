//
//  Rook.cpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-23.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#include "rook.h"
#include "board.h"
using namespace std;

Rook::Rook(Colour colour, PieceType Type, Point coordinate, Board *b):
Piece(colour, Type, coordinate, b) {}

bool Rook::hasMoved() {
    return moved;
}

void Rook::setMoved() {
    moved = true;
}

bool Rook::canMoveTo(Point dest) {
    // Information of the piece being moved
    Colour myColour = getColour();
    Point myCoord = getCoordinate();
    // Information of the target location
    Piece * target = getBoard()->pieceAt(dest);
    // Can't move to the current position
    if (dest.row == myCoord.row && dest.col == myCoord.col) {
        return false;
    }
    // If there is a piece at target
    if (target) {
        Colour destColour = target->getColour();
        if (destColour == myColour) {
            // cerr << "Can't capture your own piece" << endl;
            return false;
        }
    }
    // Now target location either is empty or has opponent's piece
    Direction targetDirection = whereIsDest(dest);
    if (!(targetDirection == Direction::N || targetDirection == Direction::S ||
          targetDirection == Direction::W || targetDirection == Direction::E)) {
            // cerr << "Rook can only move towards N, S, W, E" << endl;
            return false;
        }
    Board * theBoard = getBoard();
    if (theBoard->noPieceBetween(myCoord, dest, targetDirection)) {
        return true;
    } else {
        // cerr << "A piece blocking the way when trying to move a Rook" << endl;
        return false;
    }
}


bool Rook::movePiece(Point dest) {
    if (!this->canMoveTo(dest)) {
        return false;
    }
    setMoved();
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
