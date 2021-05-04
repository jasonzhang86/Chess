//
//  King.cpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-23.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#include "king.h"
#include "board.h"
using namespace std;

Colour oppositeColour(Colour c) {
    if (c == Colour::Black) {
        return Colour::White;
    } else {
        return Colour::Black;
    }
}

King::King(Colour colour, PieceType Type, Point coordinate, Board *b):
Piece(colour, Type, coordinate, b) {}

bool King::hasMoved() {
    return moved;
}
void King::setMoved() {
    moved = true;
}
bool King::canMoveTo(Point dest) {
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
    
    if (vert_d > 1 || horiz_d > 1){
        // cerr << "King can only move to the cells around it" << endl;
        return false;
    } else {
        return true;
    }
}

bool King::canCastleTo(Point dest) {
    Point myCoord = getCoordinate();
    Colour myColour = getColour();
    Board * theBoard = getBoard();
    // Can't move to the current position
    if (dest.row == myCoord.row && dest.col == myCoord.col) {
        return false;
    }
    // Castling to the left
    if (dest.row == myCoord.row && dest.col == myCoord.col - 2) {
        Point rookCoord{myCoord.row, myCoord.col - 4};
        // Check if king and rook are qualified
        Piece * target = theBoard->pieceAt(rookCoord);
        // Check for : (1) dest has a piece, (2) the piece is a rook, (3) it's your rook
        if (target == nullptr || target->getType() != PieceType::Rook || target->getColour() != myColour) {
            return false;
        }
        // Check neither piece has moved in this game
        if (hasMoved() || static_cast<Rook *>(target)->hasMoved()) {
            return false;
        }
        // Check no pieces between King and Rook
        if (!theBoard->noPieceBetween(myCoord, rookCoord, Direction::W)) {
            return false;
        }
        // Check none of the three cells is under attack
        Colour opponentColour = oppositeColour(myColour);
        Point RookLanding {myCoord.row, myCoord.col-1};
        if (theBoard->underAttack(myCoord, opponentColour) || theBoard->underAttack(dest, opponentColour)
            || theBoard->underAttack(RookLanding, opponentColour)) {
            return false;
        }
        return true;
    // Castling to the right
    } else if (dest.row == myCoord.row && dest.col == myCoord.col + 2) {
        Point rookCoord{myCoord.row, myCoord.col + 3};
        // Check if king and rook are qualified
        Piece * target = theBoard->pieceAt(rookCoord);
        // Check for : (1) dest has a piece, (2) the piece is a rook, (3) it's your rook
        if (target == nullptr || target->getType() != PieceType::Rook || target->getColour() != myColour) {
            return false;
        }
        // Check neither piece has moved in this game
        if (hasMoved() || static_cast<Rook *>(target)->hasMoved()) {
            return false;
        }
        // Check no pieces between King and Rook
        if (!theBoard->noPieceBetween(myCoord, rookCoord, Direction::E)) {
            return false;
        }
        // Check none of the three cells is under attack
        Colour opponentColour = oppositeColour(myColour);
        Point RookLanding {myCoord.row, myCoord.col+1};
        if (theBoard->underAttack(myCoord, opponentColour) || theBoard->underAttack(dest, opponentColour)
            || theBoard->underAttack(RookLanding, opponentColour)) {
            return false;
        }
        return true;
        // Otherwise not a possible castling dest
    } else {
        return false;
    }
}

// Set moved to rook and king
void King::CastleTo(Point dest) {
    setMoved();
    Point myCoord = getCoordinate();
    Board * theBoard = getBoard();
    //Left Rook
    if (dest.row == myCoord.row && dest.col == myCoord.col - 2) {
        Point rookCoord{myCoord.row, myCoord.col - 4};
        Point RookLanding {myCoord.row, myCoord.col - 1};
        Piece * rookPiece = theBoard->pieceAt(rookCoord);
        static_cast<Rook *>(rookPiece)->hasMoved();
        theBoard->takePiece(myCoord);
        theBoard->landPiece(this, dest);
        setCoordinate(dest);
        theBoard->updateKingLocation(this);
        theBoard->takePiece(rookCoord);
        theBoard->landPiece(rookPiece, RookLanding);
        rookPiece->setCoordinate(RookLanding);
    }
    // Right Rook
    else if (dest.row == myCoord.row && dest.col == myCoord.col + 2) {
        Point rookCoord{myCoord.row, myCoord.col + 3};
        Point RookLanding {myCoord.row, myCoord.col + 1};
        Piece * rookPiece = theBoard->pieceAt(rookCoord);
        static_cast<Rook *>(rookPiece)->hasMoved();
        theBoard->takePiece(myCoord);
        theBoard->landPiece(this, dest);
        setCoordinate(dest);
        theBoard->updateKingLocation(this);
        theBoard->takePiece(rookCoord);
        theBoard->landPiece(rookPiece, RookLanding);
        rookPiece->setCoordinate(RookLanding);
    }
        
}

bool King::movePiece(Point dest) {
    Board * theBoard = getBoard();
    Colour myColour = getColour();
    // Check whether is a common king move
    if (!this->canMoveTo(dest)) {
        // If not a common king move, check whether is a valid castling move
        if (canCastleTo(dest)) {
            CastleTo(dest);
            getBoard()->updateLastMoved(this);
            return true;
        
        } else {
        // Not a valid king move
        return false;
        }
    }
    // Cannot put your king in check
    if (theBoard->underAttack(dest, oppositeColour(myColour))) {
        cerr << "Can't put your king in check" << endl;
        return false;
    }
    // Execute king move process
    setMoved();
    Point myCoord = getCoordinate();
    // Start moving the piece
    theBoard->takePiece(myCoord);
    // If piece at dest, clear the piece first
    if (theBoard->pieceAt(dest)) {
        theBoard->removePiece(dest);
    }
    // Place the piece at dest
    theBoard->landPiece(this, dest);
    setCoordinate(dest);
    theBoard->updateKingLocation(this);
    theBoard->updateLastMoved(this);
    return true;
}
