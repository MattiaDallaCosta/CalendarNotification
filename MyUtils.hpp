#pragma once
#include <list>
#include <string>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include "Task.hpp"

typedef enum {
  NONE = 1,
  STINT = 2,
  PAUSE = 4
} State;

typedef struct {
  std::string array[6];
} strTask;

void readConfig(std::list<Task>&, std::string);
