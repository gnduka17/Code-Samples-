#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
template <
         typename T,
         typename TComparator = std::equal_to<T>,
         typename PComparator = std::less<double>,
         typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const TComparator& tcomp = TComparator()  );

    /// Destructor as needed
    ~Heap();

    /// Adds an item with the provided priority
    void push(double pri, const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey reduces the current priority of
    /// item to newpri, moving it up in the heap
    /// as appropriate.
    void decreaseKey(double newpri, const T& item);

private:
    /// Add whatever helper functions you need below
    void trickleUp(unsigned int loc);
    void trickleDown(unsigned int loc);
    void swap(unsigned int pos1, unsigned int pos2);

    // These should be all the data members you need.
    std::vector< std::pair<double, T> > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, TComparator> keyToLocation_;

};

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const TComparator& tcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, tcomp)

{

}

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::~Heap()
{

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::push(double priority, const T& item)
{
    // You complete.
    std::pair<double, T> input = std::make_pair(priority,item);
    //push at end of array
    store_.push_back(input);
    //index in map
    keyToLocation_[item]=store_.size()-1;
    trickleUp(store_.size()-1);

}
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::trickleUp(unsigned int loc)
{
  if(loc>0 && c_(store_[loc].first,store_[((loc-1)/m_)].first)){
    //swap with child and parent
   swap(loc, (loc-1)/m_);
    //trickle up
    trickleUp(((loc-1)/m_));
  }
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::decreaseKey(double priority, const T& item)
{
    //update vector->find item in map
    double atpriority = store_[keyToLocation_[item]].first;
    if(atpriority<=priority){
        return;
    }
    store_[keyToLocation_[item]]=std::make_pair(priority,item);
    trickleUp(keyToLocation_[item]);
    trickleDown(keyToLocation_[item]);

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
T const & Heap<T,TComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }
    else{
        return store_[0].second;
    }

}

/// Removes the top element
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::pop()
{
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }
     //swap first and last,remove last
    store_[0]=store_[store_.size()-1];
    keyToLocation_.erase(store_[store_.size()-1].second);
    store_.pop_back();
    trickleDown(0);
}
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::trickleDown(unsigned int loc)
{
    unsigned int child;
    for(unsigned int i =1; i<=m_;i++){
        child = m_*loc+i;
        if(child<store_.size()){
            if(child+1<store_.size()){
              if(this->c(store_[child+1].first,store_[child].first)){
                child++;
              }
            }
            if(this->c(store_[child].first,store_[loc].first)){
              swap(child,loc);
              trickleDown(child);
            }
        }
    }

}

/// returns true if the heap is empty
template <typename T, typename TComparator, typename PComparator, typename Hasher >
bool Heap<T,TComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::swap(unsigned int pos1, unsigned int pos2)
{
  
    //swap positiions
    std::pair<double,T> temp = store_[pos1];
    store_[pos1]=store_[pos2];
    store_[pos2] = temp;
    //update map
    keyToLocation_[store_[pos1].second]=pos1;
    keyToLocation_[store_[pos2].second]=pos2;
}


#endif

