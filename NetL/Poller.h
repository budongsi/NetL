#ifndef NETL_NET_POLLER_H
#define NETL_NET_POLLER_H

#include <boost/noncopyable.hpp>
#include <vector>

class EventLoop;
class Channel;

// this is a base class for IO Multiplexing, we do not use
// it directly. The poll(2) and epoll(4) derived from this
// base class. In this class, here defined some necessary
// interface for the derived class.
class Poller : boost::noncopyable
{
public:
   // type
   using ChannelList = std::vector<Channel*>;


   // It polls the I/O events. Must be called in the loop
   // thread.
   // 
   // return: 1. the time cost.
   //         2. the actvie Channel.
   virtual unsigned int poll(int timeoutMs, ChannelList* activeChannels) = 0;

   // Register and update the channel for interested I/O events.
   virtual void updateChannel(Channel* ch) = 0;

   // Remove the channel when it destructs.
   virtual void removeChannel(Channel* ch) = 0;

   virtual void assertInLoopThread() = 0;
};

#endif
