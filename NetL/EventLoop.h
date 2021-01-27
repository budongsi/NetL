#ifndef NETL_NET_EVENTLOOP_H
#define NETL_NET_EVENTLOOP_H

#include <boost/noncopyable.hpp>
#include <thread>
#include <memory>
#include <vector>
#include "Channel.h"
#include "Poller.h"

namespace NetL
{
namespace Net
{

// EventLoop for the Loop and dispatching a Event to its Event Handler
class EventLoop : boost::noncopyable
{
// Constructor
public:
   EventLoop();

   void loop();
   
   inline bool isInLoopThread() const { return m_threadId == std::this_thread::get_id();}
   EventLoop* getEventLoopOfCurrentThread();

   bool isLooping() { return m_isLooping; }

   public:
   ~EventLoop();

private:
   void abortNotInLoopThread() const;
   void assertInLoopThread() const;

// Data
private:
   const std::thread::id m_threadId;
   bool m_isLooping;

   using ChannelList = std::vector<Channel>;
   ChannelList m_activeChannelList;

   std::unique_ptr<Poller> m_poller;
};

}
}

#endif
