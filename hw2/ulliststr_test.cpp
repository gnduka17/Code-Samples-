/* Write your test code for the ULListStr in this file */

#include <iostream>
#include "ulliststr.h"

using namespace std;


int main(int argc, char* argv[])
{
    //testing pushback call on empty array, and regular pushback and push fronts
    ULListStr dat;
    dat.push_back("7");
    //a new head is created
    dat.push_front("8");
    dat.push_back("9");
    dat.push_back("3");
    dat.push_front("1");
    dat.push_back("10");
    dat.push_back("7");
    dat.push_front("8");
    dat.push_back("9");
    dat.push_back("3");
    dat.push_front("1");
    dat.push_back("10");
    //popping front (1 and 8)
    dat.pop_front();
    dat.pop_front();
    dat.push_back("7");
    dat.push_front("8");
    dat.push_back("9");
    //popback and popfront
    dat.pop_back();
    dat.pop_back();
    dat.pop_back();
    dat.pop_front();

    cout<<"dat front is: 1? "<<dat.front()<<endl;
    cout<<"dat back is:3? "<< dat.back()<<endl;
    for(size_t i =0; i<dat.size();i++){
      cout<<"datcont["<<i<<"]:"<<dat.get(i)<<endl;
    }


    ULListStr dat2;
    //testing pushfront on empty
    dat2.push_front("abc");
    cout<<"dat2 size 1?: "<<dat2.size()<<endl;
    dat2.pop_back();
    cout<<"size is 0?"<<dat2.size()<<endl;
    //checking if empty works
    cout<<"is dat2 empty?:1? "<< dat2.empty()<<endl;


    ULListStr dat3;
    dat3.push_back("d43");
    dat3.pop_front();
    cout<<"size: 0?"<<dat3.size()<<endl;

    ULListStr dat4;
    dat4.push_back("d43");
    dat4.pop_front();
    //popback on empty
    dat4.pop_back();

    dat4.push_back("3455");
    dat4.push_back("40000");
    dat4.push_back("68");
    dat4.push_back("34r");
    dat4.push_back("2");
    dat4.push_back("rtf");
    dat4.push_back("2456");
    dat4.push_back("3r%");
    dat4.push_back("3");
    dat4.push_back("8");
    //a new tail is being created
    dat4.push_back("234444");

    cout<<"size of dat:11? "<<dat4.size()<<endl;
    cout<<"dat[6]=2456?:"<<dat4.get(6)<<endl;
    cout<<"dat[3]=34r?:"<<dat4.get(3)<<endl;
    cout<<"dat[9]=8?:"<<dat4.get(9)<<endl;

    dat4.push_front("abc");
    dat4.push_front("efg");
    dat4.push_front("hij");
    dat4.push_front("jkl");
    dat4.push_back("2456");


    for(size_t j=0; j<dat4.size(); j++){
      cout<<"dat["<<j<<"]: "<<dat4.get(j)<<endl;
    }

    cout<<"back: 2456?"<<dat4.back()<<endl;
    cout<<"front: jkl? "<<dat4.front()<<endl;


    dat4.clear();

    dat4.push_front("5");
    cout<<"size: 1?"<<dat4.size()<<endl;
    dat4.pop_back();
    cout<<"size: 0?"<<dat4.size()<<endl;
    dat4.pop_back();
    cout<<"I pop_backed an empty array"<<endl;
    dat4.pop_front();
    cout<<"i pop_fronted on an empty array"<<endl;

    ULListStr dat1;
    dat1.push_back("7");
    dat1.push_front("8");
    dat1.push_back("9");
    dat1.push_back("3");
    dat1.push_front("1");
    dat1.push_back("10");
    dat1.push_back("7");

    //testing clearing
    dat1.clear();

    //popfront right after pushfront which should clear/delete array
    dat1.push_front("gloria");
    dat1.pop_front();
    if(dat1.empty()){
      cout<<"dat1 is emptyyy/deleted after I push 1 item then pop 1 item"<<endl;
    }

    cout<<"YOU HAVE PASSED GIRLY<3"<<endl;




  return 0;
}
