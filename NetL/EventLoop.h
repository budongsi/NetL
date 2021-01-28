#ifndef NETL_NET_EVENTLOOP_H
#define NETL_NET_EVENTLOOP_H

#include "Channel.h"
#include "PollPoller.h"

#include <boost/noncopyable.hpp>
#include <thread>
#include <memory>
#include <vector>

// EventLoop for the Loop and dispatching a Event to its Event Handler
class EventLoop : boost::noncopyable
{
// Constructor
public:
   EventLoop();

   void loop();
   
   inline bool isInLoopThread() const { return m_threadId == std::this_thread::get_id();}
   EventLoop* getEventLoopOfCurrentThread();
   void assertInLoopThread(); 
   void quit();

   bool isLooping() { return m_isLooping; }

   void updateChannel(Channel* ch);

   public:
   ~EventLoop();

private:
   void abortNotInLoopThread() const;

// Data
private:
   const std::thread::id m_threadId;
   bool m_isLooping;

   using ChannelList = std::vector<Channel*>;
   ChannelList m_activeChannelList;

   PollPoller* m_poller;

   bool m_quit;
};


#endif
