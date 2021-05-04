//
//  TextDisplay.cpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-23.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#include "textDisplay.h"

void TextDisplay::nofity(int row, int col, char symbol) {
    theDisplay[row][col] = symbol;
}

TextDisplay::TextDisplay() {
    theDisplay.resize(boardSize, std::vector<char>(boardSize, ' '));
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if ((i+j)%2 == 0) {
                theDisplay[i][j] = '_';
            }
        }
    }
}

TextDisplay::~TextDisplay() {}

std::ostream & operator<<(std::ostream &out, const TextDisplay &td) {
    for (int i = boardSize - 1; i >= 0; i--) {
        out << i+1 << " ";
        for (int j = 0; j < boardSize; j++) {
            out << td.theDisplay[i][j];
        }
        out << '\n';
    }
    out << '\n';
    out << "  abcdefgh" << std::endl;
    return out;
}
