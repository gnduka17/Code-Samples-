#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
using namespace std;
int main(int argc, char *argv[])
{
  if(argc < 5){
    cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
    return 1;
  }
  //setting input to variables 
  int d = atoi(argv[1]);
  int nummoves = atoi(argv[2]);
  int seed = atoi(argv[3]);
  int heur = atoi(argv[4]);
  int tile;
  deque<int> sequ;

  //creating board and outputting
  Board b(d,nummoves,seed);
  cout<<b<<endl;

  while(!b.solved()){
    cout<<"Enter tile number to move or -1 for a cheat: ";
    cin>>tile;

    //if valid tile then move 
    if(tile>0&&tile<b.size()){
      
      try{
        //move the tile then output
        b.move(tile);
        cout<<b<<endl;
      }
      //catch the error
      catch (BoardMoveError e){
        std::cout << e.what() << std::endl;
      }

    }
    else if(tile==0){
      break;
    }
    else if(tile==-1){
      //output the sequence and expansions
      if(heur==0){
        //BFS
        PuzzleBFSHeuristic puzH;
        PuzzleSolver ps(b,&puzH);
        ps.run();
        cout<<"Try this sequence:"<<endl;
        sequ=ps.getSolution();
        //output the solution
        for (std::deque<int>::iterator it = sequ.begin(); it!=sequ.end(); ++it){
          cout<<*it<<" ";
        }
        cout<<endl;
        cout<<"(Expansions = "<<ps.getNumExpansions()<<")"<<endl;
      }
      else if(heur==1){
        //Tiles out of Place
        PuzzleOutOfPlaceHeuristic puzH;
        PuzzleSolver ps(b,&puzH);
        ps.run();
        cout<<"Try this sequence:"<<endl;
        sequ=ps.getSolution();
        //output the solution
        for (std::deque<int>::iterator it = sequ.begin(); it!=sequ.end(); ++it){
          cout<<*it<<" ";
        }
        cout<<endl;
        cout<<"(Expansions = "<<ps.getNumExpansions()<<")"<<endl;
        }
      else if(heur==2){
        //manhattan
        PuzzleManhattanHeuristic puzH;
        PuzzleSolver ps(b,&puzH);
        ps.run();
        cout<<"Try this sequence:"<<endl;
        sequ=ps.getSolution();
        //output the solutions
        for (std::deque<int>::iterator it = sequ.begin(); it!=sequ.end(); ++it){
          cout<<*it<<" ";
        }
        cout<<endl;
        cout<<"(Expansions = "<<ps.getNumExpansions()<<")"<<endl;
      }
      
    }
    
  }
  return 0;
}
