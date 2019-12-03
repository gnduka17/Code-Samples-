#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "ulliststr.h"
using namespace std;



ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(NULL == ptr){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(NULL == ptr){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(NULL == ptr){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

 // pushes val to front of array and back of list
void ULListStr::push_back(const std::string& val){
  //if head is null create a new item then set val to the beginning of array
  if(head_==NULL&&tail_==NULL){
    Item* node = new Item();
    node->val[0]=val;
    size_++;
    node->first = 0;
    node->last = 1;
    head_=node;
    tail_=node;
    return;
  }
  //if last is occupied then create a new array make that the new tail
  if(tail_->last==10){
    Item* node2 = new Item();
    node2->val[0]=val;
    tail_->next=node2;
    node2->prev = tail_;
    tail_=node2;
    size_++;
    node2->first=0;
    node2->last=1;
    return;
  }
  //if theres space then insert
  if(tail_->last<10){
    tail_->val[tail_->last]=val;
    tail_->last = tail_->last+1;
    size_++;
    return;
  }

}
//push val to back of array and front of list
void ULListStr::push_front(const std::string& val){
  //if head is null create a new item then set val to the end of array
  if(head_==NULL &&tail_==NULL){
    Item* node2=new Item();
    size_++;
    node2->val[9]=val;
    node2->first=9;
    node2->last = 10;
    head_=node2;
    tail_=node2;
    return;
  }
  //if first is occupied then create a new array make that the new tail
  if(head_->first==0){
    Item* node3 = new Item();
    size_++;
    node3->val[9]=val;
    node3->first=9;
    node3->last = 10;
    head_->prev=node3;
    node3->next=head_;
    head_=node3;
    return;
  }
  //if theres space then insert
  if(head_->first>0){
    head_->val[head_->first-1]=val;
    head_->first=head_->first-1;
    size_++;
    return;
  }

}
//pop back removes last element
void ULListStr::pop_back(){
  if(head_==NULL){
    return;
  }
  if(tail_==NULL){
    return;
  }
  //set last element to empty and update tail last
  tail_->val[tail_->last-1]="\0";
  tail_->last=tail_->last-1;
  size_--;
  //if theres nothing in the item then delete then change tail;
  if(tail_->last==tail_->first){
    //if tail is the only item then delete
    if(tail_->prev==NULL){
      delete tail_;
      tail_=NULL;
      head_=NULL;
    }
    else{
      tail_->prev->next=NULL;
      Item* temp = NULL;
      temp=tail_;
      tail_=tail_->prev;
      delete temp;
    }
    
  }
  return;
}
//removes front element
void ULListStr::pop_front(){
  if(head_==NULL){
    return;
  }
  if(tail_==NULL){
    return;
  }
  //set frist element to empty and update head first
  head_->val[head_->first]="\0";
  size_--;
  head_->first=head_->first+1;
  //if empty item then delete then change head
  if(head_->first==head_->last){
    if(head_->next==NULL){
      delete head_;
      tail_=NULL;
      head_=NULL;
    }
    else{
      head_->next->prev=NULL;
      Item* temp1 = NULL;
      temp1 = head_;
      head_=head_->next;
      delete temp1;
    }
   
  }
  return;
}
//returns back element
std::string const & ULListStr::back() const{
 
  return tail_->val[tail_->last-1];
}

//returns front element
std::string const & ULListStr::front() const{
  
  return head_->val[head_->first];
}

//returns pointer to val of loc
std::string* ULListStr::getValAtLoc(size_t loc) const{
  //if loc is not in range then return null
  if(loc<0){
    return NULL;
  }
  if(loc>=size_){
    return NULL;
  }
  Item* temp=head_;
  size_t loctemp=loc;
  size_t number = 0;
  string* ptr = NULL;

  //iterate through the items
  while(temp!=NULL){
    //number keeps track of total elements (elements before temp and in temp)
    number=number+(temp->last-temp->first);
    //if number is less then loc then loc is not in temp so move to next item
    if(number<=loc){
      //loctemp is changed and keeps track 
      loctemp=loctemp-(temp->last-temp->first);
      temp = temp->next;
    }
    else{
      //loc is in this temp
      ptr=&(temp->val[temp->first+loctemp]);
       return ptr;
    }
  }
  return NULL;
 
 

  

}



