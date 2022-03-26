#include "Message.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <string.h>
  
Message &Message::operator = (const Message &m){
  this->header = m.header;
  this->comment = m.comment;
  this->state = m.state;
  return *this;
}

void msg::msg(Message & m, long type){
  this->mtype = type;
  std::string app = m.header;
  app.append(" ");
  app.append(m.comment);
  app.append(" ");
  app.append(std::to_string(m.state));
  memcpy(this->message , app.c_str(), msgSIZE);
}
Message msg::getMessage(void){
  std::string appc[3];
  std::string msgstr(this->message);
  Message app;
  int pos, prepos=0;
  for (int i = 0; i < 3; i++) {
    pos = msgstr.find(" ",prepos);
    appc[i] = msgstr.substr(prepos, pos - prepos); 
    prepos = pos+1;
  }
  app.header = appc[0];
  app.comment = appc[1];
  app.state = static_cast<State>(stoi(appc[2]));
  return app;
} 
