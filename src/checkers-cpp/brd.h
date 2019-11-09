//
//  brd.hpp
//  tiber
//
//  Created by Yubin Sun on 11/6/19.
//  Copyright © 2019 Yubin Sun. All rights reserved.
//

#ifndef brd_hpp
#define brd_hpp

#include <stdio.h>
class brd{
public:
    int col,row, p;
    int** board;
    
    brd();
    brd(int c, int r, int pieces);
    
    
    
    void showBoard();
    
};
#endif /* brd_hpp */
