#include "puzzle_heur.h"

using namespace std;

int PuzzleManhattanHeuristic::compute(const Board& b){
	int integer;
	int pickrow;
	int pickcol;
	int correctrow;
	int correctcol;
	int sum = 0;
	for(int i=0;i<b.size();i++){
		//if at right spot dont do anything
		if(b[i]==i){
			continue;
		}
		else if(b[i]!=0){
			//compute current row and col of i
			pickrow=i/b.dim();
			pickcol=i%b.dim();
			integer=b[i];
			//compute correct row and col
			correctrow=integer/b.dim();
			correctcol=integer%b.dim();
			//add manhattan distance to sum
			sum=sum+(abs(correctrow-pickrow)+abs(correctcol-pickcol));
		}
	}
	return sum;
}

int PuzzleOutOfPlaceHeuristic::compute(const Board& b){
	int count = 0;
	for(int i=0; i<b.size();i++){
		if(b[i]==0){
			continue;
		}
		else if(b[i]!=i){
			count++;
		}
	}
	return count;
}
int PuzzleBFSHeuristic::compute(const Board& b){
	return 0;

}