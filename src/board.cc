//
//  board.cpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-23.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#include "board.h"
#include "GraphicDisplay.h"
#include "window.h"

using namespace std;

/*
std::vector <std::vector<Piece *>> theBoard;
std::vector <Piece *> BlackPieces;
std::vector <Piece *> WhitePieces;
Piece * BlackKing;
Piece * WhiteKing;
TextDisplay * td = nullptr; // The text display.
// GraphicDisplay * gd = nullptr; // The graphic display. */

int abs(int a) {
    if (a >= 0) {
        return a;
    } else {
        return -a;
    }
}

// const int boardSize = 8, defined in TextDisplay.h
Board::Board() {
    theBoard.resize(boardSize, std::vector<Piece *>(boardSize, nullptr));
    BlackKing = nullptr;
    WhiteKing = nullptr;
    td = new TextDisplay;
    Xwindow * xw = new Xwindow {520, 520};
    gd = new GraphicDisplay {xw};
}

Board::~Board() {
    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            delete theBoard[row][col];
        }
    }
    delete td;
    delete gd;
}

void Board::initialize() {
    // Back Row of White
    gd->initialize();
    for (int col = 0; col < boardSize; col++) {
        Point p{0, col};
        if (col == 0 || col == boardSize-1) {
            this->addPiece("R", p);
        } else if (col == 1 || col == 6) {
            this->addPiece("N", p);
        } else if (col == 2 || col == 5) {
            this->addPiece("B", p);
        } else if (col == 3) {
            this->addPiece("Q", p);
        } else if (col == 4) {
            this->addPiece("K", p);
        }
    }
    // Pawn Row of White
    for (int col = 0; col < boardSize; col++) {
        Point p{1, col};
        this->addPiece("P", p);
    }
    // Back Row of Black
    for (int col = 0; col < boardSize; col++) {
        Point p{7, col};
        if (col == 0 || col == boardSize-1) {
            this->addPiece("r", p);
        } else if (col == 1 || col == 6) {
            this->addPiece("n", p);
        } else if (col == 2 || col == 5) {
            this->addPiece("b", p);
        } else if (col == 3) {
            this->addPiece("q", p);
        } else if (col == 4) {
            this->addPiece("k", p);
        }
    }
    // Pawn Row of Black
    for (int col = 0; col < boardSize; col++) {
        Point p{6, col};
        this->addPiece("p", p);
    }
}

void Board::reset() {
    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            delete theBoard[row][col];
        }
    }
    
    for (int i = 0; i < boardSize; i++) {
        theBoard[i].clear();
    }
    theBoard.clear();
    theBoard.resize(boardSize, std::vector<Piece *>(boardSize, nullptr));
    BlackPieces.clear();
    WhitePieces.clear();
    BlackKing = nullptr;
    WhiteKing = nullptr;
    delete td;
    delete gd;
    td = new TextDisplay;
    Xwindow * xw = new Xwindow {520, 520};
    gd = new GraphicDisplay {xw};
}

void Board::addPiece(std::string NewPiece, Point ori) {
    // White Pawn
    if (NewPiece == "P") {
        if (WhitePieces.size() == 16) {
            cerr << "White already has full piece set" << endl;
            return;
        }
        theBoard[ori.row][ori.col] = new Pawn(Colour::White, PieceType::Pawn, ori, this);
        WhitePieces.emplace_back(theBoard[ori.row][ori.col]);
        if (ori.row != 1) {
            static_cast<Pawn *>(theBoard[ori.row][ori.col])->setMoved();
        }
        td->nofity(ori.row, ori.col, NewPiece[0]);
        gd->notify(ori.row, ori.col, Colour::White, "P");
    }
    // Black Pawn
    else if (NewPiece == "p") {
        if (BlackPieces.size() == 16) {
            cerr << "Black already has full piece set" << endl;
            return;
        }
        theBoard[ori.row][ori.col] = new Pawn(Colour::Black, PieceType::Pawn, ori, this);
        BlackPieces.emplace_back(theBoard[ori.row][ori.col]);
        if (ori.row != 6) {
            static_cast<Pawn *>(theBoard[ori.row][ori.col])->setMoved();
        }
        td->nofity(ori.row, ori.col, NewPiece[0]);
        gd->notify(ori.row, ori.col, Colour::Black, "P");
    }
    // White King
    else if (NewPiece == "K") {
        if (WhiteKing) {
            cerr << "Already has a White King" << endl;
            return;
        } else if (WhitePieces.size() == 16) {
            cerr << "White already has full piece set" << endl;
            return;
        }
        theBoard[ori.row][ori.col] = new King(Colour::White, PieceType::King, ori, this);
        WhitePieces.emplace_back(theBoard[ori.row][ori.col]);
        WhiteKing = theBoard[ori.row][ori.col];
        if (!(ori.row == 0 && ori.col == 4)) {
            static_cast<King *>(theBoard[ori.row][ori.col])->setMoved();
        }
        td->nofity(ori.row, ori.col, NewPiece[0]);
        gd->notify(ori.row, ori.col, Colour::White, "K");
    }
    // Black King
    else if (NewPiece == "k") {
        if (BlackKing) {
            cerr << "Already has a Black King" << endl;
            return;
        } else if (BlackPieces.size() == 16) {
            cerr << "Black already has full piece set" << endl;
            return;
        }
        theBoard[ori.row][ori.col] = new King(Colour::Black, PieceType::King, ori, this);
        BlackPieces.emplace_back(theBoard[ori.row][ori.col]);
        BlackKing = theBoard[ori.row][ori.col];
        if (!(ori.row == 7 && ori.col == 4)) {
            static_cast<King *>(theBoard[ori.row][ori.col])->setMoved();
        }
        td->nofity(ori.row, ori.col, NewPiece[0]);
        gd->notify(ori.row, ori.col, Colour::Black, "K");
    }
    // White Queen
    else if (NewPiece == "Q") {
        if (WhitePieces.size() == 16) {
            cerr << "White already has full piece set" << endl;
            return;
        }
        theBoard[ori.row][ori.col] = new Queen(Colour::White, PieceType::Queen, ori, this);
        WhitePieces.emplace_back(theBoard[ori.row][ori.col]);
        td->nofity(ori.row, ori.col, NewPiece[0]);
        gd->notify(ori.row, ori.col, Colour::White, "Q");
    }
    // Black Queen
    else if (NewPiece == "q") {
        if (BlackPieces.size() == 16) {
            cerr << "Black already has full piece set" << endl;
            return;
        }
        theBoard[ori.row][ori.col] = new Queen(Colour::Black, PieceType::Queen, ori, this);
        BlackPieces.emplace_back(theBoard[ori.row][ori.col]);
        td->nofity(ori.row, ori.col, NewPiece[0]);
        gd->notify(ori.row, ori.col, Colour::Black, "Q");
    }
    // White Bishop
    else if (NewPiece == "B") {
        if (WhitePieces.size() == 16) {
            cerr << "White already has full piece set" << endl;
            return;
        }
        theBoard[ori.row][ori.col] = new Bishop(Colour::White, PieceType::Bishop, ori, this);
        WhitePieces.emplace_back(theBoard[ori.row][ori.col]);
        td->nofity(ori.row, ori.col, NewPiece[0]);
        gd->notify(ori.row, ori.col, Colour::White, "B");
    }
    // Black Bishop
    else if (NewPiece == "b") {
        if (BlackPieces.size() == 16) {
            cerr << "Black already has full piece set" << endl;
            return;
        }
        theBoard[ori.row][ori.col] = new Bishop(Colour::Black, PieceType::Bishop, ori, this);
        BlackPieces.emplace_back(theBoard[ori.row][ori.col]);
        td->nofity(ori.row, ori.col, NewPiece[0]);
        gd->notify(ori.row, ori.col, Colour::Black, "B");
    }
    // White Knight
    else if (NewPiece == "N") {
        if (WhitePieces.size() == 16) {
            cerr << "White already has full piece set" << endl;
            return;
        }
        theBoard[ori.row][ori.col] = new Knight(Colour::White, PieceType::Knight, ori, this);
        WhitePieces.emplace_back(theBoard[ori.row][ori.col]);
        td->nofity(ori.row, ori.col, NewPiece[0]);
        gd->notify(ori.row, ori.col, Colour::White, "N");
    }
    // Black Knight
    else if (NewPiece == "n") {
        if (BlackPieces.size() == 16) {
            cerr << "Black already has full piece set" << endl;
            return;
        }
        theBoard[ori.row][ori.col] = new Knight(Colour::Black, PieceType::Knight, ori, this);
        BlackPieces.emplace_back(theBoard[ori.row][ori.col]);
        td->nofity(ori.row, ori.col, NewPiece[0]);
        gd->notify(ori.row, ori.col, Colour::Black, "N");
    }
    // White Rook
    else if (NewPiece == "R") {
        if (WhitePieces.size() == 16) {
            cerr << "White already has full piece set" << endl;
            return;
        }
        theBoard[ori.row][ori.col] = new Rook(Colour::White, PieceType::Rook, ori, this);
        WhitePieces.emplace_back(theBoard[ori.row][ori.col]);
        if (!((ori.row == 0 && ori.col == 0) || (ori.row == 0 && ori.col == 7))) {
            static_cast<Rook *>(theBoard[ori.row][ori.col])->setMoved();
        }
        td->nofity(ori.row, ori.col, NewPiece[0]);
        gd->notify(ori.row, ori.col, Colour::White, "R");
    }
    // Black Rook
    else if (NewPiece == "r") {
        if (BlackPieces.size() == 16) {
            cerr << "Black already has full piece set" << endl;
            return;
        }
        theBoard[ori.row][ori.col] = new Rook(Colour::Black, PieceType::Rook, ori, this);
        BlackPieces.emplace_back(theBoard[ori.row][ori.col]);
        if (!((ori.row == 7 && ori.col == 0) || (ori.row == 7 && ori.col == 7))) {
            static_cast<Rook *>(theBoard[ori.row][ori.col])->setMoved();
        }
        td->nofity(ori.row, ori.col, NewPiece[0]);
        gd->notify(ori.row, ori.col, Colour::Black, "R");
    }
    else {
        cerr << "Please enter a valid piece type" << endl;
    }
}

void Board::removePiece(Point ori) {
    Piece * target = theBoard[ori.row][ori.col];
    if (target == nullptr) {
        return;
    }
    PieceType myType = target->getType();
    Colour myColour = target->getColour();
    delete target;
    theBoard[ori.row][ori.col] = nullptr;
    if (myColour == Colour::Black) {
        for (int i = 0; i < static_cast<int>(BlackPieces.size()); i++) {
            Point p = BlackPieces[i]->getCoordinate();
            if (p.row == ori.row && p.col == ori.col) {
                BlackPieces.erase(BlackPieces.begin() + i);
            }
        }
        if (myType == PieceType::King) {
            BlackKing = nullptr;
        }
    } else if (myColour == Colour::White) {
        for (int i = 0; i < static_cast<int>(WhitePieces.size()); i++) {
            Point p = WhitePieces[i]->getCoordinate();
            if (p.row == ori.row && p.col == ori.col) {
                WhitePieces.erase(WhitePieces.begin() + i);
            }
        }
        if (myType == PieceType::King) {
            WhiteKing = nullptr;
        }
    }
    if ((ori.row + ori.col)%2 == 0) {
        td->nofity(ori.row, ori.col, '_');
        gd->notify(ori.row, ori.col, Colour::White, "empty");
    } else {
        td->nofity(ori.row, ori.col, ' ');
        gd->notify(ori.row, ori.col, Colour::Black, "empty");
    }
}

Piece * Board::pieceAt(Point p) {
    return theBoard[p.row][p.col];
}

string Board::getPromotionType() {
    return PawnPromoteTo;
}

Piece * Board::getLastMoved() {
    return LastMovedPiece;
}
void Board::updateLastMoved(Piece * pie) {
    LastMovedPiece = pie;
}

bool Board::oneBlackKing() {
    if (BlackKing == nullptr) {
        cerr << "There is no Black King on board" << endl;
        return false;
    } else {
        int kingOccurence = 0;
        for (auto it = BlackPieces.begin(); it != BlackPieces.end(); ++it) {
            if ((*it)->getType() == PieceType::King) {
                kingOccurence += 1;
            }
        }
        if (kingOccurence == 1) {
            return true;
        } else {
            return false;
        }
    }
}

bool Board::oneWhiteKing() {
    if (WhiteKing == nullptr) {
        cerr << "There is no White King on board" << endl;
        return false;
    } else {
        int kingOccurence = 0;
        for (auto it = WhitePieces.begin(); it != WhitePieces.end(); ++it) {
            if ((*it)->getType() == PieceType::King) {
                kingOccurence += 1;
            }
        }
        if (kingOccurence == 1) {
            return true;
        } else {
            return false;
        }
    }
}

void Board::setUpGraphic() {
    gd->initialize();
}

void Board::takePiece(Point p) {
    theBoard[p.row][p.col] = nullptr;
    if ((p.row + p.col)%2 == 0) {
        td->nofity(p.row, p.col, '_');
        gd->notify(p.row, p.col, Colour::White, "empty");
    } else {
        td->nofity(p.row, p.col, ' ');
        gd->notify(p.row, p.col, Colour::Black, "empty");
    }
}

void Board::landPiece(Piece *myPiece, Point dest) {
    theBoard[dest.row][dest.col] = myPiece;
    Colour myColour = myPiece->getColour();
    PieceType myType = myPiece->getType();
    
    // Black Piece
    if (myColour == Colour::Black) {
        if (myType == PieceType::Pawn) {
            td->nofity(dest.row, dest.col, 'p');
            gd->notify(dest.row, dest.col, Colour::Black, "P");
        } else if (myType == PieceType::Rook) {
            td->nofity(dest.row, dest.col, 'r');
            gd->notify(dest.row, dest.col, Colour::Black, "R");
        } else if (myType == PieceType::Knight) {
            td->nofity(dest.row, dest.col, 'n');
            gd->notify(dest.row, dest.col, Colour::Black, "N");
        } else if (myType == PieceType::Bishop) {
            td->nofity(dest.row, dest.col, 'b');
            gd->notify(dest.row, dest.col, Colour::Black, "B");
        } else if (myType == PieceType::Queen) {
            td->nofity(dest.row, dest.col, 'q');
            gd->notify(dest.row, dest.col, Colour::Black, "Q");
        } else {
            td->nofity(dest.row, dest.col, 'k');
            gd->notify(dest.row, dest.col, Colour::Black, "K");
        }
    }
    
    // White Piece
    if (myColour == Colour::White) {
        if (myType == PieceType::Pawn) {
            td->nofity(dest.row, dest.col, 'P');
            gd->notify(dest.row, dest.col, Colour::White, "P");
        } else if (myType == PieceType::Rook) {
            td->nofity(dest.row, dest.col, 'R');
            gd->notify(dest.row, dest.col, Colour::White, "R");
        } else if (myType == PieceType::Knight) {
            td->nofity(dest.row, dest.col, 'N');
            gd->notify(dest.row, dest.col, Colour::White, "N");
        } else if (myType == PieceType::Bishop) {
            td->nofity(dest.row, dest.col, 'B');
            gd->notify(dest.row, dest.col, Colour::White, "B");
        } else if (myType == PieceType::Queen) {
            td->nofity(dest.row, dest.col, 'Q');
            gd->notify(dest.row, dest.col, Colour::White, "Q");
        } else {
            td->nofity(dest.row, dest.col, 'K');
            gd->notify(dest.row, dest.col, Colour::White, "K");
        }
    }
}

void Board::updateKingLocation(Piece * dest) {
    PieceType myType = dest->getType();
    if (myType != PieceType::King) {
        cerr << "You are updating a non-King piece" << endl;
        return;
    }
    Colour myColour = dest->getColour();
    if (myColour == Colour::Black) {
        BlackKing = dest;
    } else {
        WhiteKing = dest;
    }
}

bool Board::noPieceBetween(Point me, Point dest, Direction direction) {
    //Assuming dest is either on a diagonal line or a straight line from me
    // distance represent the number of legal one-cell move needed to move
    // the piece from "me" to "dest"
    int distance = abs(me.row - dest.row);
    if (me.row == dest.row) { // If "dest" is on the same row as "me"
        distance = abs(me.col - dest.col);
    }
    if (direction == Direction::NW) {
        for (int i = 1; i < distance; i++) {
            Point p{me.row - i, me.col - i};
            if (pieceAt(p) != nullptr) {
                return false;
            }
        }
        return true;
    } else if (direction == Direction::N) {
        for (int i = 1; i < distance; i++) {
            Point p{me.row - i, me.col};
            if (pieceAt(p) != nullptr) {
                return false;
            }
        }
        return true;
    } else if (direction == Direction::NE) {
        for (int i = 1; i < distance; i++) {
            Point p{me.row - i, me.col + i};
            if (pieceAt(p) != nullptr) {
                return false;
            }
        }
        return true;
    } else if (direction == Direction::W) {
        for (int i = 1; i < distance; i++) {
            Point p{me.row, me.col - i};
            if (pieceAt(p) != nullptr) {
                return false;
            }
        }
        return true;
    } else if (direction == Direction::E) {
        for (int i = 1; i < distance; i++) {
            Point p{me.row, me.col + i};
            if (pieceAt(p) != nullptr) {
                return false;
            }
        }
        return true;
    } else if (direction == Direction::SW) {
        for (int i = 1; i < distance; i++) {
            Point p{me.row + i, me.col - i};
            if (pieceAt(p) != nullptr) {
                return false;
            }
        }
        return true;
    }  else if (direction == Direction::S) {
        for (int i = 1; i < distance; i++) {
            Point p{me.row + i, me.col};
            if (pieceAt(p) != nullptr) {
                return false;
            }
        }
        return true;
    } else {
        for (int i = 1; i < distance; i++) {
            Point p{me.row + i, me.col + i};
            if (pieceAt(p) != nullptr) {
                return false;
            }
        }
        return true;
    }
}

bool Board::isCheck(Colour KingColour) {
    if (KingColour == Colour::Black) {
        return underAttack(BlackKing->getCoordinate(), Colour::White);
    } else {
        return underAttack(WhiteKing->getCoordinate(), Colour::Black);
    }
}

bool Board::underAttack(Point p, Colour opponent) {
    // If a white piece is at p, check whether it's under attack of a black piece
    if (opponent == Colour::Black) {
        for (auto it = BlackPieces.begin(); it != BlackPieces.end(); ++it) {
            Piece * myPiece = *it;
            if (myPiece->canMoveTo(p) && myPiece->getType() != PieceType::Pawn) {
                return true;
            }
            if (myPiece->getType() == PieceType::Pawn) {
                Point myCoord = myPiece->getCoordinate();
                // Pawn capture is different
                if ((p.row == myCoord.row -1 && p.col == myCoord.col -1) ||
                    (p.row == myCoord.row -1 && p.col == myCoord.col +1)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    // If a black piece is at p, check whether it's under attack of a white piece
    else {
        for (auto it = WhitePieces.begin(); it != WhitePieces.end(); ++it) {
            Piece * myPiece = *it;
            if (myPiece->canMoveTo(p) && myPiece->getType() != PieceType::Pawn) {
                return true;
            }
            if (myPiece->getType() == PieceType::Pawn) {
                Point myCoord = myPiece->getCoordinate();
                // Pawn capture is different
                if ((p.row == myCoord.row +1 && p.col == myCoord.col -1) ||
                    (p.row == myCoord.row +1 && p.col == myCoord.col +1)) {
                    return true;
                }
            }
        }
        return false;
    }
}

bool Board::isCheckmate(Colour KingColour) {
    // Black King checkmate
    if (KingColour == Colour::Black) {
        bool Checkmate = true;
        Point BlackKingPos = BlackKing->getCoordinate();
        int bRow = BlackKingPos.row;
        int bCol = BlackKingPos.col;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) { // King's current position
                    continue;
                } else if (bRow+i < 0 || bRow+i > 7 || bCol+j < 0 || bCol+j > 7) { // Out of range
                    continue;
                } else {
                    Point Escape{bRow+i, bCol+j};
                    Checkmate = Checkmate && underAttack(Escape, Colour::White);
                }
            }
        }
        return Checkmate;
    }
    
    // White King Checkmate
    else {
        bool Checkmate = true;
        Point WhiteKingPos = WhiteKing->getCoordinate();
        int wRow = WhiteKingPos.row;
        int wCol = WhiteKingPos.col;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) { // King's current position
                    continue;
                } else if (wRow+i < 0 || wRow+i > 7 || wCol+j < 0 || wCol+j > 7) { // Out of range
                    continue;
                } else {
                    Point Escape{wRow+i, wCol+j};
                    Checkmate = Checkmate && underAttack(Escape, Colour::Black);
                }
            }
        }
        return Checkmate;
    }
}

bool Board::movePiece(Point ori, Point dest, Colour playerColour) {
    Piece * me = pieceAt(ori);
    if (me == nullptr) {
        cerr << "There is no piece here" << endl;
        return false;
    }
    // Pawn Promotion
    if (((dest.row == 0 && playerColour == Colour::Black) ||
        (dest.row == 7 && playerColour == Colour::White)) && me->getType() == PieceType::Pawn) {
        if (cin >> PawnPromoteTo) {
            if (PawnPromoteTo != "R" && PawnPromoteTo != "N" && PawnPromoteTo != "B"
                       && PawnPromoteTo != "Q" ) {
                cout << "Please enter a valid piece type to which the pawn is promoted" << endl;
                return false;
            }
        } else {
            if (me->getType() == PieceType::Pawn) {
                cerr << "Need to specift the piece type to which the pawn is promoted" << endl;
            }
            cin.clear();
        }
    }
    
    Colour oriColour = pieceAt(ori)->getColour();
    if (playerColour != oriColour) {
        cerr << "You can't move your opponent's piece" << endl;
        return false;
    } else {
        return pieceAt(ori)->movePiece(dest);
    }
}

bool Board::isStalemate() {
    for (auto piece : BlackPieces) {
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                Point dest {row, col};
                if (piece->canMoveTo(dest)) {
                    return false;
                }
            }
        }
    }
    for (auto piece : WhitePieces) {
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                Point dest {row, col};
                if (piece->canMoveTo(dest)) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Board::moveComputer1(Colour computerColour) {
    // Clear previous possible moves
    possibleMoves.clear();
    // If current computer is the black player
    if (computerColour == Colour::Black) {
	bool beingCheck = underAttack(BlackKing->getCoordinate(), Colour::White);
        // Go through the avaliable pieces
        for (auto piece : BlackPieces) {
            // Reach out to every point on the board
            for (int row = 0; row < 8; row++) {
                for (int col = 0; col < 8; col++) {
                    Point dest{row, col};
                    // If dest is a valid move for the current piece, add it to possibleMoves
                    if (piece->canMoveTo(dest)) {
			    if (beingCheck && piece->getType() == PieceType::King &&
                            !(underAttack(dest, Colour::White))) {
                            takePiece(piece->getCoordinate());
                            // If not under attack after I move the king
                            if (underAttack(dest, Colour::White)) {
                                landPiece(piece, piece->getCoordinate());
                                continue;
                            }
                            possibleMoves.emplace_back(computerMove{piece, dest, 9999});
                            landPiece(piece, piece->getCoordinate());
                            // Check for next step check
                        } else if (piece->getType() == PieceType::King &&
                                   underAttack(dest, Colour::White)) {
                            continue;
                        } else {
                        possibleMoves.emplace_back(computerMove{piece, dest, 0});
			}
                    }
                }
            }
        }
    // If current computer is the white player
    } else {
	bool beingCheck = underAttack(WhiteKing->getCoordinate(), Colour::Black);
        // Go through the avaliable pieces
        for (auto piece : WhitePieces) {
            // Reach out to every point on the board
            for (int row = 0; row < 8; row++) {
                for (int col = 0; col < 8; col++) {
                    Point dest{row, col};
                    // If dest is a valid move for the current piece, add it to possibleMoves
                    if (piece->canMoveTo(dest)) {
			    if (beingCheck && piece->getType() == PieceType::King &&
                            !(underAttack(dest, Colour::White))) {
                            takePiece(piece->getCoordinate());
                            // If not under attack after I move the king
                            if (underAttack(dest, Colour::White)) {
                                landPiece(piece, piece->getCoordinate());
                                continue;
                            }
                            possibleMoves.emplace_back(computerMove{piece, dest, 9999});
                            landPiece(piece, piece->getCoordinate());
                            // Check for next step check
                        } else if (piece->getType() == PieceType::King &&
                                   underAttack(dest, Colour::White)) {
                            continue;
                        } else {
                        possibleMoves.emplace_back(computerMove{piece, dest});
			}
                    }
                }
            }
        }
    }
    // Now we have gathered all the possible moves, execute a randow one
    int totalMoves = static_cast<int>(possibleMoves.size());
    // If totalMoves is 0, then there is no valid move and should return false
    if (totalMoves == 0) {
        return false;
    }
    // Shuffle all the possible moves
    for (int i = 0; i < totalMoves - 1; i++)
    {
        // generate a random number j such that i <= j < n and
        // swap the element present at index j with the element
        // present at current index i
        int j = i + rand() % (totalMoves - i);
        swap(possibleMoves[i], possibleMoves[j]);
    }
    // After shuffling, execute a random move
    // If king is in check, rescue the king first
    computerMove bestMove;
    int max_prior = -1; // Random move has a priorty of 0
    for (auto choice : possibleMoves) {
        if (choice.priority > max_prior) {
            bestMove.whichPiece = choice.whichPiece;
            (bestMove.dest).row = (choice.dest).row;
            (bestMove.dest).col = (choice.dest).col;
            bestMove.priority = choice.priority;
            max_prior = choice.priority;
        }
    }
    Piece * bestPiece = bestMove.whichPiece;
    bool result = bestPiece->movePiece(bestMove.dest);
    while (!result && static_cast<int>(possibleMoves.size()) > 0) {
        for (int i = 0; i < static_cast<int>(possibleMoves.size()); i++) {
            Point p = possibleMoves[i].dest;
            if (p.row == (bestMove.dest).row && p.col == (bestMove.dest).col) {
                possibleMoves.erase(possibleMoves.begin() + i);
            }
        }
        int max_prior = -1; // Random move has a priorty of 0
        for (auto choice : possibleMoves) {
            if (choice.priority > max_prior) {
                bestMove.whichPiece = choice.whichPiece;
                (bestMove.dest).row = (choice.dest).row;
                (bestMove.dest).col = (choice.dest).col;
                bestMove.priority = choice.priority;
                max_prior = choice.priority;
            }
        }
        result = bestPiece->movePiece(bestMove.dest);
    }
    return result;
}

bool Board::moveComputer2(Colour computerColour) {
    // Clear previous possible moves
    possibleMoves.clear();
    // If current computer is the black player
    if (computerColour == Colour::Black) {
        bool beingCheck = underAttack(BlackKing->getCoordinate(), Colour::White);
        // Go through the avaliable pieces
        for (auto piece : BlackPieces) {
            // Reach out to every point on the board
            for (int row = 0; row < 8; row++) {
                for (int col = 0; col < 8; col++) {
                    // Check for next step check
                    Point dest{row, col};
                    Point myCoord = piece->getCoordinate();
                    piece->setCoordinate(dest);
                    bool nextStepCheck = piece->canMoveTo(WhiteKing->getCoordinate());
                    piece->setCoordinate(myCoord);
                    // If dest is a valid move for the current piece, add it to possible Moves
                    if (piece->canMoveTo(dest)) {
                        if (beingCheck && piece->getType() == PieceType::King &&
                            !(underAttack(dest, Colour::White))) {
                            takePiece(piece->getCoordinate());
                            // If not under attack after I move the king
                            if (underAttack(dest, Colour::White)) {
                                landPiece(piece, piece->getCoordinate());
                                continue;
                            }
                            possibleMoves.emplace_back(computerMove{piece, dest, 9999});
                            landPiece(piece, piece->getCoordinate());
                            // Check for next step check
                        } else if (piece->getType() == PieceType::King &&
                                   underAttack(dest, Colour::White)) {
                            continue;
                        } else if (nextStepCheck) {
                            possibleMoves.emplace_back(computerMove{piece, dest, 5000});
                        } else if (pieceAt(dest)) {
                            PieceType canCapture = pieceAt(dest)->getType();
                            if (canCapture == PieceType::Pawn) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 10});
                            } else if (canCapture == PieceType::Knight) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 20});
                            } else if (canCapture == PieceType::Bishop) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 30});
                            } else if (canCapture == PieceType::Rook) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 40});
                            } else {
                                possibleMoves.emplace_back(computerMove{piece, dest, 50});
                            }
                        } else {
                        possibleMoves.emplace_back(computerMove{piece, dest, 0});
                        }
                    }
                }
            }
        }
        // If current computer is the white player
    } else {
        // Go through the avaliable pieces
        for (auto piece : WhitePieces) {
            bool beingCheck = underAttack(WhiteKing->getCoordinate(), Colour::Black);
            // Reach out to every point on the board
            for (int row = 0; row < 8; row++) {
                for (int col = 0; col < 8; col++) {
                    // Check for next step check
                    Point dest{row, col};
                    Point myCoord = piece->getCoordinate();
                    piece->setCoordinate(dest);
                    bool nextStepCheck = piece->canMoveTo(BlackKing->getCoordinate());
                    piece->setCoordinate(myCoord);
                    // If dest is a valid move for the current piece, add it to possible Moves
                    if (piece->canMoveTo(dest)) {
                        if (beingCheck && piece->getType() == PieceType::King &&
                            !(underAttack(dest, Colour::Black))) {
                            takePiece(piece->getCoordinate());
                            // If not under attack after I move the king
                            if (underAttack(dest, Colour::Black)) {
                                landPiece(piece, piece->getCoordinate());
                                continue;
                            }
                            possibleMoves.emplace_back(computerMove{piece, dest, 9999});
                            landPiece(piece, piece->getCoordinate());
                        } else if (piece->getType() == PieceType::King &&
                                   underAttack(dest, Colour::Black)) {
                            continue;
                        } else if (nextStepCheck) {
                            possibleMoves.emplace_back(computerMove{piece, dest, 5000});
                        } else if (pieceAt(dest)) {
                            PieceType canCapture = pieceAt(dest)->getType();
                            if (canCapture == PieceType::Pawn) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 10});
                            } else if (canCapture == PieceType::Knight) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 20});
                            } else if (canCapture == PieceType::Bishop) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 30});
                            } else if (canCapture == PieceType::Rook) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 40});
                            } else {
                                possibleMoves.emplace_back(computerMove{piece, dest, 50});
                            }
                        } else {
                            possibleMoves.emplace_back(computerMove{piece, dest, 0});
                        }
                    }
                }
            }
        }
    }
    
    // Now we have gathered all the possible moves, execute a randow one
    int totalMoves = static_cast<int>(possibleMoves.size());
    // If totalMoves is 0, then there is no valid move and should return false
    if (totalMoves == 0) {
        return false;
    }
    // Shuffle all the possible moves
    for (int i = 0; i < totalMoves - 1; i++)
    {
        // generate a random number j such that i <= j < n and
        // swap the element present at index j with the element
        // present at current index i
        int j = i + rand() % (totalMoves - i);
        swap(possibleMoves[i], possibleMoves[j]);
    }
    // Select a move with priority
    computerMove bestMove;
    int max_prior = -1; // Random move has a priorty of 0
    for (auto choice : possibleMoves) {
        if (choice.priority > max_prior) {
            bestMove.whichPiece = choice.whichPiece;
            (bestMove.dest).row = (choice.dest).row;
            (bestMove.dest).col = (choice.dest).col;
            bestMove.priority = choice.priority;
            max_prior = choice.priority;
        }
    }
    Piece * bestPiece = bestMove.whichPiece;
    bool result = bestPiece->movePiece(bestMove.dest);
    while (!result && static_cast<int>(possibleMoves.size()) > 0) {
        for (int i = 0; i < static_cast<int>(possibleMoves.size()); i++) {
            Point p = possibleMoves[i].dest;
            if (p.row == (bestMove.dest).row && p.col == (bestMove.dest).col) {
                possibleMoves.erase(possibleMoves.begin() + i);
            }
        }
        int max_prior = -1; // Random move has a priorty of 0
        for (auto choice : possibleMoves) {
            if (choice.priority > max_prior) {
                bestMove.whichPiece = choice.whichPiece;
                (bestMove.dest).row = (choice.dest).row;
                (bestMove.dest).col = (choice.dest).col;
                bestMove.priority = choice.priority;
                max_prior = choice.priority;
            }
        }
        result = bestPiece->movePiece(bestMove.dest);
    }
    return result;
}


bool Board::moveComputer3(Colour computerColour) {
    // Clear previous possible moves
    possibleMoves.clear();
    // If current computer is the black player
    if (computerColour == Colour::Black) {
        bool beingCheck = underAttack(BlackKing->getCoordinate(), Colour::White);
        // Go through the avaliable pieces
        for (auto piece : BlackPieces) {
            // Reach out to every point on the board
            for (int row = 0; row < 8; row++) {
                for (int col = 0; col < 8; col++) {
                    // Check for next step check
                    Point dest{row, col};
                    Point myCoord = piece->getCoordinate();
                    piece->setCoordinate(dest);
                    bool nextStepCheck = piece->canMoveTo(WhiteKing->getCoordinate());
                    piece->setCoordinate(myCoord);
                    // If dest is a valid move for the current piece, add it to possible Moves
                    if (piece->canMoveTo(dest)) {
                       if (beingCheck && piece->getType() == PieceType::King &&
                            !(underAttack(dest, Colour::White))) {
                            takePiece(piece->getCoordinate());
                            // If not under attack after I move the king
                            if (underAttack(dest, Colour::White)) {
                                landPiece(piece, piece->getCoordinate());
                                continue;
                            }
                            possibleMoves.emplace_back(computerMove{piece, dest, 9999});
                            landPiece(piece, piece->getCoordinate());
                            // Check for next step check
                        } else if (piece->getType() == PieceType::King &&
                                   underAttack(dest, Colour::White)) {
                            continue;
                        } else if (nextStepCheck) {
                            possibleMoves.emplace_back(computerMove{piece, dest, 5000});
                        } else if (underAttack(piece->getCoordinate(), Colour::White)) {
                            if (piece->getType() == PieceType::Pawn) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 100});
                            } else if (piece->getType() == PieceType::Knight) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 200});
                            } else if (piece->getType() == PieceType::Bishop) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 300});
                            } else if (piece->getType() == PieceType::Rook) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 400});
                            } else {
                                possibleMoves.emplace_back(computerMove{piece, dest, 500});
                            }
                            // Capture piece
                        } else if (pieceAt(dest)) {
                            PieceType canCapture = pieceAt(dest)->getType();
                            if (canCapture == PieceType::Pawn) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 10});
                            } else if (canCapture == PieceType::Knight) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 20});
                            } else if (canCapture == PieceType::Bishop) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 30});
                            } else if (canCapture == PieceType::Rook) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 40});
                            } else {
                                possibleMoves.emplace_back(computerMove{piece, dest, 50});
                            }
                            // Random move
                        } else {
                            possibleMoves.emplace_back(computerMove{piece, dest, 0});
                        }
                    }
                }
            }
        }
        // If current computer is the white player
    } else {
        // Go through the avaliable pieces
        for (auto piece : WhitePieces) {
            bool beingCheck = underAttack(WhiteKing->getCoordinate(), Colour::Black);
            // Reach out to every point on the board
            for (int row = 0; row < 8; row++) {
                for (int col = 0; col < 8; col++) {
                    // Check for next step check
                    Point dest{row, col};
                    Point myCoord = piece->getCoordinate();
                    piece->setCoordinate(dest);
                    bool nextStepCheck = piece->canMoveTo(BlackKing->getCoordinate());
                    piece->setCoordinate(myCoord);
                    // If dest is a valid move for the current piece, add it to possibleMoves
                    if (piece->canMoveTo(dest)) {
                        if (beingCheck && piece->getType() == PieceType::King &&
                            !(underAttack(dest, Colour::Black))) {
                            takePiece(piece->getCoordinate());
                            // If not under attack after I move the king
                            if (underAttack(dest, Colour::Black)) {
                                landPiece(piece, piece->getCoordinate());
                                continue;
                            }
                            possibleMoves.emplace_back(computerMove{piece, dest, 9999});
                            landPiece(piece, piece->getCoordinate());
                        } else if (piece->getType() == PieceType::King &&
                                   underAttack(dest, Colour::Black)) {
                            continue;
                        } else if (nextStepCheck) {
                            possibleMoves.emplace_back(computerMove{piece, dest, 5000});
                        } else if (underAttack(piece->getCoordinate(), Colour::Black)) {
                            if (piece->getType() == PieceType::Pawn) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 100});
                            } else if (piece->getType() == PieceType::Knight) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 200});
                            } else if (piece->getType() == PieceType::Bishop) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 300});
                            } else if (piece->getType() == PieceType::Rook) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 400});
                            } else {
                                possibleMoves.emplace_back(computerMove{piece, dest, 500});
                            }
                            // Capture piece
                        } else if (pieceAt(dest)) {
                            PieceType canCapture = pieceAt(dest)->getType();
                            if (canCapture == PieceType::Pawn) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 10});
                            } else if (canCapture == PieceType::Knight) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 20});
                            } else if (canCapture == PieceType::Bishop) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 30});
                            } else if (canCapture == PieceType::Rook) {
                                possibleMoves.emplace_back(computerMove{piece, dest, 40});
                            } else {
                                possibleMoves.emplace_back(computerMove{piece, dest, 50});
                            }
                            // Random move
                        } else {
                            possibleMoves.emplace_back(computerMove{piece, dest, 0});
                        }
                    }
                }
            }
        }
    }
    // Now we have gathered all the possible moves, execute a randow one
    int totalMoves = static_cast<int>(possibleMoves.size());
    // If totalMoves is 0, then there is no valid move and should return false
    if (totalMoves == 0) {
        return false;
    }
    // Shuffle all the possible moves
    for (int i = 0; i < totalMoves - 1; i++)
    {
        // generate a random number j such that i <= j < n and
        // swap the element present at index j with the element
        // present at current index i
        int j = i + rand() % (totalMoves - i);
        swap(possibleMoves[i], possibleMoves[j]);
    }
    // Select a move with priority
    computerMove bestMove;
    int max_prior = -1; // Random move has a priorty of 0
    for (auto choice : possibleMoves) {
        if (choice.priority > max_prior) {
            bestMove.whichPiece = choice.whichPiece;
            (bestMove.dest).row = (choice.dest).row;
            (bestMove.dest).col = (choice.dest).col;
            bestMove.priority = choice.priority;
            max_prior = choice.priority;
        }
    }
    Piece * bestPiece = bestMove.whichPiece;
    bool result = bestPiece->movePiece(bestMove.dest);
    while (!result && static_cast<int>(possibleMoves.size()) > 0) {
        for (int i = 0; i < static_cast<int>(possibleMoves.size()); i++) {
            Point p = possibleMoves[i].dest;
            if (p.row == (bestMove.dest).row && p.col == (bestMove.dest).col) {
                possibleMoves.erase(possibleMoves.begin() + i);
            }
        }
        int max_prior = -1; // Random move has a priorty of 0
        for (auto choice : possibleMoves) {
            if (choice.priority > max_prior) {
                bestMove.whichPiece = choice.whichPiece;
                (bestMove.dest).row = (choice.dest).row;
                (bestMove.dest).col = (choice.dest).col;
                bestMove.priority = choice.priority;
                max_prior = choice.priority;
            }
        }
        result = bestPiece->movePiece(bestMove.dest);
    }
    return result;
}

bool Board::moveComputer4(Colour computerColour) {
    return true;
}

std::ostream& operator<<(std::ostream &out, const Board &b) {
    out << *(b.td);
    return out;
}
