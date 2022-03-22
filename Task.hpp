#pragma once
#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>

class Task
{
private:
  std::chrono::time_point<std::chrono::system_clock> tp;
  std::string date;
  std::string day;
  std::string time;
  std::chrono::duration<int,std::ratio<60,1>> dur, stint, pause;
  std::string header;
  std::string comment;
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
};

bool operator < (Task, Task);
std::ostream operator << (Task t, std::ostream os);
