#include "product.h"
#include "book.h"
#include "util.h"
#include <sstream>
#include <string>
using namespace std;


Book::Book(const std::string category, const std::string name, double price, int qty, const std::string name1, const std::string number):Product(category, name, price, qty){
	authorname_=name1;
	isbnnum_=number;
}
Book::~Book(){

}
set<string> Book::keywords() const{
	set<string> keywords;
	set<string> holder;
	string word="";
	//parse author name
	keywords = parseStringToWords(authorname_);
	//change cases 
	word = isbnnum_;
	word=convToLower(word);
	//insert isbn keyword into set
	keywords.insert(word);
	//parse title
	holder = parseStringToWords(name_);

	for(std::set<string>::iterator itr = holder.begin(); itr !=holder.end(); ++itr){
		keywords.insert(*itr);
	}
	return keywords;

}
//display string for book
string Book::displayString() const{
	stringstream ss;
	ss<<name_<<"\nAuthor: "<<authorname_<<" ISBN: "<<isbnnum_<<"\n"
	<<price_<<" "<<qty_<<" left."<<"\nRating: "<<fixed<<setprecision(2)<<avgrating<<endl;
	string word="";
	word = ss.str();
	return word;

}
//dump into ostream
void Book::dump(std::ostream& os) const{
	os << category_ << "\n" << name_ << "\n" <<fixed<<setprecision(2)<< price_ << "\n" << qty_ << "\n"<<isbnnum_<< "\n"<<authorname_<<endl;


}