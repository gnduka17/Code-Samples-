#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <iomanip>

/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User {
public:
    User();
    User(std::string name, double balance, int type,unsigned long long hashPass);
    virtual ~User();

    double getBalance() const;
    std::string getName() const;
    void deductAmount(double amt);
    virtual void dump(std::ostream& os);
    unsigned long long getHash();


private:
    std::string name_;
    double balance_;
    int type_;
    unsigned long long hash_pass;
};
#endif
