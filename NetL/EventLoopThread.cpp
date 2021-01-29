#include "EventLoopThread.h"
#include <boost/bind.hpp>
#include <functional>
#include <iostream>

using namespace std;

EventLoopThread::EventLoopThread(const ThreadInitCallback& cb)
   :m_loop(nullptr),
    m_exiting(false),
    m_callback(cb),
    m_started(false)
{

}

EventLoopThread::~EventLoopThread()
{
   m_exiting = true;
   m_loop->quit();
   m_thread->join();
}

EventLoop* EventLoopThread::startLoop()
{
   if(m_started == false)
   {
      m_started = true; 
      m_thread = new std::thread(EventLoopThread::threadFunc, this);
      
      std::unique_lock<std::mutex> lck(m_mutex);
      m_mutex.lock();
      while(m_loop == nullptr)
      {
         m_condition.wait(lck);
      }
      m_mutex.unlock();
   }
   else
   {
      cout << "Thread is already started!" << endl;
   }
   return m_loop; 
}

void EventLoopThread::threadFunc()
{
   EventLoop loop;
   if(m_callback)
   {
      m_callback(&loop);
   }

   m_mutex.lock();
   m_loop = &loop;
   m_mutex.unlock();

   m_loop = nullptr;
}

