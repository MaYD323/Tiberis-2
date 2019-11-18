//
//  brd.cpp
//  tiber
//
//  Created by Yubin Sun on 11/6/19.
//  Copyright © 2019 Yubin Sun. All rights reserved.
//

//#define P1 1
//#define P2 2
//#define b  1
//#define B  2
//#define w  -1
//#define W  -2

#include "brd.h"
#include <stdio.h>

using namespace std;

#include <sstream>


_move::_move(){
    length = 0;
    kill = 0;
}
_move::_move(int x, int y, bool k, int color){
    points[0] = point{x,y,color};
    length = 1;
    kill = k;
}
int _move::add(int x, int y, bool k, int color){
    switch (length) {
        case 9:
            throw "did not expect > 10" ;
            break;
        case 0:
            points[length] = point{x,y,color};
            length++;
            kill = k;
            break;
        default:
            if(kill == k){
                points[length++] = point{x,y,color};
            }else{
                throw "error: kill para not match";
            }
            break;
    }

    
    return length;
}
_move & _move::operator=(const _move & m){
    kill = m.kill;
    length = m.length;
    for (int i = 0; i < length; i++){
        points[i] = m.points[i];
    }
    return *this;
}
string _move::toString() const{
    if(length == 0){
        return string("");
    }
    std::ostringstream ss;
    switch (kill) {
        case true:
            ss << "Kill : (" <<  points[0].x << "," << points[0].y << ") ";
            for(int i = 1; i < length; i++){
                ss << "-> ("<<  points[i].x << "," << points[i].y << ") " ;
            }
            break;
            
        default:
            ss << "Kill : (" <<  points[0].x << "," << points[0].y << ") ";
            for(int i = 1; i < length; i++){
                ss << "-> ("<<  points[i].x << "," << points[i].y << ") " ;
            }
            break;
    }
    return ss.str();
}
ostream & operator << (ostream&os, const _move & m){

    if(m.length == 0){
        os << "";
        return os;
    }
    switch (m.kill) {
        case true:
            os << "Kill : (" << m.points[0].x << "," << m.points[0].y << ") ";
            for(int i = 1; i < m.length; i++){
                os << "-> ("<<  m.points[i].x << "," << m.points[i].y << ") " ;
            }
            break;

        default:
            os << "Kill : (" <<  m.points[0].x << "," << m.points[0].y << ") ";
            for(int i = 1; i < m.length; i++){
                os << "-> ("<<  m.points[i].x << "," << m.points[i].y << ") " ;
            }
            break;
    }
    return os;
}

brd::brd(){
    col = 0;
    row = 0;
    p = 0;
}

brd::brd(int c, int r, int pieces){
    col = c;
    row = r;
    p = pieces;
    board = new int*[row];
    for (int i = 0; i < row; i++){
        board[i] = new int[col];
    }
    
    initializeGame();


}


void brd::initializeGame(){
    if(row - 2 * p <= 0 || col * p % 2 != 0){
        throw;
    }
    
    
 
    
    int space= 0;
    int r = 0;
    for (r; r < p; r++){
        for(int c = 0; c< col; c++){
            board[r][c] = (c%2 == space? 1 : 0);
            blackCount += (c%2 == space? 1 : 0);
        }
        space = (space+1)%2;
    }
    for(r; r < (row - p ) ; r++ ){
        for(int c = 0; c< col; c++){
            board[r][c] = 0;
        }
        space = (space+1)%2;
    }
    
    for(r; r < row; r++ ){
        for(int c = 0; c< col; c++){
            board[r][c] = (c%2 == space? -1 : 0);
            whiteCount += (c%2 == space? 1 : 0);
        }
        space = (space+1)%2;
    }
    
}
bool brd::isInBoard(int x, int y){
    if(x >= 0 && x < row && y >= 0 && y < col){
        return true;
    }
    return false;
}
bool brd::valid_one_kill(int r, int c, int rn, int cn,int color){
    if(isInBoard(r, c) && isInBoard(rn, cn)){
        if(board[rn][cn] == 0 && board[(r+rn)/2][(c+cn)/2] * color < 0)
        {
            return true;
        }
    }
    return false;
}


bool brd::whether_become_king(int r, int c, int p){
    switch (p) {
        case 1:
            if(r == 0){
                return true;
            }
            break;
        case -1:
            if(r == r-1){
                return true;
            }
            break;
        case -2:
            return true;
        case 2:
            return true;
        default:
            return false;
    }
    return false;
}
int brd::find_kill_moves(int player, _move *moves, int &count){
    
    return 0;
}
int brd::find_kill_move(int x, int y, int player, int color, _move *moves, int& count, int level){
     // new color
    int case_count = 0; // count how many moves found in this level;
    int k = color; // color in subcase
    int dx,dy = 0;
    int pc = player + player;
    _move tmp_move = moves[count];
head:
    switch (pc) {
        case 4:
            dx =-2; dy = -2; goto sub; //
        case 3:
            dx = -2; dy = 2; goto sub;
        case 2:
            dx = 2; dy = -2; goto sub;
        case 1:
            dx = 2 ; dy = 2; goto sub;
            break;
            
        case -4:
            dx = 2 ; dy = -2; goto sub;
        case -3:
            dx = 2; dy = 2; goto sub;
        case -2:
            dx = -2; dy = -2; goto sub;
        case -1:
            dx = -2 ; dy = 2; goto sub;
    }
    return count;
    
    
    
sub:
    if(valid_one_kill(x, y, x+dx, y+dy,color)){
        k *= whether_become_king(x+dx, y+dy, color)?2:1;
        if(level == 0){
            moves[count].add(x, y, true, color);
            moves[count].add(x+dx, y+dy,true, k);
        }else if(case_count == 0){
            moves[count].add(x+dx, y+dy,true, k);
        }else{
            // child case, and not first hit
            moves[count+1] = moves[count];
            moves[count+1].add(x+dx, y+dy,true, k);
            count ++;
        }
        find_kill_move(x+dx, y+dy, player, k, moves, count, level+1);
        if(level == 0){
            count ++;
        }
        case_count++;
    }
    
    pc>0?pc--:pc++;
    goto head;
}
 
int brd::make_moves(const _move &m){
    // maybe necessary to check validity
    switch (m.kill) {
        case false:
            // move one step
            // in this case, there is only one move
            // check validity (sort of)
            if(board[(m.points[1].x)][(m.points[1].y)] != 0 ){
                throw "invalid move";
            }
            if(board[(m.points[0].x)][(m.points[0].y)] == 0){
                throw "invalid move";
            }
            board[(m.points[1].x)][(m.points[1].x)] = m.points[1].color;
            board[(m.points[0].x)][(m.points[0].x)] = 0;
            break;
        case true:
            // pass checking validity
            for(int i = 0; i < m.length -1; i++){
                board[(m.points[i+1].x)][(m.points[i+1].x)] = m.points[i+1].color;
                board[(m.points[i].x)][(m.points[i].x)] = 0;
                board[(m.points[i].x + m.points[i+1].x)/2][(m.points[i].x + m.points[i+1].x)/2] = 0;
            }
        default:
            break;
    }
    
    return m.length;
}

void brd::showBoard(){
    printf("\t ");
    for(int i = 0; i < col; i++){
        printf("%2d\t",i);

    }
    cout << "\n   ----";

    for(int i = 0; i < col-1; i++){
        cout << "----";

    }
    cout << endl;
    for (int i = 0; i < row; i++){
        cout << i<<" | ";
        for(int j = 0; j < col; j++){
            //cout << board[i][j] << "\t" ;
            printf("%2d\t", board[i][j]);
        }
        cout << endl;
    }
    
    for(int i = 0; i < col; i++){
        cout << "----";

    }
    cout << endl;
    return;
}


int brd::put(int x, int y, int c){
    board[x][y] = c;
    return board[x][y];
}
