#ifndef NETL_NET_POLLPOLLER_H
#define NETL_NET_POLLPOLLER_H

#include "Poller.h"

class PollPoller : public Poller
{
public:
   PollPoller(EventLoop *loop) : Poller(loop)
   {
   }

   virtual unsigned int poll(int timeoutMs, ChannelList *activeChannels) override;

   // Register and update the channel for interested I/O events.
   virtual void updateChannel(const Channel& ch) override;

    // Remove the channel when it destructs.
   virtual void removeChannel(const Channel &ch) override;

public:
   ~PollPoller(){};
};

#endif
