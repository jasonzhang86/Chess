//
//  player.cpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-26.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#include "player.h"
#include "board.h"
using namespace std;

Player::Player(Colour playerColour, string playerType, Board *theBoard)
:playerColour{playerColour}, playerType{playerType}, theBoard{theBoard} {}

Colour Player::getPlayerColour() {
    return playerColour;
}
string Player::getPlayerType() {
    return playerType;
}

Board * Player::getBoard() {
    return theBoard;
}

void Player::setBoard(Board *b) {
    theBoard = b;
}

bool Player::isCheck() {
    return getBoard()->isCheck(playerColour);
}

bool Player::isCheckmate() {
    return getBoard()->isCheckmate(playerColour);
}

bool Player::movePiece(Point ori, Point dest) {
    return getBoard()->movePiece(ori, dest, playerColour);
}

bool Player::moveComputer() {
    string level = getPlayerType();
    if (level == "computer[1]") {
        return getBoard()->moveComputer1(playerColour);
    } else if (level == "computer[2]") {
        return getBoard()->moveComputer2(playerColour);
    } else if (level == "computer[3]") {
        return getBoard()->moveComputer3(playerColour);
    } else {
        return getBoard()->moveComputer4(playerColour);
    }
}



