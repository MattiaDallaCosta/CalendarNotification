#include "Task.hpp"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/regex/v5/regex_fwd.hpp>

Task::Task(std::string _info, int _dur,
    int _stint, int _pause, std::string _head, std::string _com): header(_head), comment(_com)
{
  std::tm tm = {};
  std::cout << _info << std::endl;
  strptime(_info.c_str(), "%a %b %d %H:%M:%S %Y", &tm);
  this->tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
  this->dur = std::chrono::duration<int,std::ratio<60,1>>(_dur);
  this->stint = std::chrono::duration<int,std::ratio<60,1>>(_stint);
  this->pause = std::chrono::duration<int,std::ratio<60,1>>(_pause);
}

Task::Task(std::chrono::time_point<std::chrono::system_clock> _tp, int _dur,
    int _stint, int _pause, std::string _head, std::string _com):tp(_tp), header(_head), comment(_com)
{
  this->dur = std::chrono::duration<int,std::ratio<60,1>>(_dur);
  this->stint = std::chrono::duration<int,std::ratio<60,1>>(_stint);
  this->pause = std::chrono::duration<int,std::ratio<60,1>>(_pause);
}

inline bool operator < (Task t1, Task t2){
    return (t1.tp < t2.tp);
}

std::ostream& operator << (std::ostream& os, const Task& t){
  auto time = std::chrono::system_clock::to_time_t(t.tp);
  os << std::ctime(&time) << std::endl;   
  auto durtime = std::chrono::system_clock::to_time_t(t.tp + t.dur);
  os << std::ctime(&durtime) << std::endl;   
  auto stinttime = std::chrono::system_clock::to_time_t(t.tp + t.stint);
  std::cout << std::ctime(&stinttime) << std::endl;   
  auto stoptime = std::chrono::system_clock::to_time_t(t.tp + t.pause);
  os << std::ctime(&stoptime) << std::endl;   
  os << t.header << "\n" << t.comment << std::endl;
  return os;
}
