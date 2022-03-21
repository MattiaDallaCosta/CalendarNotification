#include "Task.hpp"
#include <cstdlib>
#include <vector>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/regex/v5/regex_fwd.hpp>

Task::Task(std::string _info, int _dur,
    int _stint, int _pause, std::string _head, std::string _com): duration(_dur), stint(_stint), header(_head), comment(_com)
{
  std::vector<std::string> elements;
  _info.erase(std::remove(_info.begin(), _info.end(), '\n'), _info.end());
  boost::split_regex(elements, _info, boost::regex(" "));
  this->day = elements[0];
  this->date = elements[1] + " " + elements[2] + " " + elements[4];
  this->time = elements[3];
}

bool operator<(Task t1, Task t2){
    auto od1 = t1.getOrdering();
    auto od2 = t2.getOrdering();
    if(od1.year < od2.year) return true;
    if(od1.month < od2.month && od1.year == od2.year) return true;
    if(od1.day < od2.day && od1.month == od2.month && od1.year == od2.year) return true;
    if(od1.day == od2.day && od1.month == od2.month && od1.year == od2.year) return true;
  return false;
}

orderDate Task::getOrdering(){
  orderDate od;
  std::vector<std::string> vec;
  boost::split_regex(vec, this->date, boost::regex(" "));
  od.day = std::atoi(vec[1].c_str());
  od.year = std::atoi(vec[2].c_str());
  od.month = -1;
    if (vec[0] == "Gen") od.month = 0;
    else if(vec[0] == "Feb") od.month = 1;
    else if(vec[0] == "Mar") od.month = 2;
    else if(vec[0] == "Apr") od.month = 3;
    else if(vec[0] == "May") od.month = 4;
    else if(vec[0] == "Jun") od.month = 5;
    else if(vec[0] == "Jul") od.month = 6;
    else if(vec[0] == "Aug") od.month = 7;
    else if(vec[0] == "Sep") od.month = 8;
    else if(vec[0] == "Oct") od.month = 9;
    else if(vec[0] == "Nov") od.month = 10;
    else if(vec[0] == "Dec") od.month = 11;
  return od;
};
