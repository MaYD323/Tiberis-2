#include "StudentAI.h"
#include <random>
#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

StudentAI::StudentAI(int col,int row,int p)
	:AI(col, row, p)
{
    ai_start = false;
    move_count = 0;
    
    board = Board(col,row,p);
    board.initializeGame();
    
    StudentAI::myboard =  brd(col, row, p);
    cout << "sizeof(myboard)" << sizeof(myboard) << endl;
    cout << "sizeof(board)" << sizeof(board) << endl;

    player = 2;
}

Move StudentAI::GetMove(Move move)
{
    time(&start);
    //cout << "AI::MOVE input " << move.seq.size()<< endl;
    _move mm(move, &myboard);
    if(move_count == 0){
        if(move.seq.size()== 0){
            ai_start = true;
            player = 1;
            myplayer = 1;
            opponent = 2;
            myopponent = -1;
        }else{
            player = 2;
            myplayer = -1;
            opponent = 1;
            myopponent = 1;
            board.makeMove(move,opponent);
            myboard.make_moves(mm);
        }
    }else{
        board.makeMove(move, opponent);
        myboard.make_moves(mm);
    }
    /* emitted for shell testing */ //cout << h(player) << endl;
    vector<vector<Move>>  moves;
    cout <<mm << "\n" <<move.toString() << endl;

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
    myboard.showBoard();
    moves = board.getAllPossibleMoves(player);
    _move * mvs = new _move[20];
    int mvs_count = 0;
    int tmp = myboard.find_kill_moves(myplayer, mvs, mvs_count);
    if(mvs_count == 0){
        myboard.find_peace_moves(myplayer, mvs, mvs_count);
    }
    cout << "black count:: " << (myboard).blackCount << "\nBlack King:: " << (myboard).black_king << "\nwhite count:: " << (myboard).whiteCount << "\nWhite King::" << (myboard).white_king << endl;
    cout << "length: " << mvs_count << endl;
    for(int i = 0; i < mvs_count ; i++){
        cout << mvs[i] << endl;
    }
    int counter = 0;
    for (auto i : moves){
        for (auto j : i){
            
            for(int k = 0; k < mvs_count; k++){
                if(j.toString() == mvs[k].toString()){
                    break;
                }
                if(k < mvs_count){
                    continue;
                }
                cout << "error check find moves" <<endl;
                cout <<mvs[k].toString() << endl;
                cout << j.toString() << endl;
                throw exception();
            }
            
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
 
    //cout << "--------TEST MINXMAX---------" << endl;
    vector<Move> vm;
    int t;
    int v = -9999;
    Move mv;
    for (auto i : moves){
        for (auto j : i){
            vm.clear();
            vm.push_back(j);
            t = minmax(vm, true, 10);
            if(t > v){
                v = t;
                mv = j;
            }
            cout << "AI : test move : " << j.toString()<< "minmax value : " <<t << endl;
        }
    }
    
    _move mymv;
    for(int i = 0; i < mvs_count; i++){
        t = minmax(mvs, mvs_count, true, 7,&myboard);
        cout << "minmax value : " <<t << "move ::" << mvs[i] << endl;
        if(t > v){
            v = t;
            mymv = mvs[i];
        }
    }
    
    //vm.push_back(moves[0][0]);
    
    //cout << "minmax value : " <<minmax(vm, true, 5) << endl;
    
    
    // finialiing
    Move res = mv;//moves[0][0];
    /* emitted for shell testing */ //cout << res.toString() << endl;
    board.makeMove(res,player);
    move_count++;
    time(&end);
    measure_time();
    /* emitted for shell testing */ //cout << "AI: Depth : " << move_count << " Branch Factor::" <<counter << endl;
    cout << "----------END AI ------------" << endl;
    _move r(res, &myboard);
    myboard.make_moves(r);
    return res;


}

int StudentAI::h(int p)const{
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
int StudentAI::minmax(_move * ms, int length, bool max, int d, brd * nb ) const{
    if(d == 0 || length == 0){
        return 0;
    }
    int v;
    int t;
    _move chosen_move;
    _move * new_ms;
    int count = 0;
    
    if(max){
        v = -9999;
        for(int i = 0; i < length; i++){
            count = 0;
            new_ms = new _move[20];
            brd newbrd(*nb);
            newbrd.make_moves(ms[i]);
            newbrd.find_peace_moves(myopponent, new_ms, count);
            if(count == 0){
                newbrd.find_kill_moves(myopponent, new_ms, count);
            }
            t = minmax(new_ms, count, !max, d-1,&newbrd);
            if(t > v){
                v = t;
                chosen_move = ms[i];
            }
            delete[] new_ms;
        }
        return v;
    }else{
        
        v = -9999;
        for(int i = 0; i < length; i++){
            count = 0;
            new_ms = new _move[20];
            brd newbrd(*nb);
            newbrd.make_moves(ms[i]);
            newbrd.find_peace_moves(myplayer, new_ms, count);
            if(count == 0){
                newbrd.find_kill_moves(myplayer, new_ms, count);
            }
            t = minmax(new_ms, count, !max, d-1,&newbrd);
            if(t < v){
                v = t;
                chosen_move = ms[i];
            }
            delete[] new_ms;

        }
        return v;
    }
    return v;
}
double StudentAI::measure_time(){
    double d = difftime(end, start);
    total_time += d;
    time_count.push_back(d);
    return d;
}
StudentAI::~StudentAI(){
    for (auto i : time_count){
        cout << i << "-";
    }
    cout << endl;
    
    for (auto i : possible_moves_counts){
        cout << i << "-";
    }
    cout << endl;
}
// some util functions


// logger
logger::logger(string name, string path, string ip){
    this->name = name;
    
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    
    int i = 0;
    char buffer [80];
    char buffer1 [80];

    strftime (buffer,80,"%F-%H-%M-%S.log",timeinfo);
    while( ifstream(buffer).good()){
        strftime (buffer,80,"%F-%H-%M-%S.log",timeinfo);
        sprintf(buffer1, "-%d",i);
        strcat(buffer, buffer1);
        strcat(buffer,".log");
        i++;
    }
    this->name = name;

    strcpy(buffer1, path.c_str());
    this->path = strcat(buffer1, buffer);
    this->filename = buffer;
    fs.open(this->path, std::fstream::in | std::fstream::out | std::fstream::app);
    fs << "name : " << this->name << endl;
    log_data.append("name : ");
    log_data.append(this->name);
    log_data.append("\n");
    
}
logger::~logger(){
    fs.close();
    cout << log_data << endl;
}
int logger::log(string c, string end){
    write(c);
    write(end);
    log_data.append(c);
    log_data.append(end);
    return 0;
}
int logger::upload(string c){
    
    return 0;
}
int logger::write(string c){
    fs << c ;
    return 0;
}
