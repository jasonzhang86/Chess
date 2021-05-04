//
//  piece.cpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-23.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#include "piece.h"
using namespace std;

Piece::Piece(Colour colour, PieceType Type, Point coordinate, Board *b):
colour{colour}, Type{Type}, coordinate{coordinate}, b{b} {}

Piece::~Piece() {}

Colour Piece::getColour() {
    return colour;
}

PieceType Piece::getType() {
    return Type;
}

Point Piece::getCoordinate() {
    return coordinate;
}

Board* Piece::getBoard() {
    return b;
}

Direction Piece::whereIsDest(Point dest) {
    Point myCoord = getCoordinate();
    if (dest.row < myCoord.row && dest.col < myCoord.col) {
        return Direction::NW;
    } else if (dest.row < myCoord.row && dest.col == myCoord.col) {
        return Direction::N;
    } else if (dest.row < myCoord.row && dest.col > myCoord.col) {
        return Direction::NE;
    } else if (dest.row == myCoord.row && dest.col < myCoord.col) {
        return Direction::W;
    } else if (dest.row == myCoord.row && dest.col > myCoord.col) {
        return Direction::E;
    } else if (dest.row > myCoord.row && dest.col < myCoord.col) {
        return Direction::SW;
    } else if (dest.row > myCoord.row && dest.col == myCoord.col) {
        return Direction::S;
    } else  {
        return Direction::SE;
    }
}

void Piece::setCoordinate(Point dest) {
    coordinate = dest;
}

bool Piece::isCaptured() {
    return captured;
}

void Piece::capturePiece() {
    captured = true;
}
