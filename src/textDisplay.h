//
//  TextDisplay.hpp
//  A5 Chess
//
//  Created by Jason Zhang on 2019-07-23.
//  Copyright © 2019 Jason Zhang. All rights reserved.
//

#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <iostream>
#include <vector>

const int boardSize = 8;

class TextDisplay {
    std::vector<std::vector<char>> theDisplay;
    
public:
    void nofity(int row, int col, char symbol);
    TextDisplay();
    ~TextDisplay();
    friend std::ostream & operator<<(std::ostream &out, const TextDisplay &td);
};

#endif /* TextDisplay_hpp */
