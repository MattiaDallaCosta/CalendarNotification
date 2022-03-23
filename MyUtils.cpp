#include "MyUtils.hpp"
#include <string>

void readConfig(std::list<Task> &list, std::string _file) {
  int fd;
  char c;
  int i = 0;
  int count = 0;
  strTask app = { .array = {"", "", "", "", "", ""}};
  if(!(fd = open(_file.c_str(), O_RDWR, 0666))){
    std::cerr << "didn't open file" << std::endl;
    exit(1);
  }
  do {
    if (c == '\n' || c == '\0') {
      list.insert(list.end(), Task(app.array[0], std::atoi(app.array[1].c_str()), std::atoi(app.array[2].c_str()), std::atoi(app.array[3].c_str()), app.array[4], app.array[5]));
      count = 0;
      for(auto &s:app.array){
        s = "";
      };
    }
    else{
      if(c == ' ') {
        if(count++ < 4) app.array[0].push_back(' ');
      } else app.array[count - 4 < 0 ? 0 : count - 4].push_back(c);
    }
  }while (read(fd, &c, 1) > 0);
  list.pop_front();
}
