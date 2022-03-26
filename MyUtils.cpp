#include "MyUtils.hpp"
#include <chrono>
#include <iostream>
#include <string>

void readConfig(std::list<Task> &list, std::string _file) {
  int fd;
  char c;
  int i = 0;
  int count = 0;
  std::cout << "pre strTask\n";
  strTask app = { .array = {"", "", "", "", ""}};
  if(!(fd = open(_file.c_str(), O_RDWR, 0666))){
    std::cerr << "didn't open file" << std::endl;
    exit(1);
  }
  do {
    if (c == '\n' || c == '\0') {
      std::cout << "Pre Alloc\n";
      Task created(app.array[0], std::atoi(app.array[1].c_str()), std::atoi(app.array[2].c_str()), 
          std::atoi(app.array[3].c_str()), strToHeader(app.array[4]), strToComment(app.array[4]));
      auto now = std::chrono::system_clock::now();
      if(now > (created._tp() + created._dur()));
      else {
        if(now > created._tp()){
          created.setDur(std::chrono::duration_cast<std::chrono::minutes>((now - created._tp() + created._dur())));
          created.setTp(now);
        }
        list.insert(list.end(), created);
      }
      count = 0;
      for(auto &s:app.array){
        s = "";
      };
    }
    else{
      if(c == ' ') {
        if(count++ < 3) app.array[0].push_back(' ');
        if(count > 6) app.array[4].push_back(' ');
      } else {
          std::cout << "insert " << count << std::endl;
          app.array[count - 3 < 0 ? 0 : count - 3 > 4 ? 4 : count - 3].push_back(c);
      }
    }
  }while (read(fd, &c, 1) > 0);
}

std::string strToHeader(std::string str){
  std::cout << "Header begin and end\n";
  int begin = str.find("Header:\(");
  int end = str.find("\)",begin);
  std::cout << "Return Header\n";
return str.substr(begin, end - begin);
}

std::string strToComment(std::string str){
  std::cout << "Comment begin and end\n";
  int begin = str.find("Comment:\(");
  int end = str.find("\)", begin);
  std::cout << "Return Comment\n";
return str.substr(begin, end - begin);
}
