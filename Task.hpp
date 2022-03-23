#pragma once
#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include "Message.hpp"

class Task
{
private:
  std::chrono::time_point<std::chrono::system_clock> tp;
  std::chrono::minutes dur, stint, pause;
  Message message;
public:
  Task(std::string, int, int, int, std::string, std::string);
  Task(std::chrono::time_point<std::chrono::system_clock>, int, int, int, std::string, std::string);
  Task(Task &&) = default;
  Task(const Task &) = default;
  Task &operator=(Task &&) = default;
  Task &operator=(const Task &) = default;
  ~Task() = default;
  friend bool operator<(Task, Task);
  friend std::ostream& operator << (std::ostream& os, const Task& t);
  std::chrono::time_point<std::chrono::system_clock> _tp();
  std::chrono::minutes _dur();
  std::chrono::minutes _stint();
  std::chrono::minutes _pause();
  void setDur(std::chrono::minutes);
  void setState(State);
  void setTp(std::chrono::time_point<std::chrono::system_clock>);

};

bool operator < (Task, Task);
std::ostream operator << (Task t, std::ostream os);
