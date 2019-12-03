#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "board.h"
using namespace std;


Board::Board(int dim, int numInitMoves, int seed )
{
  size_ = dim*dim;
  tiles_ = new int[size_];
  srand(seed);
  for(int i=0; i < size_; i++){
    tiles_[i] = i;
  }
  int blankLoc = 0;
  while(numInitMoves > 0){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < size_){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      tiles_[blankLoc] = tiles_[randNeighbor];
      tiles_[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }
}

void Board::move(int tile)
{
  int side_dim = dim();
  int tr, tc, br, bc;

  // find tile row and column
  int i=-1;
  while(tiles_[++i] != tile);

  tr = i / side_dim; 
  tc = i % side_dim;

  // find blank row and column
  int j=-1;
  while(tiles_[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;

  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    stringstream ss;
    ss << "Invalid move of tile " << tile << " at ";
    ss << tr << "," << tc << " and blank spot at ";
    ss << br << "," << bc << endl;
    throw BoardMoveError(ss.str());
  }
  // Swap tile and blank spot
  tiles_[j] = tile;
  tiles_[i] = 0;
}

// Generate new boards representing all the potential moves of tiles into 
// the current blank tile location. The returned map should have
// the key as the tile moved and the value as a new Board object with the
// configuration reflecting the move of that tile into the blank spot
map<int, Board*> Board::potentialMoves() const
{

  int emptyrow;
  int emptycol;
  int dim = this->dim();
  map<int, Board*>holder;
  for(int i=0;i<size_;i++){
    if(tiles_[i]==0){
      //finding the row and col for blank tile
      emptyrow=i/dim;
      emptycol=i%dim;
    }
  }
  //check if space all around the empty space is valid
  if(emptyrow-1>=0&&emptyrow-1<dim){
    Board* name =new Board(*this);
    int index = (emptyrow-1)*dim+emptycol;
    name->move(tiles_[index]);
    holder.insert(make_pair(tiles_[index], name));
  }
  if(emptyrow+1>=0&&emptyrow+1<dim){
    Board* name2 =new Board(*this);
    int index2 = (emptyrow+1)*dim+emptycol;
    name2->move(tiles_[index2]);
    holder.insert(make_pair(tiles_[index2], name2));
  }
  if(emptycol-1>=0&&emptycol-1<dim){
    Board* name3 =new Board(*this);
    int index3 = emptyrow*dim+(emptycol-1);
    name3->move(tiles_[index3]);
    holder.insert(make_pair(tiles_[index3], name3));
  }
  if(emptycol+1>=0&&emptycol+1<dim){
    Board* name4 =new Board(*this);
    int index4 = emptyrow*dim+(emptycol+1);
    name4->move(tiles_[index4]);
    holder.insert(make_pair(tiles_[index4], name4));
  }
  return holder;
}

// Complete this function
bool Board::solved() const
{
  for(int i = 1;i<size_;i++){
    if(tiles_[i]!=i){
      return false;
    }
  }
  return true;
}
bool Board::operator<(const Board& rhs) const{
  for(int i=0;i<size_;i++){
    //if the first is less then return true
    if(tiles_[i]<rhs[i]){
      return true;
    }
    //if greater than return false
    else if(tiles_[i]>rhs[i]){
      return false;
    }
    else if(tiles_[i]==rhs[i]){
      continue;
    }
  }
  return false;
}


const int& Board::operator[](int loc) const 
{ 
  return tiles_[loc]; 
}

int Board::size() const 
{ 
  return size_; 
}

int Board::dim() const
{
  return static_cast<int>(sqrt(size_));
}

void Board::printRowBanner(ostream& os) const
{
  int side_dim = dim();
  if(side_dim == 0) return;
  os << '+';
  for(int i=0; i < side_dim; i++){
    os << "--+";
  }
  os << endl;
}
ostream& operator<<(ostream &os, const Board &b){
  b.printRowBanner(os);
  //print the grid
  for(int i=0;i<b.dim();i++){
      for(int j=0;j<b.dim();j++){
        //if less than 10 then add extra space
        if(b[i*b.dim()+j]==0){
          os<<"|  ";
        }
        else{
          if(b[i*b.dim()+j]>=10){
            os<<"|"<<b[i*b.dim()+j];

          }
          else{
            os<<"| "<<b[i*b.dim()+j];
          }
        }
    }
    os<<"|";
    os<<endl;
    b.printRowBanner(os);
  }
  return os;

}
Board::Board(const Board& b){
  size_=b.size();
  tiles_=new int[size_];
  for(int i=0;i<size_;i++){
    tiles_[i]=b[i];
  }
  return;
}
Board::~Board(){
  delete [] tiles_;
}