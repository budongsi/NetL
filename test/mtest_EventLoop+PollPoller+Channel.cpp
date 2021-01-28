#include "EventLoop.h"
#include "Channel.h"
#include <iostream>
#include <thread>
#include <sys/timerfd.h>
#include <unistd.h>
#include <basetsd.h>

using namespace std;

EventLoop* g_loop;

void timeout()
{
   cout << "timeout" << endl;
   g_loop->quit();
}

int main()
{
   EventLoop loop;
   g_loop = &loop;

   int timerfd = ::timerfd_create(CLOCK_MONOTONIC,TFD_NONBLOCK|TFD_CLOEXEC);

   Channel channel(&loop,timerfd);
   channel.setReadCallback(timeout);
   channel.enableReading();
#
   struct itimerspec howlong;
   struct itimerspec oldhowlong; 
   struct itimerspec ramainhowlong; 
   bzero(&howlong, sizeof(howlong));
   howlong.it_value.tv_sec = 5;
   ::timerfd_settime(timerfd, 0, &howlong, &oldhowlong);
   ::timerfd_gettime(timerfd, &ramainhowlong);
   loop.loop();

   ::close(timerfd);
   return 0;
}

