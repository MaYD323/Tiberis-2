//
//  brd.cpp
//  tiber
//
//  Created by Yubin Sun on 11/6/19.
//  Copyright © 2019 Yubin Sun. All rights reserved.
//

#include "brd.h"
#include <iostream>
using namespace std;
brd::brd(){
    col = 0;
    row = 0;
    p = 0;
}

brd::brd(int c, int r, int pieces){
    col = c;
    row = r;
    p = pieces;
    board = new int*[col];
    for (int i = 0; i < col; i++){
        board[i] = new int[row];
    }
    int k = 0;
    for (int i = 0; i < col; i++){
        for(int j = 0; j < row; j++){
            board[i][j] = k++;
        }
        cout << endl;
    }
}

void brd::showBoard(){
    for (int i = 0; i < col; i++){
        for(int j = 0; j < row; j++){
            cout << board[i][j] << "-" ;
            
        }
        cout << endl;
    }
    return;
}
