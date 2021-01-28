#include "Channel.h"
#include "EventLoop.h"

#include <iostream>

using namespace std;

Channel::Channel(EventLoop *loop, int fd)
   : m_loop(loop),
     m_fd(fd),
     m_events(0),
     m_revents(0),
     m_indexInPollfdArray(-1)
{
}

void Channel::handleEvent()
{
   if(m_revents & POLLNVAL)
   {
      cout << "POLLNVAL event hanpens!" << endl;
   }

   // Handle POLLERR and POLLNVAL events
   if(m_revents & (POLLERR | POLLNVAL))
   {
      if(m_errorCallback) m_errorCallback();
   }

   // Handle POLLIN, POLLPRI and POLLRDHUP events
   if(m_revents & (POLLIN | POLLPRI /*| POLLRDHUP*/))
   {
      if(m_readCallback) m_readCallback();
   }

   // Handle POLLOUT events
   if(m_revents & POLLOUT)
   {
      if(m_writeCallback) m_writeCallback();
   }
}

void Channel::update(void)
{
   m_loop->updateChannel(this);
}

