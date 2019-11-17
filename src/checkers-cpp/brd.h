//
//  brd.hpp
//  tiber
//
//  Created by Yubin Sun on 11/6/19.
//  Copyright © 2019 Yubin Sun. All rights reserved.
//

#ifndef brd_hpp
#define brd_hpp

#include <iostream>


struct point{
    int x;
    int y;
    int color;
};

class _move{
public:
    point points[10];
    int length;
    bool kill;
    
    _move();
    _move(int x, int y, bool k,int color);
    int add(int x, int y, bool k, int color);
    _move & operator=(const _move & m);
    std::string toString() const;
    friend std::ostream & operator << (std::ostream&os, const _move & m);
};

class brd{
public:
    int col,row, p;
    
    // state block
    int** board; // 2D dynamic allocation. 
    int blackCount,whiteCount;
    
    
    brd();
    brd(int c, int r, int pieces);
    void initializeGame();
    bool isInBoard(int x, int y);
    
    bool valid_one_kill(int r, int c, int rn, int cn,int color);
    bool whether_become_king(int r, int c, int p);
    int find_kill_moves(int player, _move * moves, int& count);
    int find_kill_move(int x, int y, int player, int color, _move* moves, int& count, int level);
    int make_moves(const _move & m);
    
    void showBoard();
    
    
    
    // these functions are for testing purpose
    int put(int x, int y, int c); //
    // put color[0,-1,-2,1,2] on [x][y]. x,y must be inboud, function does not check.
    // it WILL overwrite the old one.
};




#endif /* brd_hpp */
