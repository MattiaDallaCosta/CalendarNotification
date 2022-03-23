#pragma once
#include <iostream>
typedef struct Message Message;
typedef enum {
  NONE = 1,
  STINT = 2,
  PAUSE = 4
} State;

typedef struct Message{
  std::string header;
  std::string comment;
  State state;
  Message &operator = (const Message &);
} Message;

