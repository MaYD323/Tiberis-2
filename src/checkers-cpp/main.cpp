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

int main(int argc, char *argv[])
{
    cout << sizeof(brd);
    return 0;
    GameLogic main(8,8,2, "m", 1);
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



