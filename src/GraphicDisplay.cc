//
//  graphicsDisplay.cpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-29.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#include "GraphicDisplay.h"
#include "window.h"
using namespace std;

void GraphicDisplay::initialize () {
    xw->fillRectangle(0, 0, 520, 520, 8);
    for (int i = 0 ; i <= 7 ; ++i) {
        if (i%2 == 0 ) {
            for (int j = 0 ; j <= 6; j+=2) {
                xw->fillRectangle(65*j, 65*i, 65, 65, 9);
            }
        } else {
            for (int j = 1 ; j <= 7; j+=2) {
                xw->fillRectangle(65*j, 65*i, 65, 65, 9);
            }
        }
    }
}


void GraphicDisplay::notify(int row, int col, Colour colour, string type) {
    if (row == 0) {
        row = 7;
    } else if (row == 1) {
        row = 6;
    } else if (row == 2) {
        row = 5;
    } else if (row == 3) {
        row = 4;
    } else if (row == 4) {
        row = 3;
    } else if (row == 5) {
        row = 2;
    } else if (row == 6) {
        row = 1;
    } else if (row == 7) {
        row = 0;
    }
    if (type == "empty") {
        if (colour == Colour::White) {
            xw->fillRectangle(65*col, 65*row, 65, 65, 8);
        } else {
            xw->fillRectangle(65*col, 65*row, 65, 65, 9);
        }
    } else {
        if (colour == Colour::White) {
            xw->drawBigString(col*65+20, row*65+45, type, Xwindow::White);
        } else {
            xw->drawBigString(col*65+20, row*65+45, type, Xwindow::Black);
        }
    }
}

GraphicDisplay::GraphicDisplay(Xwindow *xw): xw{xw} {}

GraphicDisplay::~GraphicDisplay() {
    delete xw;
}
