#include "StudentAI.h"
#include <random>
#include <iostream>
#include <vector>
using namespace std;
StudentAI::StudentAI(int col,int row,int p)
	:AI(col, row, p)
{
    ai_start = false;
    move_count = 0;
    
    board = Board(col,row,p);
    board.initializeGame();
    player = 2;
}

Move StudentAI::GetMove(Move move)
{
    //cout << "AI::MOVE input " << move.seq.size()<< endl;
    if(move_count == 0){
        if(move.seq.size()== 0){
            ai_start = true;
            player = 1;
            opponent = 2;
        }else{
            player = 2;
            opponent = 1;
            board.makeMove(move,opponent);

        }
    }else{
        board.makeMove(move, opponent);
    }

    /* emitted for shell testing */ //cout << h(player) << endl;
    vector<vector<Move>> moves;
    
//    moves = board.getAllPossibleMoves(opponent);
//    for (auto i : moves){
//        for (auto j : i){
//            cout << j.toString();
//        }
//    }
//    cout << endl;
//    board.makeMove(moves[0][0], opponent);
//    board.showBoard();
    //
    moves = board.getAllPossibleMoves(player);
    // count possible moves.
    int counter = 0;
    for (auto i : moves){
        for (auto j : i){
            counter ++;
        }
    }
    possible_moves_counts.push_back(counter);
    //cout << "AI count poss moves " << counter << endl;

    //
    
    /*
    int i = rand() % (moves.size());
    vector<Move> checker_moves = moves[i];
    int j = rand() % (checker_moves.size());
    */
    
    
    
    /* emitted for shell testing */ //cout << "--------TEST MINXMAX---------" << endl;
    vector<Move> vm;
    int t;
    int v = -9999;
    Move mv;
    for (auto i : moves){
        for (auto j : i){
            vm.clear();
            vm.push_back(j);
            t = minmax(vm, true, 6);
            if(t > v){
                v = t;
                mv = j;
            }
            /* emitted for shell testing */ // cout << "AI : test move : " << j.toString()<< "minmax value : " <<t << endl;
        }
    }
    //vm.push_back(moves[0][0]);
    
    //cout << "minmax value : " <<minmax(vm, true, 5) << endl;
    
    
    // finialiing
    Move res = mv;//moves[0][0];
    /* emitted for shell testing */ //cout << res.toString() << endl;
    board.makeMove(res,player);
    move_count++;
    if(move_count > -1){
        /* emitted for shell testing */ //cout << "AI: Depth : " << move_count << " Branch Factor::" <<counter << endl;
    }
    /* emitted for shell testing */ //cout << "----------END AI ------------" << endl;
    return res;


}

int StudentAI::h(int p){
    if(p == 1){
        return this->board.blackCount - this->board.whiteCount;
    }else{
        return this->board.whiteCount - this->board.blackCount;
    }
}

int StudentAI::minmax(vector<Move> m, bool max, int d){
    if(d == 0 || m.size() == 0){
        return h(player);
    }
    int v;
    int t;
    Move chosen_move;
    vector<vector<Move>> possible_moves;
    vector<Move> possivle_moves_1d;
    if(max){
        v = -9999;
        for(auto i : m){
            possible_moves.clear();
            possivle_moves_1d.clear();
            
            board.makeMove(i, player);
            possible_moves = board.getAllPossibleMoves(opponent);
            // convert 2d vector to 1d vector
            for( auto l1 : possible_moves ){
                for(auto l2 : l1){
                    possivle_moves_1d.push_back(l2);
                }
            }
            
            t = minmax(possivle_moves_1d, !max, d-1);
            if(t > v){
                v = t;
                chosen_move = i;
            }
            board.Undo();
        }
        return v;
    }else{
        v = 9999;
        for(auto i : m){
            possible_moves.clear();
            possivle_moves_1d.clear();
            
            board.makeMove(i, opponent);
            possible_moves = board.getAllPossibleMoves(player);
            // convert 2d vector to 1d vector
            for( auto l1 : possible_moves ){
                for(auto l2 : l1){
                    possivle_moves_1d.push_back(l2);
                }
            }
            
            t = minmax(possivle_moves_1d, !max, d-1);
            if(t < v){
                v = t;
                chosen_move = i;
            }
            board.Undo();
        }
        return v;
    }
    
    
    return v;
}


// some util functions
