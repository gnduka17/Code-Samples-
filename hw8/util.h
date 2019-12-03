#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	std::set<T> keywords;
	if(s1.empty()){
		return s1;
	}
	if(s2.empty()){
		return s2;
	}
	else{
		//if the same then put into a set then output
		for(typename std::set<T>::iterator itr = s1.begin(); itr !=s1.end(); ++itr){
			if(s2.find(*itr)!=s2.end()){
				keywords.insert(*itr);
			}
		}
		return keywords;
	}
	return keywords;
	

}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
	if(s1.empty()){
		return s2;
	}
	else if(s2.empty()){
		return s1;
	}
	else{
		std::set<T> keywords;
		//put all of set in keywords
		for(typename std::set<T>::iterator itr = s1.begin(); itr !=s1.end(); ++itr){
			keywords.insert(*itr);
		}
		//put all in keywords
		for(typename std::set<T>::iterator it = s2.begin(); it !=s2.end(); ++it){
			keywords.insert(*it);
		}
		return keywords;
	}
	
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
