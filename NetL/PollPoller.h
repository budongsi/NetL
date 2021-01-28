#ifndef NETL_NET_POLLPOLLER_H
#define NETL_NET_POLLPOLLER_H

#include "Poller.h"
#include <poll.h>
#include <vector>
#include <map>

class PollPoller : public Poller
{
public:
   PollPoller(EventLoop *loop) 
       : m_ownerLoop(loop)
   {}

   virtual unsigned int poll(int timeoutMs, ChannelList *activeChannels) override;

   // Register and update the channel for interested I/O events.
   virtual void updateChannel(Channel* ch) override;

    // Remove the channel when it destructs.
   virtual void removeChannel(Channel* ch) override;

private:
   void fillActiveChannels(int numEvents, ChannelList* activeChannels);


public:
   ~PollPoller()
   {}

private:
   using PollFdList = std::vector<struct pollfd>;
   using ChannelMap = std::map<int, Channel *>;

   EventLoop *m_ownerLoop; 
   PollFdList m_pollfds;
   ChannelMap m_channels; 
};

#endif
