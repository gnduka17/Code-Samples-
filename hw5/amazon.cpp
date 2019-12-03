#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"
#include "msort.h"

using namespace std;
//comparators: comparing avgrating, name of product, date of review
struct ProdRatingSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getAvRating() > p2->getAvRating());
    }
};
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
struct ProdDateSorter {
    bool operator()(Review* r1, Review* r2) {

        return (r1->getDate() > r2->getDate());
    }
};
void displayProducts(vector<Product*>& hits);
bool isValidDate(string word);
bool isRightDate(int num, int numday);
bool isvalidRN(string rnexample);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;

    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;
    ReviewSectionParser* reviewSectionParser = new ReviewSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);
    parser.addSectionParser("reviews", reviewSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  LOGIN username                  " << endl;
    cout << "  LOGOUT                   " << endl;
    cout << "  AND r/n term term ...                  " << endl;
    cout << "  OR r/n term term ...                   " << endl;
    cout << "  ADD search_hit_number     " << endl;
    cout << "  VIEWCART                   " << endl;
    cout << "  BUYCART                    " << endl;
    cout << "  ADDREV seach_hit_number rating date review_text                   " << endl;
    cout << "  VIEWREV seach_hit_number                    " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    //variable to keep track if user is still logged on or not
    bool username_on = false;
    string username = "";
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if(cmd=="LOGIN"){
                if(ss>>username){
                    //check if validuser
                    if(!ds.isUserinSet(username)){
                        cout<<"Invalid user";
                    }
                    else{
                        username_on = true;
                    }
                }
            }
            else if(cmd=="LOGOUT"){
                username = "";
                username_on = false;

            }
            else if( cmd == "AND") {
                string term="";
                string rn="";
                vector<string> terms;
                if(ss>>rn){
                    rn=trim(rn);
                    //check ig valid r/n input
                    if(isvalidRN(rn)){
                        while(ss >> term) {
                            term = convToLower(term);
                            terms.push_back(term);
                        }
                        hits = ds.search(terms, 0);
                        //sorting hits list
                        if(rn=="r"){
                            ProdRatingSorter pr;
                            std::sort(hits.begin(),hits.end(),pr);
                        }
                        else if(rn=="n"){
                            ProdNameSorter pn;
                            std::sort(hits.begin(),hits.end(),pn);
                        }
                        displayProducts(hits);
                    }
                }    
            }
            else if ( cmd == "OR" ) {
                string term="";
                vector<string> terms;
                string rn="";
                if(ss>>rn){
                    rn=trim(rn);
                    //check valid r/n input
                    if(isvalidRN(rn)){
                        while(ss >> term) {
                            term = convToLower(term);
                            terms.push_back(term);
                        }
                        hits = ds.search(terms, 1);
                        //sorting list
                        if(rn=="r"){
                            ProdRatingSorter pr;
                            std::sort(hits.begin(),hits.end(),pr);
                        }
                        else if(rn=="n"){
                            ProdNameSorter pn;
                            std::sort(hits.begin(),hits.end(),pn);
                        }
                        displayProducts(hits);
                    }
                }    
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */
            else if(cmd=="ADD"){
                unsigned int hitnum = 0;
                //check to see if user is logged on
                if(username_on==false){
                    cout<<"No current user"<<endl;
                }
                else if(ss>>hitnum){
                    //if the hit num is between the range then add product to cart
                    if(hitnum>0 && hitnum<=hits.size()){
                        ds.addtoCart(hits[hitnum-1], username);
                    }
                    else{
                        cout<<"Invalid request";
                    }
                }   
            }
            else if(cmd=="VIEWCART"){
                vector<Product*> holder;
                //check to see if user is logged on
                if(username_on==false){
                    cout<<"No current user"<<endl;
                }
                else{
                    //transforms users cart into vector.
                    holder = ds.CartinVector(username);
                    ds.viewcart(holder);  
                }
                
            }
            else if(cmd=="BUYCART"){
                if(username_on==false){
                    cout<<"No current user"<<endl;
                }
                else{
                    ds.buycart(username); 
                }       
            }
            else if(cmd=="ADDREV"){
                if(username_on==false){
                    cout<<"No current user"<<endl;
                }
                else{
                    unsigned int hit_num = 0;
                    if(ss>>hit_num){ //input valid hit num
                        if(hit_num>0 && hit_num<=hits.size()){ //check to see if its in range
                            unsigned int rating_num = 0;
                            if(ss>>rating_num){
                                if(rating_num>=1&&rating_num<=5){//check to see if rating is valid
                                    string date_ = "";
                                    if(ss>>date_){
                                        if(isValidDate(date_)){//if valid date then continue
                                            string comment;
                                            getline(ss,comment);
                                            if(!comment.empty()){
                                                comment = trim(comment);
                                            }
                                            ds.addReview(hits[hit_num-1]->getName(), rating_num, username, date_, comment);
                                        }
                                        else{
                                            cout<<"Invalid"<<endl;
                                        }
                                    }
                                }
                                else{
                                    cout<<"Invalid"<<endl;
                                }
                            }
                        }
                        else{
                            cout<<"Invalid"<<endl;
                        }
                    }
                }
            }
            else if(cmd=="VIEWREV"){
                unsigned int hit_num;
                if(ss>>hit_num){
                    if(hit_num>0 && hit_num<=hits.size()){//if hit num is in within range
                        Product* hold;
                        ProdDateSorter pd;
                        hold = hits[hit_num-1];
                        vector<Review*> hold1;
                        hold1=hold->getReview();//hold1 is the vector of review from product
                        std::sort(hold1.begin(),hold1.end(),pd);//sorting
                        for (std::vector<Review*>::iterator itr = hold1.begin();//output all the reviews 
                             itr != hold1.end(); ++itr){
                                cout<<(*itr)->getDate()<<" "<<(*itr)->getRating()<<" "
                                <<(*itr)->getUsername()<<" "<<(*itr)->getReviewText()<<endl;
                        }   
                    }
                    else{
                        cout<<"Invalid request";
                    } 
                }
            }
            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
//checks if its a valid r/n
bool isvalidRN(string rnexample){
    if(rnexample.size()==1){
        if(rnexample[0]=='r'||rnexample[0]=='n'){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}
//checks if the month and day fit and are correct
bool isRightDate(int num, int numday){
    if(num < 1 || num > 12){
        return false;
    }
    if(numday<1 || numday>31){
        return false;
    }
    if(num==2){
        if(numday>28){
            return false;
        }
    }
    if(num==4 || num==6 || num==9 ||num==11){
        if(numday>30){
            return false;
        }
    }
    return true;
}
//checks if the date format is correct
bool isValidDate(string word){
    if(word.size()==10){//checks to see if size is 10
        if(word[4]=='-'&&word[7]=='-'){//the - are in correct position
            word.erase(4,1);
            word.erase(6,1);//after erasing - then should be left with digits
            for(unsigned int i =0;i<word.size();i++){//check to see if all are digits
                if(isdigit(word[i])){
                    continue;
                }
                else{
                    return false;
                }
            }
            string mons = "";
            int mon = 0;
            string days="";
            int day = 0;
            mons = word.substr(4,2);
            days = word.substr(6,2);
            mon = stoi(mons);
            day = stoi(days);
            if(isRightDate(mon,day)){//check if its right date
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}
