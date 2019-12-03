#include "product.h"
#include "movie.h"
#include "util.h"
#include <sstream>
#include <string>
using namespace std;


Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating):Product(category, name, price, qty){
	genre_=genre;
	rating_=rating;
}
Movie::~Movie(){

}
//put leywords for movie in set 
set<string> Movie::keywords() const{
	set<string> keywords;
	keywords=parseStringToWords(name_);
	//change case
	string word = genre_;
	word=convToLower(word);
	keywords.insert(word);
	return keywords;

}
//display string info
string Movie::displayString() const{
	stringstream ss;
	ss<<name_<<"\nGenre: "<<genre_<<" Rating: "<<rating_<<"\n"<<price_<<" "<<qty_<<" left.";
	string word="";
	word = ss.str();
	return word;

}
//dump info to ostream
void Movie::dump(std::ostream& os) const{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n"<<genre_<< "\n"<<rating_<<endl;


}