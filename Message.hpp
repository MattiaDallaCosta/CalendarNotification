#pragma once
#include <iostream>
#include <map>
#include <string>

#define msgSIZE 1024

typedef enum {
  NONE = 0,
  STINT = 1,
  PAUSE = 2
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
  std::string getOp();
  void Op(std::string, long);
} msg;
