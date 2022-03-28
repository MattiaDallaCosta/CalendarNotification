#include "MyUtils.hpp"
#include "Task.hpp"
#include <chrono>
#include <iostream>
#include <ostream>
#include <string>

void readConfig(std::list<Task> &list, std::string _file) {
  int fd;
  char c;
  int i = 0;
  int count = 0;
  strTask app = { .array = {"", "", "", "", ""}};
  if(!(fd = open(_file.c_str(), O_RDWR, 0666))){
    std::cerr << "didn't open file" << std::endl;
    exit(1);
  }
  read(fd, &c, 1);
  do {
    if (c == '\n' || c == '\0') {
      Task created(app.array[0], std::atoi(app.array[1].c_str()), std::atoi(app.array[2].c_str()), 
          std::atoi(app.array[3].c_str()), NEVER,strToHeader(app.array[4]),strToComment(app.array[4]));
      auto now = std::chrono::system_clock::now();
      std::cout << "Is too old? " << (now > (created._tp() + created._dur()) ? "yes" : "no") << std::endl;
      if(now > (created._tp() + created._dur()));
      else {
        std::cout << "New Begin? " << (now > (created._tp()) ? "yes" : "no") << std::endl;
        if(now > created._tp()){
          created.setDur(std::chrono::duration_cast<std::chrono::seconds>((created._tp() - now + created._dur())));
          created.setTp(now);
        }
        std::cout << "Created:\n" << created << std::endl;
        list.insert(list.end(), created);
      }
      count = 0;
      for(auto &s:app.array){
        s = "";
      };
    }
    else if(c >= 32 && c <= 126){
      if(c == ' ') {
        if(count++ < 3) app.array[0].push_back(' ');
        if(count > 6) app.array[4].push_back(' ');
      } else {
          app.array[count - 3 < 0 ? 0 : count - 3 > 4 ? 4 : count - 3].push_back(c);
      }
    }
  }while (read(fd, &c, 1) > 0);
}

std::string strToHeader(std::string str){
  int begin = str.find("Header:(") + std::string("Header:(").length();
  int end = str.find(")",begin);
return str.substr(begin, end - begin);
}

std::string strToComment(std::string str){
  int begin = str.find("Comment:(") + std::string("Comment:(").length();
  int end = str.find(")", begin);
return str.substr(begin, end - begin);
}
