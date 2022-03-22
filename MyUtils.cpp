#include "MyUtils.hpp"
#include <string>

std::string strTask[6];

void readConfig(std::list<Task> list, std::string _file) {
  int fd;
  char c;
  int i = 0;
  int count = 0;
  std::string app[6] = {"", "", "", "", "", ""};
  std::list<std::string[6]> inputs;
  if(!(fd = open(_file.c_str(), O_RDWR, 0666))){
    std::cerr << "didn't open file" << std::endl;
    exit(1);
  }
  do {
    if (c == '\n' || c == '\0') {
      inputs.insert(inputs.end(),app);
      count = 0;
    }
    else{
      if(c == ' ')
      {
        if(count++ > 5) {

        } else app[0].push_back(' ');
      }
      app[count - 5 < 0 ? 0 : count - 5].push_back(c);
    }
  }while (read(fd, &c, 1) > 0);
  std::cout << "after read" << std::endl;
  for(auto v:inputs) {
    list.insert(list.end(), Task(v[0], std::stoi(v[1]), std::stoi(v[2]), std::stoi(v[3]), v[4], v[5]));
  }
}
