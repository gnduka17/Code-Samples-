#include "board.h"
#include "puzzle_move.h"

PuzzleMove::PuzzleMove(Board* board){
	this->prev=nullptr;
    this->b= new Board(*board);
    this->tileMove=-1;
    this->h=0;
    this->g=0;
}
PuzzleMove::PuzzleMove(int tile, Board* board, PuzzleMove *parent){
    tileMove=tile;
    b=board;
    prev=parent;
    this->g=parent->g+1;
  }
PuzzleMove::~PuzzleMove(){
    delete b;
  }