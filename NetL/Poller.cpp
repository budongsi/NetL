#include "Poller.h"


void Poller::assertInLoopThread()
{
   m_ownerLoop->assertInLoopThread();
}


