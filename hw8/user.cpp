#include "user.h"
using namespace std;

User::User() : name_("unknown"), balance_(0.0), type_(1), hash_pass(0)
{

}
User::User(std::string name, double balance, int type, unsigned long long hashPass) :
    name_(name), balance_(balance), type_(type), hash_pass(hashPass)
{

}

User::~User()
{

}
std::string User::getName() const
{
    return name_;
}

double User::getBalance() const
{
    return balance_;
}

void User::deductAmount(double amt)
{
    balance_ -= amt;
}

void User::dump(std::ostream& os)
{
    os << name_ << " "<< fixed<<setprecision(2)<< balance_ << " " << type_ << endl;
}
 unsigned long long User::getHash(){
 	return hash_pass;
 }
