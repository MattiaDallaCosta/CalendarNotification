#include "Message.hpp"
#include <cstdlib>
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
  char * appc[3];
  appc[0] = this->message;
  Message app;
  int i = 0;
  for(char c:this->message){
    if(c == '\0') break;
    if(c == ' '){
      appc[++i] = (&c)+1;
    }
  }
  app.header = appc[0];
  app.comment = appc[1];
  app.state = static_cast<State>(atoi(appc[2]));
  return app;
}
