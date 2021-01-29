#include "EventLoop.h"
#include "PollPoller.h"
#include "TimerId.h"

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
   m_timerQueue = new TimerQueue(this);
}

EventLoop::~EventLoop()
{
   assert(!m_isLooping);

   if(m_poller != nullptr) delete m_poller;
   if(m_timerQueue != nullptr) delete m_timerQueue;
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

      m_eventHandling = true;
      for(auto ch : m_activeChannelList)
      {
         currentActiveChannel = ch; // set the current running channel
         ch->handleEvent();
      }
      currentActiveChannel= nullptr;
      m_eventHandling = false;
      doPendingFunctors();
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

   // wakeup IO thread to quit
   if(!isInLoopThread())
   {
      wakeup();
   }
}

void EventLoop::runInLoop(const Functor &cb)
{
   if(isInLoopThread())
   {
      cb();
   }
   else
   {
      queueInLoop(cb);
   }
}

TimerId EventLoop::runAt(const Timestamp &time, TimerCallback cb)
{
   return m_timerQueue->addTimer(cb,time,0.0);
}

TimerId EventLoop::runAfter(double delay, const TimerCallback cb)
{
   Timestamp time(addTime(Timestamp::now(), delay));
   return runAt(time, cb);
}

TimerId EventLoop::runEvery(double interval, const TimerCallback cb)
{
   Timestamp time(addTime(Timestamp::now(), interval));
   return m_timerQueue->addTimer(cb,time,interval);
}

void EventLoop::queueInLoop(const Functor &cb)
{
   // ref to: doPendingFunctors()
   m_mutex.lock();
   m_pendingFunctors.push_back(cb);
   m_mutex.unlock();

   if(!isInLoopThread() || m_callingPendingFunctors)
   {
      wakeup();
   }
}


void EventLoop::doPendingFunctors()
{
   std::vector<Functor> functors;

   m_callingPendingFunctors = true;
   // ref to: queueInLoop()
   m_mutex.lock();
   functors.swap(m_pendingFunctors);
   m_mutex.unlock();

   for(auto functor : functors)
   {
      functor();
   }
   m_callingPendingFunctors = false;
}

void EventLoop::wakeup()
{

}


