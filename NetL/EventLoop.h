#ifndef NETL_NET_EVENTLOOP_H
#define NETL_NET_EVENTLOOP_H

#include "Channel.h"
#include "PollPoller.h"
#include "TimerQueue.h"

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <thread>
#include <memory>
#include <vector>
#include <mutex>

// EventLoop for the Loop and dispatching a Event to its Event Handler
class EventLoop : boost::noncopyable
{
// Constructor
public:
   // type
   using Functor = boost::function<void()>; 

   EventLoop();

   void loop();
   
   inline bool isInLoopThread() const { return m_threadId == std::this_thread::get_id();}
   EventLoop* getEventLoopOfCurrentThread();

   void assertInLoopThread();

   void quit();

   bool isLooping() { return m_isLooping; }

   void updateChannel(Channel* ch);

   void runInLoop(const Functor &cb);
 
   // Timer Event Management
   TimerId runAt(const Timestamp& time, TimerCallback cb);
   TimerId runAfter(double delay, const TimerCallback cb);
   TimerId runEvery(double interval, const TimerCallback cb);
   
   void wakeup(); 

   public:
   ~EventLoop();

private:
   void abortNotInLoopThread() const;
   void handleRead();
   void doPendingFunctors();
   void queueInLoop(const Functor& cb);

// Data
private:
   const std::thread::id m_threadId;
   bool m_isLooping;

   using ChannelList = std::vector<Channel*>;
   ChannelList m_activeChannelList;
   Channel *currentActiveChannel = nullptr; 

   PollPoller* m_poller;

   bool m_quit; 

   TimerQueue* m_timerQueue;
   bool m_callingPendingFunctors;

   // wakeup IO thread
   int m_wakeupFd;
   Channel *m_wakeupChannel; // channel for wake-up using eventfd

   std::mutex m_mutex;
   std::vector<Functor> m_pendingFunctors; // guarded by m_mutex

   bool m_eventHandling = false;
};


#endif
