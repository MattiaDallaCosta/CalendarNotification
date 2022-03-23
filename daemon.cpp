#include <iostream>
#include <ostream>
#include <system_error>
#include <ctime>
#include <iterator>
#include <string>
#include <list>
#include <chrono>
#include <thread>
#include <unistd.h>

#include "Message.hpp"
#include "Task.hpp"
#include "MyUtils.hpp"

std::string file = "/home/mattia/.config/noteCalendar/config";
State state = NONE;

int main (int argc, char ** argv)
{
  auto now = std::chrono::system_clock::now();
  Task start(now,0,0,0,"", "");
  std::list<Task> tasks;

  readConfig(tasks, file);
  
  for (auto t:tasks) {
    std::cout << t;
  }
  std::cout << std::endl;

  std::chrono::milliseconds sleepTime = std::chrono::duration_cast<std::chrono::milliseconds>(tasks.front()._tp() - now);
  std::chrono::minutes appDur = tasks.front()._dur();
  std::cout << start;
  auto update = [&] (std::chrono::minutes upVal) {
        sleepTime = std::chrono::duration_cast<std::chrono::milliseconds>(appDur < upVal ? appDur : upVal);
        if(sleepTime == upVal){
          tasks.front().setState(state == STINT ? PAUSE : STINT);
          std::cout << "bella" << std::endl;
          appDur = appDur - upVal;
          if((fork() == 0)){
            //exec
          }
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
          appDur = tasks.front()._dur();
          sleepTime = std::chrono::duration_cast<std::chrono::milliseconds>(tasks.front()._tp() - (lastTask._tp() + lastTask._dur())); 
        } else return 1;
      break;
      }
    }
  }
  return 0;
}
