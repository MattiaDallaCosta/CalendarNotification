#pragma once
#include <iostream>

typedef enum {
  NONE = 1,
  STINT = 2,
  PAUSE = 4
} State;

typedef struct 
{
  std::string header;
  std::string comment;
  State state;
} Message;
