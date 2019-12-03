#ifndef ULLISTSTR_H
#define ULLISTSTR_H
#include <string>

#define ARRSIZE 10
class ULListStr {
 public:
  struct Item {
    std::string val[ARRSIZE];
    /**
     * first and last indicate the occupied/used 
     * elements of the array where first is an
     * inclusive index and last is an exclusive
     * index (i.e. first=0, last=0 indicates none
     * of the elements of the array are used and
     * first=0, last=ARRSIZE indicates the array
     * is fully occupied
     */
    size_t first, last;
    Item *prev;
    Item *next;

    /**
     * Default constructor
     */
    Item(){
      first = last = 0;
      prev = next = NULL;
    }
  };

  /**
   * Default constructor - empty list
   */
  ULListStr();

  /**
   * Destructor
   */
  ~ULListStr();

  /**
   * Returns the current number of items in the list 
   *   - MUST RUN in O(1)
   */
  size_t size() const;

  /**
   * Returns true if the list is empty, false otherwise
   *   - MUST RUN in O(1)
   */
  bool empty() const;

  /**
   * Adds a new value to the back of the list
   *   - MUST RUN in O(1)
   */
  void push_back(const std::string& val);

  /**
   * Removes a value from the back of the list
   *   - MUST RUN in O(1)
   */
  void pop_back();
  
  /**
   * Adds a new value to the front of the list.
   * If there is room before the 'first' value in
   * the head node add it there, otherwise, 
   * allocate a new head node.
   *   - MUST RUN in O(1)
   */
  void push_front(const std::string& val);

  /**
   * Removes a value from the front of the list
   *   - MUST RUN in O(1)
   */
  void pop_front();
  
  /**
   * Returns a const reference to the back element
   *   - MUST RUN in O(1)
   */
  std::string const & back() const;

  /**
   * Returns a const reference to the front element
   *   - MUST RUN in O(1)
   */
  std::string const & front() const;
  
  /**
   * Overwrites the old value at index, pos, with val
   *   - Can run in O(n)
   */
  void set(size_t pos, const std::string& val);

  /**
   * Returns the value at index, pos
   *   - Can run in O(n)
   */
  std::string& get(size_t pos);

  /**
   * Returns the value at index, pos
   *   - Can run in O(n)
   */
  std::string const & get(size_t pos) const;

  /**
   * Deletes all items in the list
   */
  void clear();
  /**
   * Copy constructor (initiale list with deep copy of `other`)
   *
   * It is fine to consolodate the contents of `other` to start at the head
   *  Item's location 0.
   *
   * MUST RUN in O(n) where n is the size of other
   */
  ULListStr (const ULListStr& other);

  /**
   * Assignment Operator (replace current contents with deep copy of `other`)
   *  Note: It is fine to deallocate the current contents and construct
   *  a whole new set of internal Items maintaining the same internal data
   *  element positions, or consolodating the elements to start at the head
   *  Item's location 0.
   *
   *  MUST RUN in O(n+m) where n is the size of this list and m the size
   *   of `other` and not O(n^2) or O(m^2)
   */
  ULListStr& operator= (const ULListStr& other);

  /**
   * Concatenation operator.
   * Returns a separate list consisting of other appended to this.
   * Does not modify this nor other.
   *
   *  Note: It is fine to consolodate the elements from both lists 
   *  to start at the returned list's head Item's location 0.
   *
   *  MUST RUN in O(n+m) where n is the size of this list and m the size
   *   of `other`
   */
  ULListStr operator+ (const ULListStr& other) const;

  /**
   * Remove the last 'num' strings from the **back** of this list
   * 
   * Returns a reference to this list.
   *
   *  MUST RUN in O(num)
   */
  ULListStr& operator-= (size_t num);

  /**
   * Const access Operator of element at location/position: loc
   */
  std::string const & operator[] (size_t loc) const;

  /**
   * Non-const access Operator of element at location/position: loc
   */
  std::string & operator[] (size_t loc);
  

 private:
  /** 
   * Returns a pointer to the item at index, loc,
   *  if loc is valid and NULL otherwise
   *   - MUST RUN in O(n) 
   */
  std::string* getValAtLoc(size_t loc) const;

  /*
   * Appends the contents of `other` to the end of `this` list
   * allocating new Items and updating pointers and first/last
   * indices of `this` as necessary.
   *
   * Does not modify `other`.
   *
   * Runs in O(m) where m is the size of `other`
   */
  void appendContents(const ULListStr& other);

  /**
   * Data members
   *  You MUST keep these members though you
   *  may add more if desired.
   */
  Item* head_;
  Item* tail_;
  size_t size_;
};

#endif
