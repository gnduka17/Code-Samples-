all:puzzle
puzzle: puzzle.cpp board.o puzzle_move.o puzzle_heur.o puzzle_solver.o
	g++ -g -Wall puzzle.cpp board.o puzzle_move.o puzzle_heur.o puzzle_solver.o -o puzzle -std=c++11
board.o: board.cpp board.h
	g++ -g -Wall -c board.cpp -o board.o -std=c++11
puzzle_heur.o: puzzle_heur.cpp puzzle_heur.h
	g++ -g -Wall -c puzzle_heur.cpp -o puzzle_heur.o -std=c++11
puzzle_solver.o: puzzle_solver.cpp puzzle_solver.h heap.h puzzle_heur.h puzzle_move.h
	g++ -g -Wall -c puzzle_solver.cpp -o puzzle_solver.o -std=c++11
puzzle_move.o: puzzle_move.cpp puzzle_move.h board.h
	g++ -g -Wall -c puzzle_move.cpp -o puzzle_move.o -std=c++11
clean: 
	rm -rf *o