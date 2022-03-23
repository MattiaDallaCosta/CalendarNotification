#include "Message.hpp"

Message &Message::operator = (const Message &m){
  this->header = m.header;
  this->comment = m.comment;
  this->state = m.state;
  return *this;
}
