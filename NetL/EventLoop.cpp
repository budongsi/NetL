#include "EventLoop.h"
#include <iostream>

using namespace std;

static __thread EventLoop* t_loopInThisThread = nullptr;

EventLoop::EventLoop()
    : m_isLooping(false),
      m_threadId(1)
{
   cout << "EventLoop created" << this << "in thread" << m_threadId;

}

EventLoop::~EventLoop()
{
   
}

EventLoop* getEventLoopOfCurrentThread()
{
   return t_loopInThisThread;
}

