#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Location
{
  Location()
  {
    row = -1;
    col = -1;
  }
  Location(int r, int c)
  {
    row = r;
    col = c;
  }
  int row;
  int col;
};

// @param[in] instream - Input (file) stream for the input file.  Opened in main()
// @param[out] grid Blank vector of vectors.  Should be updated with the
//                  contents of the grid from the input file
// @return true if successful, false otherwise (see HW writeup for details
//         about possible error cases to be checked)
bool readGrid(istream& instream, vector<vector<char> >& grid )
{
  int count=0;
  int compcount=0;
  char letter;
  vector<char> temp;
  string line;

  getline(instream, line);
  stringstream tr(line);
  if(line.empty()){
    return false;
  }
  //counting how many columns and checking if it's not a letter
  while(tr>>letter){
    if(isalpha(letter)==0){
      return false;
    }
    count++;
    temp.push_back(letter);
  }
  grid.push_back(temp);
  temp.clear();

  while(getline(instream, line)){
    stringstream ss(line);
    while(ss>>letter){
      if(isalpha(letter)==0){
      return false;
    }
      compcount++;
      temp.push_back(letter);
    }
   //checking if same number of columns in each row
    if(compcount!=count || line.empty()){
      return false;
    }

    compcount=0;
    grid.push_back(temp);
    temp.clear();
  }
  return true;
}

// prototype - will be implemented below
bool findWordHelper(
   const vector<vector<char> >& grid, 
   Location currLoc,
   Location delta,
   string word,
   unsigned int currWordIndex);

// Do not change
void printSolution(const string& targetWord, const Location& start, string direction)
{
  cout << targetWord << " starts at (row,col) = (" << start.row << "," << start.col
       << ") and proceeds " << direction << "." << endl;
}

// Do not change
void printNoSolution(const string& targetWord)
{
  cout << targetWord << " does NOT occur." << endl;
}

// Complete - you should not need to change this.
void findWord(const vector<vector<char> >& grid, 
	      const string& targetWord)
{
  bool found = false;
  if(targetWord.size() < 2){
    cout << "Need a word of length 2 or more." << endl;
    return;
  }
  for(unsigned int r=0; r < grid.size(); r++){
    for(unsigned int c=0; c < grid[r].size(); c++){
      if(grid[r][c] == targetWord[0]){
      	Location loc(r,c);
      	if( findWordHelper(grid, Location(r-1,c), Location(-1, 0), targetWord, 1) ){
      	  printSolution(targetWord, loc, "up");
      	  found = true;
      	}
      	if( findWordHelper(grid, Location(r,c-1), Location(0,-1), targetWord, 1) ){
      	  printSolution(targetWord, loc, "left");
      	  found = true;
      	}
      	if( findWordHelper(grid, Location(r+1,c), Location(1, 0), targetWord, 1) ){
      	  printSolution(targetWord, loc, "down");
      	  found = true;
      	}
      	if( findWordHelper(grid, Location(r,c+1), Location(0,1), targetWord, 1) ){
      	  printSolution(targetWord, loc, "right");
      	  found = true;
      	}
      }      
    }
  }
  if(!found){
    printNoSolution(targetWord);
  }
}

/**
 * @param[in] grid The 2D vector containing the entire search contents
 * @param[in] currLoc Current row and column location to try to match 
 *                    with the next letter
 * @param[in] delta   Indicates direction to move for the next search
 *                    by containing the *change* in row, col values
 *                    (i.e. 1,0 = down since adding 1 will move down 1 row)
 * @param[in] word The word for which you are searching
 * @param[in] currWordIndex The index to word indicating which letter must
 *                          be matched by this call
 */
bool findWordHelper(const vector<vector<char> >& grid, 
		 Location currLoc,
		 Location delta,
		 string word,
		 unsigned int currWordIndex)
{
  unsigned int colsize = grid[0].size();
  unsigned int rowsize = grid.size();
  if((unsigned)currLoc.col>=colsize || (unsigned)currLoc.row>=rowsize){
    return false;
  }
  else{
      if(word[currWordIndex]==grid[currLoc.row][currLoc.col]){
          if(currWordIndex==word.size()-1){
            return true;
        }
        currLoc.row = currLoc.row + delta.row;
        currLoc.col = currLoc.col + delta.col;
        currWordIndex++;
        return findWordHelper(grid, currLoc, delta, word, currWordIndex);
      }
  }
  return 0;
}

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide a grid filename and targetWord" << endl;
    return 1;
  }
  ifstream ifile(argv[1]);
  string targetWord(argv[2]);
  if(ifile.fail()){
    cerr << "Unable to open input grid file" << endl;
    return 1;
  }

  vector<vector<char> > mygrid;
  if( ! readGrid(ifile, mygrid) ){
    cerr << "Error reading grid" << endl;
    ifile.close();
    return 1;
  }
  findWord(mygrid, targetWord);

  return 0;
}
