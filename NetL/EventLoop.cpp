#include "EventLoop.h"
#include "PollPoller.h"

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
      m_threadId(std::this_thread::get_id()
    )
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
   m_poller = new PollPoller(this);
}

EventLoop::~EventLoop()
{
   assert(!m_isLooping);

   if(m_poller != nullptr) delete m_poller; 
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

   while(!m_quit)
   {
      m_activeChannelList.clear();
      m_poller->poll(10000, &m_activeChannelList); // 3s
      for(auto ch : m_activeChannelList)
      {
         ch->handleEvent();
      }
   }

   cout << "EventLoop(obj):" << this << " stop looping" << endl;
   m_isLooping = false;
}

void EventLoop::updateChannel(Channel* ch)
{
   assert(ch->ownerLoop() == this);
   assertInLoopThread();
   m_poller->updateChannel(ch);
}

void EventLoop::quit()
{
   m_quit = true;
}

