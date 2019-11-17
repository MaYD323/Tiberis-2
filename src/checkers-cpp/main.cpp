//#include "GameLogic.h"

#include "GameLogic.h"


#include "brd.h"
#include "StudentAI.h"
int main11(){
    logger l("l1");
    l.log("line1");
    l.log("line2");
    return 0;
}

int main1(){
    brd a(5,5,5);
    a.showBoard();
    
    
    
    
    
    return 0;
}

int main2(int argc, char *argv[])
{
//    GameLogic main(7,7,2, "m", 1);
//    main.Run();
//    return 0;
    
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
    GameLogic main(col,row,p, mode, order);//col,row,p,g,mode,debug
	main.Run();

	return 0;
}


int main(){
    Board a(7, 7, 2);
    a.initializeGame();
    a.board[2][2] = Checker("W",2,3);
    a.showBoard();
    

    
    
    
    brd d(7, 7, 2);

    
    d.showBoard();
    _move * ms = new _move[10];
    int count = 0;
    int k;
    // k = d.find_kill_move(1, 3, 1, 1, ms, count, 0);
    
//    _move m(6,6,true,-1);
//    m.add(4, 4, true, -1);
//    d.make_moves(m);
//    d.showBoard();
//
//    _move mm;
//    mm.add(4, 4, false, -1);
//    mm.add(3, 3, false, -1);
//    d.make_moves(mm);
//    d.showBoard();
    for(int i = 0; i < k; i++){
        cout << ms[i] << endl;
    }
    delete[]ms;
    return 0;
}



