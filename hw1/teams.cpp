#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

//void swap(int a, int b, string* array);

// *You* are not allowed to use global variables
//  but for just the output portion *we* will. ;>
int combo = 1;

// @brief Prints a single combination of teams
//
// @param[in] team1 Array containing the names of team 1
// @param[in] team2 Array containing the names of team 2
// @param[in] len Size of each array
void printSolution(const string* team1, 
		   const string* team2,
		   int len)
{
  cout << "\nCombination " << combo++ << endl;
  cout << "T1: ";
  for(int i=0; i < len; i++){
    cout << team1[i] << " ";
  }
  cout << endl;
  cout << "T2: ";
  for(int i=0; i < len; i++){
    cout << team2[i] << " ";
  }
  cout << endl;
}

// figure function determines the different combinations recursively
// size1 is team1 size, size2 is team2 size, and r is size of names
void figure(string* names, int index, string* team1, string* team2, int size1, int size2, int r){
  if(size1==r/2 && size2==r/2){
    printSolution(team1, team2, size1);
    return;
  }
  else{
    if(r/2>size1){
      team1[size1]=names[index];
      figure(names, index+1, team1, team2, size1+1, size2,r);
    }
    if(r/2>size2){
      team2[size2]=names[index];
      figure(names, index+1, team1, team2, size1, size2+1,r);
    }
  }
}

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide a file of names" << endl;
    return 1;
  }
  ifstream myfile;
  myfile.open(argv[1]);
  if(myfile.fail()){
    cout << "Error" << endl;
    return 1;
  }

  int number;
  myfile>>number;

  if(myfile.fail()){
    cout<<"Error";
    return 1;
  }

  string *filenames = new string[number];
  // inputting everything in string array
  for(int i =0; i <number; i++){
    myfile>>filenames[i];
    if(myfile.fail()){
      cout<<"Error";
      return 1;
    }
  }

  string* t1;
  string* t2;

  t1 = new string[number/2];
  t2= new string[number/2];

  figure(filenames, 0, t1, t2, 0, 0,number);

  delete [] t1;
  delete [] t2;
  delete [] filenames;
  
  myfile.close();
  return 0;
}
