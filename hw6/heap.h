#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, PComparator c = PComparator());

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

 private:
  /// Add whatever helper functions and data members you need below
  std::vector<T>heaparray; 
  unsigned int m;
  PComparator c;
  void trickleUp(int loc);
  void trickleDown(int loc);

};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c) 
{
  if(m>=2){
    this->m=m;
    this->c=c;
  }
}
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap() 
{
}
template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(int loc)
{
  if(loc>0 && this->c(heaparray[loc],heaparray[((loc-1)/m)])){
    //swap with last and parent
    T temp = heaparray[loc];
    heaparray[loc]=heaparray[((loc-1)/m)];
    heaparray[((loc-1)/m)] = temp;
    //trickle up
    trickleUp(((loc-1)/m));
  }
}
template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleDown(int loc)
{
  unsigned int child;
  //iterate through m
  for(unsigned int i =1; i<=m;i++){
    //left child
  child = m*loc+i;
  if(child<heaparray.size()){
    if(child+1<heaparray.size()){
      //compare values with l/r child
      if(this->c(heaparray[child+1],heaparray[child])){
        //right child
        child++;
      }
    }
    //compare parent and child
    if(this->c(heaparray[child],heaparray[loc])){
      //swap
      T temp = heaparray[child];
      heaparray[child]=heaparray[loc];
      heaparray[loc] = temp; 
      trickleDown(child);
    }
  }
}

}
template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  //push at end of array
  heaparray.push_back(item);
  trickleUp(heaparray.size()-1);
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  //check if it's empty
  if (heaparray.empty()){
    return true;
  }
  else{
    return false;
  }
}
// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  else{
    return heaparray[0];
  }
}

// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }
  else{
    //swap first and last
    T temp = heaparray[0];
    heaparray[0]=heaparray[heaparray.size()-1];
    heaparray[heaparray.size()-1] = temp;
    heaparray.pop_back();
    trickleDown(0);
  }

}

#endif

