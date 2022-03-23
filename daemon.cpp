#include <iostream>
#include <ostream>
#include <system_error>
#include <ctime>
#include <iterator>
#include <string>
#include <list>
#include <chrono>
#include <thread>

#include "Message.hpp"
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
  std::chrono::minutes appDur(0);

  auto update = [&] (std::chrono::minutes upVal) {
        sleepTime = std::chrono::duration_cast<std::chrono::milliseconds>(tasks.front()._dur() < upVal ? tasks.front()._dur() : upVal);
        if(sleepTime == upVal){
          state = state == STINT ? PAUSE : STINT;
          tasks.front().setDur(tasks.front()._dur() - upVal);
        }else {
          state = NONE;
          
        }
    };

  while(1){
  if (sleepTime > std::chrono::milliseconds(0)) std::this_thread::sleep_for(sleepTime);
  else {
    switch (state) {
      case(PAUSE):
        update(tasks.front()._stint());
      break;
      case(STINT):
        update(tasks.front()._pause());
      break;
      case(NONE):
      Task lastTask(tasks.front());
      tasks.pop_front();
        if(!tasks.empty()){
          state = STINT;
          sleepTime = std::chrono::duration_cast<std::chrono::milliseconds>(tasks.front()._tp() - (lastTask._tp() + lastTask._dur())); 
        } else return 1;
      break;
      }
    }
  }
  return 0;
}
