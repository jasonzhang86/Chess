//
//  graphicsDisplay.hpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-29.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#ifndef GRAPHICDISPLAY_H
#define GRAPHICDISPLAY_H
#include "enum.h"
#include <string>

class Xwindow;
class GraphicDisplay {
    Xwindow *xw = nullptr;
public:
    void initialize ();
    void notify (int row, int col, Colour colour, std::string type);
    GraphicDisplay(Xwindow *xw);
    ~GraphicDisplay();
};

#endif
 /* graphicsDisplay_hpp */
