#include <csignal>
#include <cstddef>
#include <cstdio>
#include <fcntl.h>
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
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/wait.h>

#include "Message.hpp"
#include "Task.hpp"
#include "MyUtils.hpp"

std::string file = "/home/mattia/.config/noteCalendar/config";
std::string Qfile = "/tmp/noteCalendar";
int Qnum = 1;
State state = NONE;

int main (int argc, char ** argv)
{
  std::cout << "start\n";
  auto now = std::chrono::system_clock::now();
  Task start(now,0,0,0,"", "");
  std::cout << start << std::endl;
  std::list<Task> tasks;
  readConfig(tasks, file);
  for (auto t : tasks) std::cout << t << std::endl;
  
  remove(Qfile.c_str());
  key_t k = ftok(Qfile.c_str(), Qnum);
  creat(Qfile.c_str(), 0666);
  k = ftok(Qfile.c_str(), Qnum);
  int qId = msgget(k, 0666 | IPC_CREAT);
  qId = msgget(k, 0666);
  
  std::chrono::milliseconds sleepTime(0);
  if (!tasks.empty()) {
    if (now < tasks.front()._tp()) sleepTime = std::chrono::duration_cast<std::chrono::milliseconds>((tasks.front()._tp() - now));
    else {
      tasks.front().setDur(std::chrono::duration_cast<std::chrono::seconds>(tasks.front()._dur() + (tasks.front()._tp() - now)));
      tasks.front().setTp(now);
      sleepTime = std::chrono::duration_cast<std::chrono::milliseconds>((tasks.front()._tp() - now + tasks.front()._stint()));
      state = STINT;
    }
  }
  std::chrono::seconds appDur = tasks.front()._dur();
  Task lastTask(now, 0, 0, 0, "", "");

  while(1){
  if (sleepTime > std::chrono::milliseconds(0)) {
    if(!fork()){
      std::string QnumS = std::to_string(Qnum);
      char ** argV = {};
      execlp("./sender", "./sender", Qfile.c_str(), std::to_string(Qnum).c_str(),  NULL);
    } else {
      Message appm = tasks.front()._message();
      msg app;
      app.msg(appm, 1);
      msgsnd(qId, &app, sizeof(Message), 0);
    }
    usleep(std::chrono::duration_cast<std::chrono::microseconds>(sleepTime).count());
    while(wait(NULL) > 0);
    sleepTime = std::chrono::milliseconds(0);
  } else {
    switch (state) {
      case(PAUSE):
        sleepTime = std::chrono::duration_cast<std::chrono::milliseconds>(appDur < tasks.front()._stint() ? appDur : tasks.front()._stint());
        if(sleepTime == tasks.front()._stint()){
          state = STINT;
          tasks.front().setState(STINT);
          appDur = appDur - tasks.front()._stint();
        } else {
            if(!tasks.empty()) {
              lastTask  = tasks.front();
              tasks.pop_front();
              state = NONE; 
            }
        }
        std::cout << "Post Pause update\n";
      break;
      case(STINT):
        sleepTime = std::chrono::duration_cast<std::chrono::milliseconds>(appDur < tasks.front()._pause() ? appDur : tasks.front()._pause());
        if(sleepTime == tasks.front()._pause()){
          state = PAUSE;
          tasks.front().setState(PAUSE);
          appDur = appDur - tasks.front()._pause();
        } else {
            if(!tasks.empty()) {
              lastTask  = tasks.front();
              tasks.pop_front();
              state = NONE; 
            }
          }
        std::cout << "Post Stint update\n";
      break;
      case(NONE):
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
