#include <iostream>
#include "stackstring.h"
#include <fstream>
#include <cctype>
#include <sstream>
#include <algorithm>

using namespace std;

string nospace(string compact);

int main (int argc, char* argv[]){

	if(argc < 3){
	    cerr << "Please provide a input filename and output filename" << endl;
	    return 0;
  	}
  	ifstream ifile(argv[1]);
  	ofstream ofs(argv[2]);

  	if(ifile.fail()){
	    cout << "Error" << endl;
	    return 0;
  	}
    //declaring variables
  	string expression;
  	StackString exholder;
  	string word = "";
  	string newword = "";
  	string addedword = "";
  	string lookin = "";
  	int count =0;
  	int count2 = 0;
  	int par = 0;
  	int count3 = 0;
  	bool minus = false;
  	bool admin = false;
  
//retrieving each line
  	while(getline(ifile, expression)){
  		expression = nospace(expression);

      //checking if right number of parentheses
  		for(size_t k =0; k<expression.size();k++){
  			if(expression[k]=='('){
  				par++;
  			}
  			else if(expression[k]==')'){
  				par--;
  			}
  		}

  		if(par!=0){
  			ofs<<"Malformed"<<endl;
  			par = 0;
  			continue;
  		}
      //check if string is empty
  		if(expression==""){
  			ofs<<endl;
  			continue;
  		}

  		for(size_t i =0; i<expression.size(); i++){

  			if(expression[i]=='('){
  				if(word == ""){
  					exholder.push("(");
  				}
          //check abd(de) vs abd+(de)
  				else{
  					count3++;
  					break;
  				}
          //resetting variables
  				admin = false;
  				minus=false;
  			}
        //check if capital letter
  			else if(isupper(expression[i])!=0){
  				ofs<<"Malformed"<<endl;
  				count++;
  				break;
  			}
  			else if(expression[i]==')'){
  				minus=false;
  				admin = false;
  				while(exholder.top()!="("){
            //adding words
  					if(exholder.top()=="+"){
	  					exholder.pop();
	  					addedword = exholder.top();
	  					exholder.pop();
	  					word = addedword + word;
	  					addedword = "";
  					}
            //subtracting words
  					else if(exholder.top()=="-"){
  						exholder.pop();
  						lookin = exholder.top();
  						exholder.pop();
  						size_t found = lookin.find(word);

  						//word not found in longer word  
  						if(found!=string::npos){
  							lookin.erase(found, word.size());
  							word = lookin;
  							lookin = "";
  						}
  						else{
  							word = lookin;
  							lookin = "";
  						}
  					}
            //changing word given the character
  					else if(exholder.top()==">"){
  						for(size_t j =1; j<word.size();j++){
  							newword.push_back(word[j]);
  						}
  						word = newword;
  						newword = "";
  						exholder.pop();
  					}
  					else if(exholder.top()=="<"){
  						word.pop_back();
  						exholder.pop();
  					}
  				}
  				exholder.pop();
  			}
        //if its a letter push it into the word string
  			else if(isalpha(expression[i])!=false){
  				word.push_back(expression[i]);
  			}
  			else if(expression[i]=='+'){
          //checking if there is already a minus sign in expression
  				if(minus==true){
  					minus=false;
  					ofs<<"Malformed"<<endl;
  					count++;
  					break;
  				}
  				while(exholder.empty()==true||exholder.top()=="<"||exholder.top()==">"){
            //check if there is no open parentheses
  					if(exholder.empty()==true){
  						count2++;
  						break;
  					}
            //do changes to word
  					else if(exholder.top()=="<"){
  						word.pop_back();
  						exholder.pop();
  					}
  					else if(exholder.top()==">"){
  						for(size_t j =1; j<word.size();j++){
  							newword.push_back(word[j]);
  						}
  						word = newword;
  						newword = "";
  						exholder.pop();
  					}
  				}
  				if(word ==""){
  					count2++;
  				}
  				else{
  					exholder.push(word);
  					word = "";
  					exholder.push("+");
  					admin = true;
  				}
  				if(count2!=0){
  					ofs<<"Malformed"<<endl;
  					count2=0;
  					count++;
  					break;
  				}	
  			}
  			else if(expression[i]=='-'){
          //check if there is already a + or -
  				if(minus==true ||admin==true){
  					minus=false;
  					admin = false;
  					ofs<<"Malformed"<<endl;
  					count++;
  					break;
  				}
  				while(exholder.empty()==true||exholder.top()=="<"||exholder.top()==">"){
  					if(exholder.empty()==true){
  						count2++;
  						break;
  					}
  					else if(exholder.top()=="<"){
  						word.pop_back();
  						exholder.pop();
  					}
  					else if(exholder.top()==">"){
  						for(size_t j =1; j<word.size();j++){
  							newword.push_back(word[j]);
  						}
  						word = newword;
  						newword = "";
  						exholder.pop();
  					}
  				}
  				if(word ==""){
  					count2++;
  				}
  				else{
            //push word and -
  					exholder.push(word);
  					word = "";
  					exholder.push("-");
  					minus = true;
  				}
  				if(count2!=0){
  					ofs<<"Malformed"<<endl;
  					count2=0;
  					count++;
  					break;
  				}
  			}
  			else if(expression[i]=='<'){
          // no < - or <+
  				if(expression[i+1]=='+' || expression[i+1]=='-'){
  					count3++;
  					break;
  				}
          else if(word!=""){
            count3++;
            break;
          }
  				exholder.push("<");

  			}
  			else if(expression[i]=='>'){
          //no >- or >+
  				if(expression[i+1]=='+' || expression[i+1]=='-'){
  					count3++;
  					break;
  				}
          else if(word!=""){
            count3++;
            break;
          }
  				exholder.push(">");

  			}
        //anything else is malformed
  			else{
  				ofs<<"Malformed"<<endl;
  				count++;
  				break;
  			}
  		}

  		if(count3!=0){
  			count3=0;
  			word = "";
  			ofs<<"Malformed"<<endl;
        //resetting stack
  			while(exholder.empty()!=true){
  				exholder.pop();
  			}
  			continue;
  		}
  		if(count!=0){
  			count =0;
  			word = "";
        //resetting stack
  			while(exholder.empty()!=true){
  				exholder.pop();
  			}
  			continue;
  		}
      //if< or > is left then do expression
  		while(exholder.empty()!=true){
  			if(exholder.top()=="<"){
  				word.pop_back();
  				exholder.pop();
  			}
  			else if(exholder.top()==">"){
  				for(size_t j =1; j<word.size();j++){
  					newword.push_back(word[j]);
  				}
  				word = newword;
  				newword = "";
  				exholder.pop();
  			}
  			else if(exholder.top()=="("){
  				word = "Malformed";
  				while(exholder.empty()!=true){
  					exholder.pop();
  				}
  				break;
  			}
  		}

  		ofs<<word<<endl;
  		word = "";
  	}
    ifile.close();
    ofs.close();
   
	return 0;
}
//function to eliminate spaces in string 
string nospace(string compact){
	compact.erase(remove(compact.begin(), compact.end(), ' '), compact.end()); 
    return compact; 
}
