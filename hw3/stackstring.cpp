#include "stackstring.h"
#include <iostream>

StackString::StackString(){

}

StackString::~StackString(){

}
bool StackString::empty() const{
	if(list_.empty()){
		return true;
	}
	else{
		return false;
	}

}
size_t StackString::size() const{
	return list_.size();

}
void StackString::push(const std::string& val){
	list_.push_back(val);

}
const std::string& StackString::top() const{
	return list_.back();
}

void StackString::pop(){
	if(empty()){
		return;
	}
	else{
		list_.pop_back();
	}

}