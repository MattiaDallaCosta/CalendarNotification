#include <iostream>
#include <ostream>
#include <system_error>
#include <ctime>
#include <iterator>
#include <string>
#include <list>
#include <chrono>
#include <thread>

#include "Task.hpp"
#include "MyUtils.hpp"

std::string file = "/home/mattia/.config/noteCalendar/config";

int main (int argc, char ** argv)
{
  auto now = std::chrono::system_clock::now();
  Task start(now, 0, 0, 0, "", "");
  std::list<Task> tasks;

  readConfig(tasks, file);
  return 0;
}
