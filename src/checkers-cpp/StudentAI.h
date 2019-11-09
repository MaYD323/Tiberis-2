#ifndef STUDENTAI_H
#define STUDENTAI_H
#include "AI.h"
#include "Board.h"
#include <string>
#include <vector>
#include <fstream>

//#include "Move.h"
#pragma once

//The following part should be completed by students.
//Students can modify anything except the class name and exisiting functions and varibles.
class StudentAI :public AI
{
public:
    bool ai_start;
    int opponent; // int player in ai.h
    double total_time;
    time_t start;
    time_t end;
    double measure_time();
    
    vector<double> time_count;
    int move_count; // depth
    vector<int> possible_moves_counts; // for analysis branch factor
    
    Board board;
	StudentAI(int col, int row, int p);
    ~StudentAI();
	virtual Move GetMove(Move board);
    int h(int p);
    int minmax(vector<Move> m, bool max, int d);
};


class logger{
public:
    string name, path;
    string log_data;
    string filename;
    bool online;
    std::fstream fs;
    
    
    logger(string name , string path = "", string ip = "");
    ~logger();
    
    int log(string c, string end = "\n");
    int upload(string c); // empty now
    int write(string c);
    
    
    
    
};
#endif //STUDENTAI_H
