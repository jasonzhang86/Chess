//
//  pawn.cpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-23.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#include "pawn.h"
#include "board.h"
using namespace std;

Pawn::Pawn(Colour colour, PieceType Type, Point coordinate, Board *b):
Piece(colour, Type, coordinate, b) {}

bool Pawn::hasMoved() {
    return moved;
}

void Pawn::setMoved() {
    moved = true;
}

bool Pawn::hasJumped() {
    return jumped;
}

void Pawn::setJumped(bool b) {
    jumped = b;
}

bool Pawn::canMoveTo(Point dest) {
    // Information of the piece being moved
    Colour myColour = getColour();
    Point myCoord = getCoordinate();
    // Can't move to the current position
    if (dest.row == myCoord.row && dest.col == myCoord.col) {
        return false;
    }
    // Information of the piece at target location
    Piece * target = getBoard()->pieceAt(dest);
    // If there is a piece at target
    if (target) {
    Colour destColour = target->getColour();
        if (destColour == myColour) {
            // cerr << "Can't capture your own piece" << endl;
            return false;
        }
    }
    // Black Pawn
    if (myColour == Colour::Black) {
        if (dest.row == myCoord.row - 1 && dest.col == myCoord.col && !target) {
            return true; // Normal move, forward one cell
        } else if (dest.row == myCoord.row - 2 && dest.col == myCoord.col && !target && !hasMoved()
			&& getBoard()->noPieceBetween(myCoord, dest, Direction::N)) {
            return true; // First move, forward two cell
        } else if (dest.row == myCoord.row - 1 && dest.col == myCoord.col - 1 && target &&
                   target->getColour() == Colour::White) {
            return true; // Capture move, NW
        } else if (dest.row == myCoord.row - 1 && dest.col == myCoord.col + 1 && target &&
                   target->getColour() == Colour::White) {
            return true; // Capture move, NE
        } else {
            // cerr << "Invalid Black Pawn Move" << endl;
            return false;
        }
    } else { // White Pawn
        if (dest.row == myCoord.row + 1 && dest.col == myCoord.col && !target) {
            return true; // Normal move, forward one cell
        } else if (dest.row == myCoord.row + 2 && dest.col == myCoord.col && !target && !hasMoved()
			&& getBoard()->noPieceBetween(myCoord, dest, Direction::S)) {
            return true; // First move, forward two cell
        } else if (dest.row == myCoord.row + 1 && dest.col == myCoord.col - 1 && target &&
                   target->getColour() == Colour::Black) {
            return true; // Capture move, SW
        } else if (dest.row == myCoord.row + 1 && dest.col == myCoord.col + 1 && target &&
                   target->getColour() == Colour::Black) {
            return true; // Capture move, SE
        } else {
            // cerr << "Invalid White Pawn Move" << endl;
            return false;
        }
    }
}

void Pawn::pawnPromotion(Point dest) {
    Point myCoord = getCoordinate();
    Colour myColour = getColour();
    Board * theBoard = getBoard();
    string PromotionType = theBoard->getPromotionType();
    // Remove the Pawn
    theBoard->removePiece(myCoord);
    // If piece at dest, clear the piece first
    if (theBoard->pieceAt(dest)) {
        theBoard->removePiece(dest);
    }
    // Start Promotion
    // Black Pawn
    if (myColour == Colour::Black) {
        if (PromotionType == "R") {
            theBoard->addPiece("r", dest);
            static_cast<Rook *>(theBoard->pieceAt(dest))->setMoved();
            theBoard->updateLastMoved(theBoard->pieceAt(dest));
        } else if (PromotionType == "N") {
            theBoard->addPiece("n", dest);
            theBoard->updateLastMoved(theBoard->pieceAt(dest));
        } else if (PromotionType == "B") {
            theBoard->addPiece("b", dest);
            theBoard->updateLastMoved(theBoard->pieceAt(dest));
        } else if (PromotionType == "Q") {
            theBoard->addPiece("q", dest);
            theBoard->updateLastMoved(theBoard->pieceAt(dest));
        }
    }
    // White Pawn
    else if (myColour == Colour::White) {
        if (PromotionType == "R") {
            theBoard->addPiece("R", dest);
            static_cast<Rook *>(theBoard->pieceAt(dest))->setMoved();
            theBoard->updateLastMoved(theBoard->pieceAt(dest));
        } else if (PromotionType == "N") {
            theBoard->addPiece("N", dest);
            theBoard->updateLastMoved(theBoard->pieceAt(dest));
        } else if (PromotionType == "B") {
            theBoard->addPiece("B", dest);
            theBoard->updateLastMoved(theBoard->pieceAt(dest));
        } else if (PromotionType == "Q") {
            theBoard->addPiece("Q", dest);
            theBoard->updateLastMoved(theBoard->pieceAt(dest));
        }
    }
}

bool Pawn::canEnPassant(Point dest) {
    Point myCoord = getCoordinate();
    Colour myColour = getColour();
    Board * theBoard = getBoard();
    // Can't move to the current position
    if (dest.row == myCoord.row && dest.col == myCoord.col) {
        return false;
    }
    // dest can't have any piece
    if (theBoard->pieceAt(dest)) {
        return false;
    }
    // Black Pawn EnPassant
    if (myColour == Colour::Black) {
        // Check for validity of dest
        if (!(dest.row == myCoord.row - 1 && dest.col == myCoord.col - 1) ||
            (dest.row == myCoord.row - 1 && dest.col == myCoord.col + 1)) {
                return false;
            }
        // Check the validity of piece being EnPassanted
        Point opponentPawn{dest.row + 1, dest.col};
        Piece * target = theBoard->pieceAt(opponentPawn);
        if (target->getType() != PieceType::Pawn) {
            cerr << "Can't EnPassant a non-pawn piece" << endl;
            return false;
        }
        // Check for: (1) Last move is made by this pawn, (2) Pawn "jumped" two squares forward
        if (theBoard->getLastMoved() == target && static_cast<Pawn *>(target)->hasJumped()) {
            return true;
        } else {
            return false;
        }
    }
        
    // White Pawn EnPassant
    else {
        // Check for validity of dest
        if (!(dest.row == myCoord.row + 1 && dest.col == myCoord.col - 1) ||
            (dest.row == myCoord.row + 1 && dest.col == myCoord.col + 1)) {
            return false;
        }
        // Check the validity of piece being EnPassanted
        Point opponentPawn{dest.row - 1, dest.col};
        Piece * target = theBoard->pieceAt(opponentPawn);
        if (target->getType() != PieceType::Pawn) {
            cerr << "Can't EnPassant a non-pawn piece" << endl;
            return false;
        }
        // Check for: (1) Last move is made by this pawn, (2) Pawn "jumped" two squares forward
        if (theBoard->getLastMoved() == target && static_cast<Pawn *>(target)->hasJumped()) {
            return true;
        } else {
            return false;
        }
    }
}

void Pawn::EnPassant(Point dest) {
    Point myCoord = getCoordinate();
    Board * theBoard = getBoard();
    Colour myColour = getColour();
    // Start moving the piece
    theBoard->takePiece(myCoord);
    theBoard->landPiece(this, dest);
    setCoordinate(dest);
    // Clear the piece being EnPassented
    if (myColour == Colour::Black) {
        Point opponentPawn{dest.row + 1, dest.col};
        theBoard->removePiece(opponentPawn);
    } else {
        Point opponentPawn{dest.row - 1, dest.col};
        theBoard->removePiece(opponentPawn);
    }
}

bool Pawn::movePiece(Point dest) {
    // Check for normal move
    if (!this->canMoveTo(dest)) {
        // Check for EnPassant
        if (canEnPassant(dest)) {
            EnPassant(dest);
            getBoard()->updateLastMoved(this);
            return true;
        }
        // Not a valid Pawn Move
        return false;
    }
    // Pawn Promotion
    if ((dest.row == 0 && getColour() == Colour::Black) ||
        (dest.row == 7 && getColour() == Colour::White)) {
        pawnPromotion(dest);
        return true;
    }
    setMoved();
    Point myCoord = getCoordinate();
    Board * theBoard = getBoard();
    if (myCoord.col == dest.col && abs(myCoord.row - dest.row) == 2) {
        setJumped(true);
    } else {
        setJumped(false);
    }
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
