/*
CSCI 104: Homework 2 Problem 6

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/
#include "split.h"
/* Add a prototype for a helper function here if you need */

void splithelper(Node*& in, Node*& odds, Node*& evens, Node* tracker1, Node* tracker2);

//split function 
void split(Node*& in, Node*& odds, Node*& evens)
{
	Node* etrack=nullptr;
	Node* otrack=nullptr;
	splithelper(in, odds, evens, etrack, otrack);
	//set in to nullptr after split
	in = nullptr;
}
//split helper function 
void splithelper(Node*& in, Node*& odds, Node*& evens, Node* etracker1, Node* otracker2){
	if(in==nullptr){
		if(etracker1==nullptr || otracker2==nullptr){
			return;
		}
		//trackers of the last element in even and odd list
		etracker1->next=nullptr;
		otracker2->next=nullptr;
		return;
	}
	else{
		//if odd value then connect to odd list
		if(in->value %2 !=0){
			if(odds==nullptr){
				odds=in;
				otracker2 = odds;
			}
			else{
				otracker2->next=in;
				otracker2=in;
			}
			splithelper(in->next, odds, evens,etracker1,otracker2);
		}
		//if even value connect to even list
		else{
			if(evens==nullptr){
				evens=in;
				etracker1 = evens;
			}
			else{
				etracker1->next=in;
				etracker1=in;
			}
			splithelper(in->next, odds, evens, etracker1, otracker2);
		}
	}
}
