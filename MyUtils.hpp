#pragma once
#include <list>
#include <string>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include "Task.hpp"

typedef struct {
  std::string array[5];
} strTask;

void readConfig(std::list<Task>&, std::string);
std::string strToHeader(std::string);
std::string strToComment(std::string);
