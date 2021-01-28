#include "Poller.h"

Poller::Poller(EventLoop *loop)
    : m_ownerLoop(loop)
{

}

void Poller::assertInLoopThread()
{
   m_ownerLoop->assertInLoopThread();
}


