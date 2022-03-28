#include <csignal>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <memory>
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

void cliOperations(std::list<Task>);
void createTask(std::list<Task>);
void listTasks(std::list<Task>);
void timer(void);
void time(int,std::string,std::string);

std::string file = "/home/mattia/.config/noteCalendar/config";
std::string Qfile = "/tmp/noteCalendar";
int Qnum = 1;
int qId;
State state = NONE;

int main (int argc, char ** argv)
{
  std::list<Task> tasks;
  readConfig(tasks, file);
  for (auto t : tasks) std::cout << t << std::endl;
  
  remove(Qfile.c_str());
  key_t k = ftok(Qfile.c_str(), Qnum);
  creat(Qfile.c_str(), 0666);
  k = ftok(Qfile.c_str(), Qnum);
  qId = msgget(k, 0666 | IPC_CREAT);
  qId = msgget(k, 0666);

  auto now = std::chrono::system_clock::now();
  std::chrono::milliseconds sleepTime(0);
  std::chrono::seconds appDur = tasks.front()._dur();
  Task lastTask(now, 0, 0, 0, NEVER, "", "");

  std::thread cliReader(cliOperations, tasks);
  cliReader.detach();

  while(1){
  if (sleepTime > std::chrono::milliseconds(0)) {
    if (state != NONE) {
      if(!fork()){
        std::string QnumS = std::to_string(Qnum);
        char ** argV = {};
        execlp("./sender", "./sender", Qfile.c_str(), std::to_string(Qnum).c_str(),  NULL);
      } else {
        Message appm = tasks.front()._message();
        msg app;
        app.msg(appm, 1);
        msgsnd(qId, &app, msgSIZE, 0);
      }
    }
    while(wait(NULL) > 0);
    usleep(std::chrono::duration_cast<std::chrono::microseconds>(sleepTime).count());
    sleepTime = std::chrono::milliseconds(0);
  } else {
    now = std::chrono::system_clock::now();
    auto subval = std::chrono::duration_cast<std::chrono::seconds>(now - tasks.front()._tp());
    appDur = appDur < (tasks.front()._dur() - subval) ? appDur : tasks.front()._dur() - subval;
    state = (tasks.front()._tp() - now).count() > 0 ? NONE : (((tasks.front()._dur() - appDur).count()%(tasks.front()._stint() + tasks.front()._pause()).count()) < tasks.front()._stint().count() ? STINT : PAUSE);
    tasks.front().setState(state);
    switch (state) {
      case(NONE):
          if(!tasks.empty()){
            sleepTime = std::chrono::duration_cast<std::chrono::milliseconds>(tasks.front()._tp() - (lastTask._tp() + lastTask._dur())); 
            //TODO: endless check
          } else return 1;
      break;
      default:
        auto length = state == STINT ? tasks.front()._stint() : tasks.front()._pause();
        sleepTime = std::chrono::duration_cast<std::chrono::milliseconds>(appDur < length ? appDur : length);
        if(sleepTime == appDur) {
            if(!tasks.empty()) {
              lastTask  = tasks.front();
              tasks.pop_front();
            }
        }
        std::cout << (state == PAUSE ? "Pause" : "Stint") << " update\n";
      }
    }
  }
  return 0;
}

void cliOperations(std::list<Task> list){
  msg op;
  msgrcv(qId, &op, msgSIZE, 2, 0);
  std::string operation = op.getOp();
  if (operation == "create") createTask(list);
  if (operation == "list") listTasks(list);
  if (operation == "timer") timer();
}

void createTask(std::list<Task> list){
  msg op;
  msgrcv(qId, &op, msgSIZE, 2, 0);
  std::string str = op.getOp();
  int begin = str.find("date:(") + std::string("date:(").length();
  int end = str.find(")",begin);
  std::string date = str.substr(begin,end - begin);
  begin = end;
  end = str.find(" ",begin);
  int dur = atoi(str.substr(begin,end - begin).c_str());
  begin = end;
  end = str.find(" ",begin);
  int stint = atoi(str.substr(begin,end - begin).c_str());
  begin = end;
  end = str.find(" ",begin);
  int pause = atoi(str.substr(begin,end - begin).c_str());
  begin = end;
  end = str.find(" ",begin);
  int cadence = atoi(str.substr(begin,end - begin).c_str());
  begin = str.find("Header:(") + std::string("Header:(").length();
  end = str.find(")",begin);
  std::string header = str.substr(begin,end - begin);
  begin = str.find("Comment:(") + std::string("Comment:(").length();
  end = str.find(")",begin);
  std::string comment = str.substr(begin,end - begin);
  list.insert(list.end(), Task(date, dur, stint, pause, cadence, header, comment));
}

void listTasks(std::list<Task> list){
  msg send;
  for (auto t : list) {
  }
}

void timer(void) {
  msg op;
  msgrcv(qId, &op, msgSIZE, 2, 0);
  std::string str = op.getOp();
  int begin = 0;
  int end = str.find(" ",begin);
  std::string length = str.substr(begin, end - begin).c_str();
  std::chrono::milliseconds len = std::chrono::minutes(atoi(length.substr(0,length.find(":")).c_str())) + std::chrono::seconds(atoi(length.substr(length.find(":"),).c_str()));
  
  begin = str.find("Header:(") + std::string("Header:(").length();
  end = str.find(")",begin);
  std::string header = str.substr(begin,end - begin);
  begin = str.find("Comment:(") + std::string("Comment:(").length();
  end = str.find(")",begin);
  std::string comment = str.substr(begin,end - begin);

  std::thread t(time, );
  t.detach();
}

void time(int ms, std::string header, std::string comment){
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));

}
