//#include "GameLogic.h"

#include "GameLogic.h"

#include "StudentAI.h"


int main(int argc, char *argv[])
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

