#include "Task.hpp"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

Task::Task(std::string _info, int _dur,
    int _stint, int _pause, std::string _head, std::string _com): message{_head, _com, }
{
  std::tm tm = {};
  strptime(_info.c_str(), "%a %b %d %H:%M:%S %Y", &tm);
  this->tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
  this->dur = std::chrono::minutes(_dur);
  this->stint = std::chrono::minutes(_stint);
  this->pause = std::chrono::minutes(_pause);
}

Task::Task(std::chrono::time_point<std::chrono::system_clock> _tp, int _dur,
    int _stint, int _pause, std::string _head, std::string _com):tp(_tp), message{_head, _com}
{
  this->dur = std::chrono::minutes(_dur);
  this->stint = std::chrono::minutes(_stint);
  this->pause = std::chrono::minutes(_pause);
}

inline std::chrono::time_point<std::chrono::system_clock> Task::_tp(){
  return this->tp;
}

inline std::chrono::minutes Task::_dur() {
  return this->dur;
}

inline std::chrono::minutes Task::_stint() {
  return this->stint;
}

inline std::chrono::minutes Task::_pause() {
  return this->pause;
}

inline void Task::setDur(std::chrono::minutes m) {
  this->dur = m;
}

inline bool operator < (Task t1, Task t2){
    return (t1.tp < t2.tp);
}

std::ostream& operator << (std::ostream& os, const Task& t){
  auto time = std::chrono::system_clock::to_time_t(t.tp);
  std::string strTime = std::ctime(&time);
  strTime[strTime.size() - 1] = '\0';
  os << "time point: " << strTime << "\nduration time: " << t.dur.count() << " min\nstint time: " 
     << t.stint.count() << " min\npause time: " << t.pause.count() << " min\nMessage: " << t.message.header << " -=- " << t.message.comment << std::endl;
  return os;
}

