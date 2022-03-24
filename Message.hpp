#pragma once
#include <iostream>

#define msgSIZE 1024

typedef enum {
  NONE = 1,
  STINT = 2,
  PAUSE = 4
} State;

typedef struct message{
  std::string header;
  std::string comment;
  State state;
  struct message & operator = (const struct message &m);
} Message;

typedef struct {
  long mtype;
  char message[msgSIZE];
  void msg(Message &, long);
  Message getMessage(void);
} msg;
