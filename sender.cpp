#include <cstdio>
#include <libnotify/notification.h>
#include <libnotify/notify.h>
#include <iostream>
#include <string>

void sendNotification(std::string, std::string, int);

int main (int argc, char ** argv)
{
  notify_init("Sample");
  sendNotification("Ciao", "Ciao gay", 4000);
  notify_uninit();
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
