#pragma once
#include <list>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include "Task.hpp"

void readConfig(std::list<Task>, std::string);
