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
#include "review.h"

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
	void addReview(const std::string& prodName,
                          int rating,
                          const std::string& username,
                          const std::string& date,
                          const std::string& review_text);
	double getProdRating(std::string prodname);
private:
	//map of string keyword to set of products with that keyword
	std::map<std::string,std::set<Product*>> keywordproduct; 
	std::set<Product*>productholder;//set of all the products
	std::map<std::string, User*> userholder;//map of username to user
	std::set<User*>realuserhold;//set of all users
	std::map<std::string, std::deque<Product*>> usercart;//map username to cart
	std::map<std::string, std::vector<Review*>> ProdReview; //map prodname to reviews
	std::map<std::string, Product*> nameNprod; //map of product name to product
	std::set<Review*>rev;//set of reviews 

};
#endif