#include "product.h"
#include "clothing.h"
#include <sstream>
#include <string>
using namespace std;


Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand):Product(category, name, price, qty){
	size_=size;
	brand_=brand;
}
Clothing::~Clothing(){

}
	//put keyword in set for clothing
set<string> Clothing::keywords() const{
	set<string> keywords;
	set<string> holder;
	//parse name and brand
	holder=parseStringToWords(name_);
	keywords = parseStringToWords(brand_);
	for(std::set<string>::iterator itr = holder.begin(); itr !=holder.end(); ++itr){
		keywords.insert(*itr);
	}
	return keywords;

}
//display string
string Clothing::displayString() const{
	stringstream ss;
	ss<<name_<<"\nSize: "<<size_<<" Brand: "<<brand_<<"\n"<<price_
	<<" "<<qty_<<" left."<<"\nRating: "<<fixed<<setprecision(2)<<avgrating<<endl;
	string word="";
	word = ss.str();
	return word;

}
//display in ostream
void Clothing::dump(std::ostream& os) const{
	os << category_ << "\n" << name_ << "\n" <<fixed<<setprecision(2)<< price_ << "\n" << qty_ << "\n"<<size_<< "\n"<<brand_<<endl;


}