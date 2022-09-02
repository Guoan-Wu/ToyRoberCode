#pragma once
#include <string>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
class MyString
{
private:
    /* data */
public:
    MyString(/* args */){}
    ~MyString(){}

    static bool isNumber(const string& s){
        if(s.empty()) return false;
        auto iter = find_if(s.cbegin(),s.cend(),[](const unsigned char& c) {return !isdigit(c);});
        return iter == s.cend();
    }
    static vector<string> split(const string& cmd, string delimiter){
    vector<string> result;
    if(cmd.length() ==0 || delimiter.length()==0)
        return result;

    size_t pos =0,prevPos=0;
    string item;
    pos = cmd.find(delimiter,prevPos);
    while(pos!= string::npos){
        item = cmd.substr(prevPos,pos-prevPos);
        result.push_back(item);
        pos += delimiter.length();
        prevPos = pos;
        pos = cmd.find(delimiter,pos);
    }
    item = cmd.substr(prevPos,cmd.length()-prevPos+1);
    result.push_back(item);

    return result;
}
};

