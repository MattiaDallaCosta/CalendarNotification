#pragma once
#include <memory>
#include <string>

typedef struct {
  int day;
  int month;
  int year;
} orderDate;

class Task
{
private:
  std::string date;
  std::string day;
  std::string time;
  int duration;
  int stint;
  int pause;
  std::string header;
  std::string comment;
  orderDate getOrdering();
public:
  Task(std::string, int, int, int, std::string, std::string);
  Task(Task &&) = default;
  Task(const Task &) = default;
  Task &operator=(Task &&) = default;
  Task &operator=(const Task &) = default;
  ~Task() = default;
  friend bool operator<(Task, Task);
};

bool operator<(Task, Task);
