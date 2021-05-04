//
//  main.cpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-21.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#include <iostream>
#include "board.h"
#include "player.h"
#include "textDisplay.h"
#include "enum.h"
using namespace std;

//205
//210 329 computepr move fail throw and catch?
//remove/set piece return type
int main(int argc, const char * argv[]) {
    Board b;
    Player *whitePlayer = nullptr;
    Player *blackPlayer = nullptr;
    Point moveFrom;
    Point moveTo;
    float whiteWins = 0;
    float blackWins = 0;
    bool isPlaying = false;
    bool isWhiteMove = true;
    bool setUp = false;
    //by defalut white player makes the first move.
    string s;
    
    while (cin >> s) {
        if (s == "game") {
            if (!isPlaying) {
                if (cin >> s) {
                    if (s == "human") {
                        whitePlayer = new Player {Colour::White, "human"};
                    } else if (s == "computer[1]") {
                        whitePlayer = new Player {Colour::White, "computer[1]"};
                    } else if (s == "computer[2]") {
                        whitePlayer = new Player {Colour::White, "computer[2]"};
                    } else if (s == "computer[3]") {
                        whitePlayer = new Player {Colour::White, "computer[3]"};
                    } else if (s == "computer[4]") {
                        whitePlayer = new Player {Colour::White, "computer[4]"};
                    } else {
                        cout << "Please enter correct information for player1: human / computer[1-4]" << endl;
                        continue;
                    }
                } else {
                    break; //if encounter EOF
                }
                
                if (cin >> s) {
                    if (s == "human") {
                        blackPlayer = new Player {Colour::Black, "human"};
                    } else if (s == "computer[1]") {
                        blackPlayer = new Player {Colour::Black, "computer[1]"};
                    } else if (s == "computer[2]") {
                        blackPlayer = new Player {Colour::Black, "computer[2]"};
                    } else if (s == "computer[3]") {
                        blackPlayer = new Player {Colour::Black, "computer[3]"};
                    } else if (s == "computer[4]") {
                        blackPlayer = new Player {Colour::Black, "computer[4]"};
                    } else {
                        delete whitePlayer;
                        cout << "Please enter correct information for player2: human / computer[1-4]" << endl;
                        continue;
                    }
                } else {
                    break; //if encounter EOF
                }
                
                isPlaying = true;
                if (!setUp) {
                    b.initialize();
                }
                cout << b;
                whitePlayer->setBoard(&b);
                blackPlayer->setBoard(&b);
            } else {
                cout << "There is an ongoing game, you cannot start a new one :(" << endl;
            }
        } else if (s == "resign") {
            if (!isPlaying) {
                cout << "There is no ongoing game, please start a new one before resigning." << endl;
            } else {
                if (isWhiteMove) {
                    ++blackWins;
                    cout << "White resigned, Black gets one point!" << endl;
                    cout << "Please start a new game or end to get the final score." << endl;
                } else {
                    ++whiteWins;
                    cout << "Black resigned, White gets one point!" << endl;
                    cout << "Please start a new game or end to get the final score." << endl;
                }
                //destroy the current game
                delete whitePlayer;
                delete blackPlayer;
                whitePlayer = nullptr;
                blackPlayer = nullptr;
                b.reset();
                isPlaying = false;
                setUp = false;
                isWhiteMove = true;
            }
        } else if (s == "move") {
            if (!isPlaying) {
                cout << "There is no ongoing game, please start a new one before resigning." << endl;
            } else if (isWhiteMove) {
                if (whitePlayer->getPlayerType() == "human") {
                    //getting moveFrom
                    if (cin >> s) {
                        if(s.length() == 2) {
                            //get col:
                            if (s[0] == 'a') {
                                moveFrom.col = 0;
                            } else if (s[0] == 'b') {
                                moveFrom.col = 1;
                            } else if (s[0] == 'c') {
                                moveFrom.col = 2;
                            } else if (s[0] == 'd') {
                                moveFrom.col = 3;
                            } else if (s[0] == 'e') {
                                moveFrom.col = 4;
                            } else if (s[0] == 'f') {
                                moveFrom.col = 5;
                            } else if (s[0] == 'g') {
                                moveFrom.col = 6;
                            } else if (s[0] == 'h') {
                                moveFrom.col = 7;
                            } else {
                                cout << "Please enter a column from a to h" << endl;
                                continue;
                            }
                            //get row:
                            if (s[1] == '1') {
                                moveFrom.row = 0;
                            } else if (s[1] == '2') {
                                moveFrom.row = 1;
                            } else if (s[1] == '3') {
                                moveFrom.row = 2;
                            } else if (s[1] == '4') {
                                moveFrom.row = 3;
                            } else if (s[1] == '5') {
                                moveFrom.row = 4;
                            } else if (s[1] == '6') {
                                moveFrom.row = 5;
                            } else if (s[1] == '7') {
                                moveFrom.row = 6;
                            } else if (s[1] == '8') {
                                moveFrom.row = 7;
                            } else {
                                cout << "Please enter a row number from 1 to 8" << endl;
                                continue;
                            }
                        } else {
                            cout << "Please enter correct move a-h + 1-8" << endl;
                            continue;
                        }
                    } else {
                        break; //if encounter EOF
                    }
                    //getting moveTo
                    if (cin >> s) {
                        if(s.length() == 2) {
                            //get col:
                            if (s[0] == 'a') {
                                moveTo.col = 0;
                            } else if (s[0] == 'b') {
                                moveTo.col = 1;
                            } else if (s[0] == 'c') {
                                moveTo.col = 2;
                            } else if (s[0] == 'd') {
                                moveTo.col = 3;
                            } else if (s[0] == 'e') {
                                moveTo.col = 4;
                            } else if (s[0] == 'f') {
                                moveTo.col = 5;
                            } else if (s[0] == 'g') {
                                moveTo.col = 6;
                            } else if (s[0] == 'h') {
                                moveTo.col = 7;
                            } else {
                                cout << "Please enter a column from a to h" << endl;
                                continue;
                            }
                            //get row:
                            if (s[1] == '1') {
                                moveTo.row = 0;
                            } else if (s[1] == '2') {
                                moveTo.row = 1;
                            } else if (s[1] == '3') {
                                moveTo.row = 2;
                            } else if (s[1] == '4') {
                                moveTo.row = 3;
                            } else if (s[1] == '5') {
                                moveTo.row = 4;
                            } else if (s[1] == '6') {
                                moveTo.row = 5;
                            } else if (s[1] == '7') {
                                moveTo.row = 6;
                            } else if (s[1] == '8') {
                                moveTo.row = 7;
                            } else {
                                cout << "Please enter a row number from 1 to 8" << endl;
                                continue;
                            }
                        } else {
                            cout << "Please enter correct move a-h + 1-8" << endl;
                            continue;
                        }
                    } else {
                        break; //if encounter EOF
                    }
                    //we've read in valid inputs, make move:
                    if (!(whitePlayer->movePiece(moveFrom, moveTo))) {
                        cout << "move unsuccessful :(" << endl;
                        cout << b;
                    } else {
                        cout << b;
                        isWhiteMove = false;
                    }
                } else {//white computer is making a move
                    if (!(whitePlayer->moveComputer())) {
                        cout << "move unsuccessful :(" << endl;
                        cout << b;
                        ////throw and catch???
                    } else {
                        cout << b;
                        isWhiteMove = false;
                    }
                }
            } else { //blackPlayer's turn to make a move
                if (blackPlayer->getPlayerType() == "human") {
                    //getting moveFrom
                    if (cin >> s) {
                        if(s.length() == 2) {
                            //get col:
                            if (s[0] == 'a') {
                                moveFrom.col = 0;
                            } else if (s[0] == 'b') {
                                moveFrom.col = 1;
                            } else if (s[0] == 'c') {
                                moveFrom.col = 2;
                            } else if (s[0] == 'd') {
                                moveFrom.col = 3;
                            } else if (s[0] == 'e') {
                                moveFrom.col = 4;
                            } else if (s[0] == 'f') {
                                moveFrom.col = 5;
                            } else if (s[0] == 'g') {
                                moveFrom.col = 6;
                            } else if (s[0] == 'h') {
                                moveFrom.col = 7;
                            } else {
                                cout << "Please enter a column from a to h" << endl;
                                continue;
                            }
                            //get row:
                            if (s[1] == '1') {
                                moveFrom.row = 0;
                            } else if (s[1] == '2') {
                                moveFrom.row = 1;
                            } else if (s[1] == '3') {
                                moveFrom.row = 2;
                            } else if (s[1] == '4') {
                                moveFrom.row = 3;
                            } else if (s[1] == '5') {
                                moveFrom.row = 4;
                            } else if (s[1] == '6') {
                                moveFrom.row = 5;
                            } else if (s[1] == '7') {
                                moveFrom.row = 6;
                            } else if (s[1] == '8') {
                                moveFrom.row = 7;
                            } else {
                                cout << "Please enter a row number from 1 to 8" << endl;
                                continue;
                            }
                        } else {
                            cout << "Please enter correct move a-h + 1-8" << endl;
                            continue;
                        }
                    } else {
                        break; //if encounter EOF
                    }
                    //getting moveTo
                    if (cin >> s) {
                        if(s.length() == 2) {
                            //get col:
                            if (s[0] == 'a') {
                                moveTo.col = 0;
                            } else if (s[0] == 'b') {
                                moveTo.col = 1;
                            } else if (s[0] == 'c') {
                                moveTo.col = 2;
                            } else if (s[0] == 'd') {
                                moveTo.col = 3;
                            } else if (s[0] == 'e') {
                                moveTo.col = 4;
                            } else if (s[0] == 'f') {
                                moveTo.col = 5;
                            } else if (s[0] == 'g') {
                                moveTo.col = 6;
                            } else if (s[0] == 'h') {
                                moveTo.col = 7;
                            } else {
                                cout << "Please enter a column from a to h" << endl;
                                continue;
                            }
                            //get row:
                            if (s[1] == '1') {
                                moveTo.row = 0;
                            } else if (s[1] == '2') {
                                moveTo.row = 1;
                            } else if (s[1] == '3') {
                                moveTo.row = 2;
                            } else if (s[1] == '4') {
                                moveTo.row = 3;
                            } else if (s[1] == '5') {
                                moveTo.row = 4;
                            } else if (s[1] == '6') {
                                moveTo.row = 5;
                            } else if (s[1] == '7') {
                                moveTo.row = 6;
                            } else if (s[1] == '8') {
                                moveTo.row = 7;
                            } else {
                                cout << "Please enter a row number from 1 to 8" << endl;
                                continue;
                            }
                        } else {
                            cout << "Please enter correct move a-h + 1-8" << endl;
                            continue;
                        }
                    } else {
                        break; //if encounter EOF
                    }
                    if (!blackPlayer->movePiece(moveFrom, moveTo)) {
                        cout << "move unsuccessful :(" << endl;
                        cout << b;
                    } else {
                        cout << b;
                        isWhiteMove = true;
                    }
                } else {//black computer is making a move
                    if (!blackPlayer->moveComputer()) {
                        cout << "move unsuccessful :(" << endl;
                        cout << b;
                        ////throw and catch???
                    } else {
                        cout << b;
                        isWhiteMove = true;
                    }
                }
            }
        } else if (s == "setup") {
            if (isPlaying) {
                cout << "There is an ongoing game, please set-up before a game starts." << endl;
            } else {
                bool endOfFile = false;
                //king not in check
                b.setUpGraphic();
                cout << b;
                cout << "Set up your custom board" << endl;
                while (cin >> s) {
                    if (s == "+") {
                        string pieceType;
                        string piecePoint;
                        Point setPoint;
                        //getting piecetype
                        if (cin >> pieceType) {
                            if (!((pieceType == "k")||(pieceType =="q")||
                                  (pieceType == "b")||(pieceType == "r")||
                                  (pieceType == "n")||(pieceType == "p")||
                                  (pieceType == "K")||(pieceType == "Q")||
                                  (pieceType == "B")||(pieceType == "R")||
                                  (pieceType == "N")||(pieceType == "P"))) {
                                cout << "Please enter a valid piece type." << endl;
                                continue;
                            }
                        } else {
                            endOfFile = true;
                            break;
                        }
                        //getting piecepoint
                        if (cin >> piecePoint) {
                            if(piecePoint.length() == 2) {
                                //get col:
                                if (piecePoint[0] == 'a') {
                                    setPoint.col = 0;
                                } else if (piecePoint[0] == 'b') {
                                    setPoint.col = 1;
                                } else if (piecePoint[0] == 'c') {
                                    setPoint.col = 2;
                                } else if (piecePoint[0] == 'd') {
                                    setPoint.col = 3;
                                } else if (piecePoint[0] == 'e') {
                                    setPoint.col = 4;
                                } else if (piecePoint[0] == 'f') {
                                    setPoint.col = 5;
                                } else if (piecePoint[0] == 'g') {
                                    setPoint.col = 6;
                                } else if (piecePoint[0] == 'h') {
                                    setPoint.col = 7;
                                } else {
                                    cout << "Please enter a column from a to h" << endl;
                                    continue;
                                }
                                //get row:
                                if (piecePoint[1] == '1') {
                                    setPoint.row = 0;
                                } else if (piecePoint[1] == '2') {
                                    setPoint.row = 1;
                                } else if (piecePoint[1] == '3') {
                                    setPoint.row = 2;
                                } else if (piecePoint[1] == '4') {
                                    setPoint.row = 3;
                                } else if (piecePoint[1] == '5') {
                                    setPoint.row = 4;
                                } else if (piecePoint[1] == '6') {
                                    setPoint.row = 5;
                                } else if (piecePoint[1] == '7') {
                                    setPoint.row = 6;
                                } else if (piecePoint[1] == '8') {
                                    setPoint.row = 7;
                                } else {
                                    cout << "Please enter a row number from 1 to 8" << endl;
                                    continue;
                                }
                                
                                if (pieceType == "P" || pieceType == "p") {
                                    if (setPoint.row == 0 || setPoint.row == 7) {
                                        cout << "No pawns on the first or last row of the borad." << endl;
                                        continue;
                                    }
                                }
                                //now we've ensured all the inputs are valid, set a new piece:
                                b.addPiece(pieceType, setPoint);
                                cout << b;
                            } else {
                                cout << "Please enter a valid position to set a new piece." << endl;
                                continue;
                            }
                        } else {
                            endOfFile = true;
                            break;
                        }
                    } else if (s == "-") {
                        string piecePoint;
                        Point setPoint;
                        //getting piecepoint
                        if (cin >> piecePoint) {
                            if(piecePoint.length() == 2) {
                                //get col:
                                if (piecePoint[0] == 'a') {
                                    setPoint.col = 0;
                                } else if (piecePoint[0] == 'b') {
                                    setPoint.col = 1;
                                } else if (piecePoint[0] == 'c') {
                                    setPoint.col = 2;
                                } else if (piecePoint[0] == 'd') {
                                    setPoint.col = 3;
                                } else if (piecePoint[0] == 'e') {
                                    setPoint.col = 4;
                                } else if (piecePoint[0] == 'f') {
                                    setPoint.col = 5;
                                } else if (piecePoint[0] == 'g') {
                                    setPoint.col = 6;
                                } else if (piecePoint[0] == 'h') {
                                    setPoint.col = 7;
                                } else {
                                    cout << "Please enter a column from a to h" << endl;
                                    continue;
                                }
                                //get row:
                                if (piecePoint[1] == '1') {
                                    setPoint.row = 0;
                                } else if (piecePoint[1] == '2') {
                                    setPoint.row = 1;
                                } else if (piecePoint[1] == '3') {
                                    setPoint.row = 2;
                                } else if (piecePoint[1] == '4') {
                                    setPoint.row = 3;
                                } else if (piecePoint[1] == '5') {
                                    setPoint.row = 4;
                                } else if (piecePoint[1] == '6') {
                                    setPoint.row = 5;
                                } else if (piecePoint[1] == '7') {
                                    setPoint.row = 6;
                                } else if (piecePoint[1] == '8') {
                                    setPoint.row = 7;
                                } else {
                                    cout << "Please enter a row number from 1 to 8" << endl;
                                    continue;
                                }
                                //now we've ensured all the inputs are valid, remove a new piece:
                                b.removePiece(setPoint);
                                cout << b;
                            } else {
                                cout << "Please enter a valid position to remove a piece." << endl;
                                continue;
                            }
                        } else {
                            endOfFile = true;
                            break;
                        }
                    } else if (s == "=") {
                        if (cin >> s) {
                            if(s == "black") {
                                isWhiteMove = false;
                            } else if (s == "white") {
                                isWhiteMove = true;
                            } else {
                                cout << "Please enter a color black/white." << endl;
                                continue;
                            }
                        } else {//if EOF
                            endOfFile = true;
                            break;
                        }
                    } else if (s == "done") {
                        if (b.oneBlackKing() && b.oneWhiteKing()) {
                            if(b.isCheck(Colour::Black) || b.isCheck(Colour::White)) {
                                cout << "You must not leave the King in check before leaving the set-up mode." << endl;
                                continue;
                            } else {
                                setUp = true;
                                break; //leave set-up mode
                            }
                        } else {
                            cout << "You must have one black King and one white King before leaving the set-up mode." << endl;
                            continue;
                        }
                    } else {
                        cout << "Please enter a valid command for set-up." << endl;
                    }
                }
                if (endOfFile) {
                    break; //break out of the larger loop.
                }
                
            }
            
        } else { //command is neither resign, move, setup, game
            cout << "please enter a valid command: game/resign/move/setup" << endl;
        }
        // Check for end games
        if (isPlaying) {
                if (blackPlayer->isCheck()) {
                    cout << "Black is in Check" << endl;
                    if (blackPlayer->isCheckmate()) {
                        cout << "Checkmate! White wins!" << endl;
                        whiteWins += 1;
                        //destroy the current game
                        delete whitePlayer;
                        delete blackPlayer;
                        whitePlayer = nullptr;
                        blackPlayer = nullptr;
                        b.reset();
                        isPlaying = false;
                        setUp = false;
                        isWhiteMove = true;
                    }
                } else if (whitePlayer->isCheck()) {
                    cout << "White is in Check" << endl;
                    if (whitePlayer->isCheckmate()) {
                        cout << "Checkmate! Black wins!" << endl;
                        blackWins += 1;
                        //destroy the current game
                        delete whitePlayer;
                        delete blackPlayer;
                        whitePlayer = nullptr;
                        blackPlayer = nullptr;
                        b.reset();
                        isPlaying = false;
                        setUp = false;
                        isWhiteMove = true;
                    }
                } else if (b.isStalemate()) {
                    whiteWins += 0.5;
                    blackWins += 0.5;
                    //destroy the current game
                    delete whitePlayer;
                    delete blackPlayer;
                    whitePlayer = nullptr;
                    blackPlayer = nullptr;
                    b.reset();
                    isPlaying = false;
                    setUp = false;
                    isWhiteMove = true;
                }
        }
        // End of while loop
    }
    delete whitePlayer;
    delete blackPlayer;
    cout << "Final Score:" << endl;
    cout << "White: " << whiteWins << endl;
    cout << "Black: " << blackWins << endl;
    
}


