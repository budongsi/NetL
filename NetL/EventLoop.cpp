#include "EventLoop.h"

// Language Library
#include <iostream>
#include <thread>
#include <assert.h>

// System Library
#include <sys/poll.h>

using namespace std;

static __thread EventLoop* t_loopInThisThread = nullptr;

EventLoop::EventLoop()
    : m_isLooping(false),
      m_threadId(std::this_thread::get_id())
{
   cout <<  "EventLoop(obj) created:" << this << ", in thread:" << m_threadId << endl;

   if(t_loopInThisThread)
   {
      cout << "Another EventLoop: " << t_loopInThisThread 
           << "exist in this thread: " << m_threadId
           << endl;
   }
   else
   {
      t_loopInThisThread = this;
   }
}

EventLoop::~EventLoop()
{
   assert(!m_isLooping);
   t_loopInThisThread = nullptr;
}

EventLoop* EventLoop::getEventLoopOfCurrentThread()
{
   return t_loopInThisThread;
}

void EventLoop::abortNotInLoopThread() const
{
   cout << "EventLoop::abortNotInLoopThread - EventLoop(obj):" << this
       << " was created in thread:" << m_threadId
       << ", but current thread id is " <<  std::this_thread::get_id()
       << endl;
}


void EventLoop::assertInLoopThread()
{
   if(isInLoopThread() == false) // not in looping
   {
      abortNotInLoopThread();
   }
}

void EventLoop::loop()
{
   assert(!m_isLooping);
   assertInLoopThread();

   m_isLooping = true;

   poll(NULL, 0, 5000);

   cout << "EventLoop(obj):" << this << " stop looping" << endl;
   m_isLooping = false;
}

void EventLoop::updateChannel(const Channel& ch)
{
   m_poller->updateChannel(ch);
}

