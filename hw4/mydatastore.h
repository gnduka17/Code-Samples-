#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "util.h"
#include <string>
#include <set>
#include <map>
#include <deque>
#include <vector>
#include "product.h"
#include "user.h"
#include "datastore.h"

class MyDataStore: public DataStore{
public:
	~MyDataStore();
	void addProduct(Product* p);
	void addUser(User* u);
	std::vector<Product*> search(std::vector<std::string>& terms, int type);
	void dump(std::ostream& ofile);
	void addtoCart(Product* a, std::string un);
	bool isUserinSet(std::string un);
	std::vector<Product*> CartinVector(std::string un);
	int cartSize(std::string un);
	void buycart(std::string un);
	void viewcart(std::vector<Product*> v);
private:
	std::map<std::string,std::set<Product*>> keywordproduct; //map of username and set of products
	std::set<Product*>productholder;//set of all the products
	std::map<std::string, User*> userholder;//map of username to user
	std::set<User*>realuserhold;//set of all users
	std::map<std::string, std::deque<Product*>> usercart;//map username to cart

};
#endif