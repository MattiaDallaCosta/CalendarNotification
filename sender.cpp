#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <libnotify/notification.h>
#include <libnotify/notify.h>
#include <iostream>
#include <string>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include "Message.hpp"

void sendNotification(std::string, std::string, int);

int main (int argc, char ** argv)
{
  if(argc < 3) {
    std::cout << "Wrong number of arguments" << std::endl;
    return 1;
  }
  int log = open("/tmp/mylog", O_RDWR | O_CREAT, 0666);
  key_t k = ftok(argv[1], atoi(argv[2]));
  int qId = msgget(k, 0666);
  msg m;
  msgrcv(qId, &m, msgSIZE, 1, 0);
  Message mess = m.getMessage();
  notify_init("Sample");
  sendNotification(mess.header, mess.comment, 4000);
  notify_uninit();
  exit(0);
  return 0;
}

void sendNotification(std::string _sum, std::string _text, int _timeout){
  if(!notify_is_initted()) notify_init("Sample");
  NotifyNotification * n = notify_notification_new(_sum.c_str(), _text.c_str(), 0);
  notify_notification_set_timeout(n, _timeout);
  int flag = notify_notification_show(n, 0);
  std::fprintf(flag ? stdout : stderr, "%s", flag ? "sent\n" : "not sent\n");
  if (!flag) sendNotification(_sum, _text, _timeout);
}
