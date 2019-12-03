#include <sstream>
#include <iomanip>
#include "product.h"

using namespace std;

Product::Product(const std::string category, const std::string name, double price, int qty) :
    name_(name),
    price_(price),
    qty_(qty),
    category_(category),
    avgrating(0.0)

{
}

Product::~Product()
{
    for(vector<Review*>::iterator iter = reviews_.begin(); iter !=reviews_ .end(); ++iter){
        delete *iter;
    }
}


double Product::getPrice() const
{
    return price_;
}

std::string Product::getName() const
{
    return name_;
}

void Product::subtractQty(int num)
{
    qty_ -= num;
}

int Product::getQty() const
{
    return qty_;
}

/**
 * default implementation...can be overriden in a future
 * assignment
 */
bool Product::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}

void Product::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
}

//function to add review in product vector and calculate the average rating 
void Product::addrev(Review* rev){
    double sum = 0.0;
    reviews_.push_back(rev);
    for(unsigned int i=0; i<reviews_.size();i++){
        sum = sum + reviews_[i]->getRating();
    }
    avgrating = sum/reviews_.size();
}
double Product::getAvRating(){
    return avgrating;
}
//return reviews in vector form for a specific product
std::vector<Review*> Product::getReview(){
    return reviews_;
}
//function to dump reviews in ofile
void Product::spillit(std::ostream& os){
    for(unsigned int i =0; i<reviews_.size();i++){
        os<<name_<<endl;
        os<<(reviews_[i])->getRating()<<" "<<(reviews_[i])->getUsername()<<" "<<(reviews_[i])->getDate()<<" "
                <<(reviews_[i])->getReviewText()<<endl;
    }

}

