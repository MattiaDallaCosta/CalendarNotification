#include "Task.hpp"
#include "Message.hpp"
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <system_error>
#include <vector>

Task::Task(std::string _info, int _dur,
    int _stint, int _pause, int _cadence, std::string _head, std::string _com): message{_head, _com, STINT} {
  std::tm tm = {};
  strptime(_info.c_str(), "%b %d %Y %H:%M", &tm);
  this->tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
  this->dur = std::chrono::minutes(_dur);
  this->stint = std::chrono::minutes(_stint);
  this->pause = std::chrono::minutes(_pause);
  auto tp = std::chrono::system_clock::to_time_t(this->tp);
  auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::cout << "this.tp: " << std::ctime(&tp) << "\nnow: " << std::ctime(&now) << std::endl;
}

Task::Task(std::chrono::time_point<std::chrono::system_clock> _tp, int _dur,
    int _stint, int _pause, int _cadence, std::string _head, std::string _com): tp(_tp), message{_head, _com, STINT} {
  this->dur = std::chrono::minutes(_dur);
  this->stint = std::chrono::minutes(_stint);
  this->pause = std::chrono::minutes(_pause);
  auto tp = std::chrono::system_clock::to_time_t(this->tp);
  auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::cout << "this.tp: " << std::ctime(&tp) << "\nnow: " << std::ctime(&now) << std::endl;
}

Task::Task(std::string _info, int _dur,
    int _stint, int _pause): message{"Bella Li", "Sei un Champ", NONE} {
  std::tm tm = {};
  strptime(_info.c_str(), "%b %d %Y %H:%M", &tm);
  this->tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
  this->dur = std::chrono::minutes(_dur);
  this->stint = std::chrono::minutes(_stint);
  this->pause = std::chrono::minutes(_pause);
}

std::chrono::time_point<std::chrono::system_clock> Task::_tp(){
  return this->tp;
}

std::chrono::seconds Task::_dur() {
  return this->dur;
}

std::chrono::seconds Task::_stint() {
  return this->stint;
}

std::chrono::seconds Task::_pause() {
  return this->pause;
}

void Task::setDur(std::chrono::seconds s) {
  this->dur = s;
}

void Task::setState(State s) {
  this->message.state = s;
}

void Task::setTp(std::chrono::time_point<std::chrono::system_clock> _tp){
  this->tp = _tp;
}
  Message Task::_message(){
    return this->message;
  }

bool operator < (Task t1, Task t2){
    return (t1.tp < t2.tp);
}

std::ostream& operator << (std::ostream& os, const Task& t){
  auto time = std::chrono::system_clock::to_time_t(t.tp);
  char appo[32];
  std::strftime(appo, sizeof(appo), "%b %d %Y %H:%M", std::localtime(&time));
  std::string strTime(appo);
  strTime[strTime.size()] = '\0';
  os << "time point: " << strTime << "\nduration time: " << std::chrono::duration_cast<std::chrono::minutes>(t.dur).count() << "m\nstint time: " 
     << std::chrono::duration_cast<std::chrono::minutes>(t.stint).count() << "m\npause time: " << std::chrono::duration_cast<std::chrono::minutes>(t.pause).count()
     << "m\nMessage: " << t.message.header << " -=- " << t.message.comment << std::endl;
  return os;
}

Task &Task::operator=(const Task &t) {
  this->tp = t.tp;
  this->dur = t.dur;
  this->stint = t.stint;
  this->pause = t.pause;
  this->message = t.message;
  return *this;
}

Task::Task(const Task &t) {
  this->tp = t.tp;
  this->dur = t.dur;
  this->stint = t.stint;
  this->pause = t.pause;
  this->message = t.message;
}

