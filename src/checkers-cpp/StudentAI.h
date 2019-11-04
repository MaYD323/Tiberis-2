#ifndef STUDENTAI_H
#define STUDENTAI_H
#include "AI.h"
#include "Board.h"
#include <string>
#include <vector>
//#include "Move.h"
#pragma once

//The following part should be completed by students.
//Students can modify anything except the class name and exisiting functions and varibles.
class StudentAI :public AI
{
public:
    bool ai_start;
    int opponent; // int player in ai.h
    int move_count;
    vector<int> possible_moves_counts; // for analysis branch factor
    Board board;
	StudentAI(int col, int row, int p);
	virtual Move GetMove(Move board);
    int h(int p);
    int minmax(vector<Move> m, bool max, int d);
};


#endif //STUDENTAI_H
