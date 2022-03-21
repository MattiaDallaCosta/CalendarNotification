#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <ctime>
#include <iterator>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/regex/v5/regex_fwd.hpp>
#include "Task.hpp"

std::string file = "/home/mattia/.config/noteCalendar/config";

int main (int argc, char ** argv)
{
  auto start = std::time(0);
  auto timeChr = std::ctime(&start);
  Task init(timeChr, 0, 0, 0, "", "");
  std::vector<Task> tasks;
  int fd;
  char c;
  int i = 0;
  std::vector<std::string> inputs;
  if(!(fd = open(file.c_str(), O_RDWR, 0666))){
    std::cerr << "didn't open file" << std::endl;
    return 1;
  }
  do {
  if(read(fd, &c, 1) > 0) {
    if (c == '\n') i++;
    else{
      inputs[i].push_back(c);
    }
  } else break;
  }while (c != '\n' && c != '\0');
  return 0;
}
