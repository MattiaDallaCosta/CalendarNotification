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
State state = NONE;

int main (int argc, char ** argv)
{
  auto now = std::chrono::system_clock::now();
  std::list<Task> tasks;

  readConfig(tasks, file);
  
  for (auto t:tasks) {
    std::cout << t;
  }
  std::cout << std::endl;

  std::chrono::milliseconds sleepTime = std::chrono::duration_cast<std::chrono::milliseconds>(tasks.front()._tp() - now);

  while(1){
  if (sleepTime > std::chrono::milliseconds(0)) std::this_thread::sleep_for(sleepTime);
  else {
    switch (state) {
      case(PAUSE):
        sleepTime = std::chrono::duration_cast<std::chrono::milliseconds>(tasks.front()._dur() < tasks.front()._stint() ? tasks.front()._dur() : tasks.front()._stint());
        if(sleepTime == tasks.front()._stint()){
          state = STINT;
          tasks.front().setDur(tasks.front()._dur() - tasks.front()._stint());
        }else {
          state = NONE;
          tasks.pop_front();
        }
      break;
      case(STINT):
        sleepTime = std::chrono::duration_cast<std::chrono::milliseconds>(tasks.front()._dur() < tasks.front()._stint() ? tasks.front()._dur() : tasks.front()._stint());
        if(sleepTime == tasks.front()._stint()){
          state = STINT;
          tasks.front().setDur(tasks.front()._dur() - tasks.front()._stint());
        }else {
          state = NONE;
          tasks.pop_front();
        }
      break;
      case(NONE):
        if(!tasks.empty()){

        } else return 1;
      break;
      }
    }
  }
  return 0;
}
