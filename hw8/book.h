#ifndef BOOK_H
#define BOOK_H
#include "product.h"
#include "util.h"
#include "mydatastore.h"

class Book: public Product{
public:
	Book(const std::string category, const std::string name, double price, int qty, const std::string name1, const std::string number);
	~Book();
	std::set<std::string> keywords() const;
	std::string displayString() const;
	void dump(std::ostream& os) const;
private:
	std::string authorname_;
	std::string isbnnum_;
};
#endif