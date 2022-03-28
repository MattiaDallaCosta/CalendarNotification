#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include "Message.hpp"
#include "Task.hpp"

void createTask(void);
void operations(std::vector<std::string>);
void listTasks(std::vector<std::string>);
void timer(std::vector<std::string>);
void helper(void);
bool running = true;

std::vector<Task> tasks;
int qId;

int main (int argc, char ** argv) {

  std::vector<std::string> comm;
  if (argc > 1) {
    for (int i = 1; i < argc; i++) comm.push_back(std::string(argv[i]));
    operations(comm);
  }
  key_t k = ftok("/tmp/noteCalendar", 1);
  qId = msgget(k, 0666);
  while (running) {
    std::string input;
    std::cout << ">";
    while(std::cin >> input) comm.push_back(input);
    operations(comm);
  }
  return 0;
}

void createTask(void) {
  std::string date, header, comment, dur, stint, stop, cadc;
  msg snd;
  snd.Op("create", 2);
  msgsnd(qId, &snd, msgSIZE, 0);
  std::cout << "date of the new task[format: Mmm dd yyyy hh:mm]: ";
  std::cin >> date; 
  std::cout << "duration of the new task: ";
  std::cin >> dur; 
  std::cout << "stint of the new task: ";
  std::cin >> stint; 
  std::cout << "pause of the new task: ";
  std::cin >> stop; 
  std::cout << "cadence of the new task: ";
  std::cin >> cadc; 
  std::cout << "header of the new task: ";
  std::cin >> header; 
  std::cout << "comment of the new task: ";
  std::cin >> comment; 
  std::string body = "date:(" + date + ") " + dur + " " + stint + " " + stop + " " + cadc + " Header:(" + header + ") Comment: " + comment + ")";
  snd.Op(body, 3);
  msgsnd(qId, &snd, msgSIZE, 0);
}

void listTasks(std::vector<std::string> vec){
    msg snd;
    snd.Op("list", 2);
    msgsnd(qId, &snd, msgSIZE, 0);
  if(vec[1] != ""){
    snd.Op(vec[2], 2);
    msgsnd(qId, &snd, msgSIZE, 0);
  } else {
    std::string input;
    std::cout << "for wich period?{day, week}";
    std::cin >> input;
    snd.Op(input, 2);
    msgsnd(qId, &snd, msgSIZE, 0);
  }

  //while(msgrcv(qId, &rcv, msgSIZE, 3, 0)>0) tasks.;
}

void timer(std::vector<std::string> vec){
    msg snd;
    snd.Op("timer", 2);
  if(vec[1] != ""){
    snd.Op(vec[2], 2);
    msgsnd(qId, &snd, msgSIZE, 0);
  } else {
    std::string input;
    std::cout << "length of the timer: ";
    std::cin >> input;
    std::string out = input + " Header:(";
    std::cout << "header the timer: ";
    std::cin >> input;
    out += input + ") Comment:(";
    std::cout << "comment the timer: ";
    std::cin >> input;
    out += input + ")";
    snd.Op(out, 2);
    msgsnd(qId, &snd, msgSIZE, 0);
  }
}

void helper(void){
  std::cout << "Usage: notecal-cli <option> [args]\n";
  std::cout << "Options:\n create-task: creates a task\n list-tasks: lists the tasks [possible args: day, week]\n timer: sets a timer";
  std::cout << "\n help: shows this help message\n";
}

void operations(std::vector<std::string> params){
    if (std::string(params[0]) == "exit") running = false;
    if (std::string(params[0]) == "create-task") createTask();
    if (std::string(params[0]) == "list-tasks") listTasks(params);
    if (std::string(params[0]) == "timer") timer(params);
    if (std::string(params[0]) == "help") helper();
}

