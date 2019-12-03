#include "mydatastore.h"

using namespace std;

MyDataStore::~MyDataStore(){
	for(set<Product*>::iterator itr = productholder.begin(); itr !=productholder.end(); ++itr){
		delete *itr;
	}
	for(set<User*>::iterator it = realuserhold.begin(); it !=realuserhold.end(); ++it){
		delete *it;
	}
	// for(set<Review*>::iterator it1 = rev.begin(); it1 !=rev.end(); ++it1){
	// 	delete *it1;
	// }
}
 /**
     * Adds a product to the data store
     */
void MyDataStore::addProduct(Product* p){
	//inserting into needed data structures
	nameNprod.insert(make_pair(p->getName(), p));

	vector<Review*> reviews_;
	ProdReview.insert(make_pair(p->getName(), reviews_));

	set<string>productkeys;
	productkeys = p->keywords();

	//insert to product holder set
	productholder.insert(p);

	if(productkeys.empty()){
		return;
	}
	//inserting to map of string to set of keywords
	for(std::set<string>::iterator itr = productkeys.begin(); itr!=productkeys.end(); ++itr){
		if(keywordproduct.find(*itr)==keywordproduct.end()){
			set<Product*>holder;
			holder.insert(p);
			keywordproduct.insert(make_pair(*itr,holder));
		}
		else{
			keywordproduct[*itr].insert(p);
		}
	}
}

/**
     * Adds a user to the data store
     */
//basically inserting user to map
void MyDataStore::addUser(User* u){
	deque<Product*>p;
	string username = u->getName();
	userholder.insert(make_pair(username, u));
	realuserhold.insert(u);
	usercart.insert(make_pair(username,p));
}
/**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
	vector<Product*>holder;
	set<Product*>results;
	set<Product*>s2;
	
	if(terms.empty()){ return holder;}
	//set first term to results
	if(keywordproduct.find(terms[0])!=keywordproduct.end()){
		results = keywordproduct[terms[0]];
	}
		for(unsigned int i =1; i<terms.size(); i++){
			if(keywordproduct.find(terms[i])!=keywordproduct.end()){//check if term is in map
				s2=keywordproduct[terms[i]];
			}
			else{
				s2.clear();//if a term is not in map set the set to empty
			}	
			//IF AND THEN DO SETINTERSECTION
				if(type==0){
					results=setIntersection(s2, results);
				}
				//IF OR DO UNION INTERSECTION
				else if(type==1){
					results=setUnion(s2, results);
				}	
			
		}
		if(results.empty()){//if the set is empty then return the empty variable
			return holder;
		}
		for(std::set<Product*>::iterator itr = results.begin(); itr!=results.end(); ++itr){
			holder.push_back(*itr);
		}
		return holder;
}
/**
     * Reproduce the database file from the current Products and User values
     */
void MyDataStore::dump(std::ostream& ofile){
	ofile<<"<products>"<<endl;
	for(std::set<Product*>::iterator itr = productholder.begin(); itr!=productholder.end(); ++itr){
		(*itr)->dump(ofile);
	}
	ofile<<"</products>"<<endl<<"<users>"<<endl;

	for(std::set<User*>::iterator it = realuserhold.begin(); it!=realuserhold.end(); ++it){
		(*it)->dump(ofile);
	}
	ofile<<"</users>"<<endl<<"<reviews>"<<endl;
	for(std::set<Product*>::iterator it1 = productholder.begin(); 
		it1!=productholder.end(); ++it1){
		(*it1)->spillit(ofile);//spillit function is basically a dump for reviews
	}
	ofile<<"</reviews>"<<endl;


}
//add product to user's cart
void MyDataStore::addtoCart(Product* a, string un){
	if(usercart.find(un)!=usercart.end()){
		usercart[un].push_back(a);
	}
}
//checks if user is in set
bool MyDataStore::isUserinSet(string un){
	if(usercart.find(un)!=usercart.end()){
		return true;
	}
	else{
		return false;
	}
}
//transfroms cart into a vector then output the vector
vector<Product*> MyDataStore::CartinVector(string un){
	vector<Product*> v;
	for(deque<Product*>::iterator itr = usercart[un].begin(); itr!=usercart[un].end(); ++itr){
		v.push_back(*itr);
	}
	return v;
}
//output cart size
int MyDataStore::cartSize(std::string un){
	return usercart[un].size();
}
//update all informations decrement item and credit
void MyDataStore::buycart(std::string un){
	for(deque<Product*>::iterator itr = usercart[un].begin(); itr!=usercart[un].end(); ++itr){
		if(((*itr)->getQty()>0)&&((*itr)->getPrice()<userholder[un]->getBalance())){
			cout << "processing" << endl;
			(*itr)->subtractQty(1);
			userholder[un]->deductAmount((*itr)->getPrice());
			usercart[un].pop_front();
		}
	}
}
//function outputs cart when viewcart is hit
void MyDataStore::viewcart(std::vector<Product*> v){
	int num =1;
	if(v.empty()){
		return;
	}
	for(vector<Product*>::iterator it = v.begin(); it != v.end(); ++it) {
        cout << "Item " << num << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        num++;
    }
}
void MyDataStore::addReview(const std::string& prodName,
                          int rating,
                          const std::string& username,
                          const std::string& date,
                          const std::string& review_text){
	if(ProdReview.find(prodName)==ProdReview.end()){//checks if the product name isnt in database
		return;
	}
	if(isUserinSet(username)==false){//if user is not in set 
		return;
	}
	
	Review* review = new Review(rating, username, date, review_text);
	nameNprod[prodName]->addrev(review); //add review in product class

	ProdReview[prodName].push_back(review);//add review in map

}
unsigned long long MyDataStore::correctHash(string username){
	return userholder[username]->getHash();
}

