//#include "GameLogic.h"

#include "GameLogic.h"


#include "brd.h"
#include "StudentAI.h"
//int main11(){
//    logger l("l1");
//    l.log("line1");
//    l.log("line2");
//    return 0;
//}
//
//int main1(){
//    brd a(5,5,5);
//    a.showBoard();
//
//
//
//
//
//    return 0;
//}
int player = 1;
int opponent  = 2;
int myplayer = 1;
int myopponent = -1;
int boardminmax(vector<Move> m, bool max, int d,Board & board);
int test_board();
int myboardminmax(_move * ms, int length, bool max, int d, brd * nb );
int test_myboard();
int main(){
    test_board();
    //test_myboard();
    return 0;
}

int boardminmax(vector<Move> m, bool max, int d,Board & board){
    if(d == 0 || m.size() == 0){
        return 1;
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
            
            t = boardminmax(possivle_moves_1d, !max, d-1,board);
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
            
            t = boardminmax(possivle_moves_1d, !max, d-1,board);
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
int test_board(){
    int total; //= 1 << 20;// 1M
    total = 10;
    for(int i = 0; i < total; i++){
        Board b(7, 7, 2);
        b.initializeGame();
        vector<vector<Move>> moves = b.getAllPossibleMoves(player);
        
        
        vector<Move> vm;
        int t;
        int v = -9999;
        Move mv;
        for (auto i : moves){
            for (auto j : i){
                vm.clear();
                vm.push_back(j);
                t = boardminmax(vm, true, 8,b);
                cout << j.toString() << " :: " << t << endl;
                if(t > v){
                    v = t;
                    mv = j;
                }
            }
        }
    }
    return 0;
}
int myboardminmax(_move * ms, int length, bool max, int d, brd * nb ) {
    if(d == 0 || length == 0){
        return 1;
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
            t = myboardminmax(new_ms, count, !max, d-1,&newbrd);
            if(t > v){
                v = t;
                chosen_move = ms[i];
            }
            delete[] new_ms;
        }
        return v;
    }else{
        
        v = 9999;
        for(int i = 0; i < length; i++){
            count = 0;
            new_ms = new _move[20];
            brd newbrd(*nb);
            newbrd.make_moves(ms[i]);
            newbrd.find_peace_moves(myplayer, new_ms, count);
            if(count == 0){
                newbrd.find_kill_moves(myplayer, new_ms, count);
            }
            t = myboardminmax(new_ms, count, !max, d-1,&newbrd);
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
int test_myboard(){
    int total = 10;
    for(int c = 0; c < total; c++){
        
        brd b(7,7,2);
        _move * mvs = new _move[20];
        int count = 0;
        b.find_peace_moves(myplayer, mvs, count);
        if(count == 0){
            b.find_kill_moves(myplayer, mvs, count);
        }
        
        int t;
        int v = -9999;
        _move mymv;
        for(int i = 0; i < count; i++){
            t = myboardminmax(mvs, count, true, 8,&b);
            cout << "minmax value : " <<t << "move ::" << mvs[i] << endl;
            if(t > v){
                v = t;
                mymv = mvs[i];
            }
        }
    }
    return 0;
}
int maink(int argc, char *argv[])
{
    
    GameLogic main(7,7,2, "m", 1);
    main.Run();
    return 0;
    
	if (argc < 5)
	{
		cout << "Invalid Parameters" << endl;
		//return 0;
	}
	//mode="m"->manual/"t"->tournament
    int col = atoi(argv[1]);
    int row = atoi(argv[2]);
    int p = atoi(argv[3]);
    string mode = argv[4];
	int order = 0;
    if (mode == "m" or mode == "manual")
    {
        order = atoi(argv[5]);
    }
//    GameLogic main(col,row,p, mode, order);//col,row,p,g,mode,debug
//	main.Run();

	return 0;
}


int main00(){

    
    
    
    
    Board a(7, 7, 2);
    //a.initializeGame();
    a.board[4][0] = Checker("B",4,0);
//    a.board[5][1] = Checker("W",5,1);
    a.board[5][3] = Checker("W",5,1);
    a.blackCount++;
    a.whiteCount=2;
    a.showBoard();

    vector<vector<Move>> moves = a.getAllPossibleMoves("B");
    for (auto i : moves){
        for (auto j : i){
            cout << j.toString() << endl;
        }
    }
    brd d(7,7, 2);
    for(int i =0; i < 7; i ++){
        for(int j = 0; j < 7; j++){
            d.put(i,j,0);
        }
    }
    d.put(4, 0, 1);
//    d.put(5, 1, -1);
    d.put(5,3,-1);
    _move am(moves[0][0],&d);
    cout << am << endl;
    
    return 0;
//
//    int c = 0;
//    for (auto i : moves){
//        for (auto j : i){
//            c++;
//            cout << j.toString() << endl;
//            a.makeMove(j, 1);
//        }
//    }
//    cout << c << endl;
//    a.showBoard();
//
//    moves = a.getAllPossibleMoves("B");

//    for (auto i : moves){
//        for (auto j : i){
//            c++;
//            cout << j.toString() << endl;
//        }
//    }
//
    
    
    
    for(int i =0; i < 7; i ++){
        for(int j = 0; j < 7; j++){
            d.put(i,j,0);
        }
    }
//    d.showBoard();
    d.put(3, 5, -1);
    d.put(2,2,2);
    d.put(3,3,-1);
    d.put(4,0,0);
    d.put(5,1,-1);
    d.put(5,3,-1);
    d.put(2,4,2);
//    d.showBoard();
    _move * ms = new _move[30];
    int count = 0;
    int k;
    k = d.find_peace_moves(1, ms, count);

//    _move m(6,6,true,-1);
//    m.add(4, 4, true, -1);
//    d.make_moves(m);
//    d.showBoard();
//
//    _move mm;
//    mm.add(4, 4, false, -1);
//    mm.add(3, 3, false, -1);
//    d.showBoard();
//    d.showBoard();
//    cout << k << endl;
    for(int i = 0; i < k; i++){
        cout << i<<ms[i] << endl;
    }
    delete[]ms;
    return 0;
}



