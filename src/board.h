//
//  board.hpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-23.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include "computerMove.h"
#include "enum.h"
#include "piece.h"
#include "pawn.h"
#include "king.h"
#include "knight.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "textDisplay.h"

class TextDisplay;
class GraphicDisplay;

const int pieceSet = 16;

class Board {
    std::vector <std::vector<Piece *>> theBoard;
    std::vector <Piece *> BlackPieces;
    std::vector <Piece *> WhitePieces;
    Piece * BlackKing;
    Piece * WhiteKing;
    std::string PawnPromoteTo = "";
    std::vector <computerMove> possibleMoves;
    Piece * LastMovedPiece = nullptr;
    TextDisplay * td = nullptr; // The text display.
    GraphicDisplay * gd = nullptr; // The graphic display.
    
    
public:
    Board();
    ~Board();
    void initialize();
    void reset();
    // Setup Mode
    void addPiece(std::string NewPiece, Point ori);
    void removePiece(Point ori);
    Piece * pieceAt(Point p);
    std::string getPromotionType();
    Piece * getLastMoved();
    void updateLastMoved(Piece * pie);
    bool oneBlackKing();
    bool oneWhiteKing();
    void setUpGraphic();
    // Moving a Piece
    void takePiece(Point p);
    void landPiece(Piece *myPiece, Point dest);
    void updateKingLocation(Piece * dest);
    bool noPieceBetween(Point me, Point dest, Direction direction);
    bool isCheck(Colour KingColour);
    bool underAttack(Point p, Colour opponent);
    bool isCheckmate(Colour KingColour);
    bool isStalemate();
    bool movePiece(Point ori, Point dest, Colour colour);
    bool moveComputer1(Colour computerColour);
    bool moveComputer2(Colour computerColour);
    bool moveComputer3(Colour computerColour);
    bool moveComputer4(Colour computerColour);
    
    friend std::ostream& operator<<(std::ostream &out, const Board &b);
};


#endif /* board_hpp */
