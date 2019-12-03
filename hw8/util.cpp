#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    set<std::string> keywords;
    string word = "";
    rawWords=convToLower(rawWords);
    for(unsigned int i=0;i<rawWords.size();i++){
        char c = rawWords[i];
        //if letter then put in word
        if(isalpha(c)||isdigit(c)){
            word=word+rawWords[i];
        }
        //if punct then insert word if 2 and more
        else if(ispunct(c)){
            if(word.size()>=2){
                keywords.insert(word);
                word="";
            }
            else{
                word="";
            }
        }
        else{
            //if word is greater than 2 then insert
            if(word.size()>=2){
                keywords.insert(word);
                word="";
            }
            else{
                word="";
            }
        }
    }
    if(word.size() >= 2){
        keywords.insert(word);
    }
    return keywords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
