#ifndef NETL_NET_EVENTLOOPTHREAD_H
#define NETL_NET_EVENTLOOPTHREAD_H

#include "EventLoop.h"

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <thread>
#include <condition_variable>

class EventLoopThread : boost::noncopyable
{
public:
   using ThreadInitCallback = boost::function<void(EventLoop*)>;

   EventLoopThread(const ThreadInitCallback &cb = ThreadInitCallback());
   ~EventLoopThread();
   EventLoop* startLoop();

private:
   void threadFunc();

private:
   EventLoop* m_loop;
   bool m_exiting;
   bool m_started;

   std::thread* m_thread;
   std::mutex m_mutex;
   std::condition_variable m_condition;

   ThreadInitCallback m_callback;
};




#endif
