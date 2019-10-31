from random import randint
from BoardClasses import Move
from Checker import Checker
from BoardClasses import Board
#The following part should be completed by students.
#Students can modify anything except the class name and exisiting functions and varibles.
class StudentAI():

    def __init__(self,col,row,p):
        self.col = col
        self.row = row
        self.p = p
        self.board = Board(col,row,p)
        self.board.initialize_game()
        self.color = ''
        self.opponent = {1:2,2:1}
        self.color = 2




    def get_move(self,move):
        if len(move) != 0:
            self.board.make_move(move,self.opponent[self.color])
        else:
            self.color = 1
        moves = self.board.get_all_possible_moves(self.color)
        #index_tuple = self.one_step_search(moves)
        heu, index_tuple = self.depth_iter_search(self.board,2,0,[0,0])
        print(index_tuple)
        move = moves[index_tuple[0]][index_tuple[1]]
        print(move)
        self.board.make_move(move,self.color)
        return move


    def one_step_search_heuristic(self, move):
        nb = Board(self.board.row, self.board.col,self.board.p)
        n = len(self.board.board)
        m = len(self.board.board[0])
        for i in range(n):
            for z in range(m):
                nb.board[i][z] = Checker(self.board.board[i][z].color, [self.board.board[i][z].row, self.board.board[i][z].col])
                nb.board[i][z].is_king = self.board.board[i][z].is_king
        nb.make_move(move,self.color)
        heuristic = 20
        if self.color == 2:
            heuristic -= nb.black_count
            for i in nb.board:
                for z in i:
                    if z.is_king and z.color==2:
                        heuristic+=1
        else:
            heuristic -= nb.white_count
            for i in nb.board:
                for z in i:
                    if z.is_king and z.color==1:
                        heuristic += 1
        return heuristic

    def one_step_search(self,moves):
        max_heu = -100
        outter_ini = randint(0,len(moves)-1)
        max_move_index = (outter_ini, randint(0,len(moves[outter_ini])-1))
        for i in range(len(moves)):
            for z in range(len(moves[i])):
                h = self.one_step_search_heuristic(moves[i][z])
                if h>max_heu:
                    max_heu = h
                    max_move_index = (i,z)
        return max_move_index

    def print_b(self,board):
        for i in range(len(board.board)):
            s = "row "+str(i)+": "
            for z in range(len(board.board[i])):
                s+=board.board[i][z].color
            print(s)


     #"""Still need to be coded"""

    def depth_iter_search(self, search_board, limit,d, ancester_index):

        if limit==d:
            moves = search_board.get_all_possible_moves(self.color)
            max_heu = -100
            heu = max_heu
            for i in range(len(moves)):
                for z in range(len(moves[i])):
                    heu = self.depth_iter_search_heuristic(search_board, moves[i][z])
                    if heu > max_heu:
                        max_heu = heu
            return (heu, ancester_index)
        elif d == 0:
            moves = search_board.get_all_possible_moves(self.color)
            max_heu = -100
            outter_ini = randint(0, len(moves) - 1)
            max_move_index = (outter_ini, randint(0, len(moves[outter_ini]) - 1))
            for i in range(len(moves)):
                for z in range(len(moves[i])):
                    b = self.generate_board(search_board, moves[i][z],self.color)
                    ########Gen need to be coded
                    if self.color ==2:
                        oppo_color =1
                        oppo_moves = b.get_all_possible_moves(oppo_color)
                    else:
                        oppo_color=2
                        oppo_moves = b.get_all_possible_moves(oppo_color)
                    next_stage_board = []
                    if len(oppo_moves)==0:
                        return 20, [i,z]
                    for x in range(len(oppo_moves)):
                        for y in range(len(oppo_moves[x])):
                            next_b = self.generate_board(b,oppo_moves[x][y],oppo_color)
                            next_stage_board.append(next_b)
                    for next_b in next_stage_board:
                        heu, index = self.depth_iter_search(next_b,limit,d+1,[i,z])
                        if heu > max_heu:
                            max_heu = heu
                            max_move_index = [i, z]

            return max_heu,max_move_index
        else:
            moves = search_board.get_all_possible_moves(self.color)
            if len(moves)<=0:
                return -100, ancester_index
            max_heu = -100
            outter_ini = randint(0, len(moves) - 1)
            max_move_index = (outter_ini, randint(0, len(moves[outter_ini]) - 1))
            for i in range(len(moves)):
                for z in range(len(moves[i])):
                    b = self.generate_board(search_board, moves[i][z], self.color)  ########Gen need to be coded
                    if self.color == 2:
                        oppo_color =1
                        oppo_moves = b.get_all_possible_moves(oppo_color)
                    else:
                        oppo_color =2
                        oppo_moves = b.get_all_possible_moves(oppo_color)
                    next_stage_board = []
                    if len(oppo_moves)<=0:
                        return 20,ancester_index
                    for x in range(len(oppo_moves)):
                        for y in range(len(oppo_moves[x])):
                            next_b = self.generate_board(b, oppo_moves[x][y], oppo_color)
                            next_stage_board.append(next_b)
                    for next_b in next_stage_board:
                        heu, index = self.depth_iter_search(next_b, limit, d + 1, [i, z])
                        if heu > max_heu:
                            max_heu = heu
                            max_move_index = [i, z]
            return max_heu,ancester_index



    def generate_board(self,search_board, move, color):
        nb = Board(search_board.row, search_board.col, search_board.p)
        n = len(search_board.board)
        m = len(search_board.board[0])
        for i in range(n):
            for z in range(m):
                nb.board[i][z] = Checker(search_board.board[i][z].color,
                                         [search_board.board[i][z].row, search_board.board[i][z].col])
                nb.board[i][z].is_king = search_board.board[i][z].is_king
        nb.make_move(move, color)
        return nb







    def depth_iter_search_heuristic(self, search_board,move):
        nb = Board(search_board.row, search_board.col,search_board.p)
        n = len(search_board.board)
        m = len(search_board.board[0])
        for i in range(n):
            for z in range(m):
                nb.board[i][z] = Checker(search_board.board[i][z].color, [search_board.board[i][z].row, search_board.board[i][z].col])
                nb.board[i][z].is_king = search_board.board[i][z].is_king
        nb.make_move(move,self.color)
        heuristic = 20
        if self.color == 2: #we are white
            heuristic -= nb.black_count
            for i in nb.board:
                for z in i:
                    if z.is_king and z.color==2:
                        heuristic+=1
        else:
            heuristic -= nb.white_count
            for i in nb.board: #we are black
                for z in i:
                    if z.is_king and z.color==1:
                        heuristic += 1
        return heuristic