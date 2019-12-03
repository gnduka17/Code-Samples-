#ifndef _STACKSTRING_H
#define _STACKSTRING_H

#include "ulliststr.h"

class StackString
{
public:
    /**
     * Default constructor
     */
    StackString();

    /**
     * Destructor
     */
    ~StackString();

    /**
     * Returns true if the stack is empty, false otherwise
     */
    bool empty() const;

    /**
     * Returns the number of elements on the stack
     */
    size_t size() const;

    /**
     * Pushes a new value, val, onto the top of the stack
     */
    void push(const std::string& val);

    /**
     * Returns the top value on the stack.
     * If the stack is empty, the correct behavior is to throw
     * an exception: use ULListStr::get to achieve this rather
     * than calling ULListStr::back() or ULListStr::front().
     */
    const std::string& top() const;

    /**
     * Removes the top element on the stack.
     * Should do nothing if the stack is empty.
     */
    void pop();

private:
    /**
     * Single data member of the Stack.
     * We use composition to implement this Stack
     */
    ULListStr list_;
};
#endif
