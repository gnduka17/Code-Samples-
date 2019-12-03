#include "puzzle_solver.h"


PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph):b_(b),ph_(ph){
	expansions_ = 0;
}
PuzzleSolver::~PuzzleSolver(){

}
void PuzzleSolver::run(){
	PuzzleMoveScoreComp sc;
	map<int, Board*> succ;
	PuzzleMove* puz = new PuzzleMove(&b_);

	Heap<PuzzleMove*,PuzzleMoveScoreComp> heapholder(2,sc);
	PuzzleMoveSet closedlist;

	puz->h=ph_->compute(*(puz->b));
	
	//push start state to open and closed
	heapholder.push(puz);
	closedlist.insert(puz);
	//while openlist is not empty
	while(!heapholder.empty()){
		//remove min. f-value state from open_list(if tie in f-values, 
		//select one w/ larger g-value)
		PuzzleMove* s;
		s = heapholder.top();
		heapholder.pop();
		//if s = goal node then trace path back to start; STOP
		if(s->b->solved()){
			while(s->prev!=nullptr){
				solution_.push_front(s->tileMove);
				s=s->prev;
			}
			for (std::set<PuzzleMove*>::iterator itr=closedlist.begin(); itr!=closedlist.end(); ++itr){
				delete *itr;
			}
			break;
		}
		else {
			//S's neighbors
			succ=s->b->potentialMoves();
			//compare to evreytthing in clsoe
			//if not in close then push to open
			for (std::map<int,Board*>::iterator it=succ.begin(); it!=succ.end(); ++it){
				PuzzleMove* temp = new PuzzleMove(it->first,it->second,s);
				//check if its in closed 
				if(closedlist.find(temp)==closedlist.end()){
					temp->h = ph_->compute(*(temp->b));
					closedlist.insert(temp);
					heapholder.push(temp);
					expansions_++;
				}
				else{
					delete temp;
				}
			}
		}
	}

}
std::deque<int> PuzzleSolver::getSolution(){
	return solution_;

}
int PuzzleSolver::getNumExpansions(){
	return expansions_;

}