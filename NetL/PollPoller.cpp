#include "PollPoller.h"
#include "EventLoop.h"
#include <poll.h>

#include <iostream>

using namespace std;

unsigned int PollPoller::poll(int timeoutMs, ChannelList *activeChannels)
{
   int numEvents = ::poll(&*m_pollfds.begin(), m_pollfds.size(), timeoutMs);
   //int numEvents = ::poll(0, 0, 5000);

   if(numEvents > 0)
   {
      cout << numEvents << " events happended" << endl;
      fillActiveChannels(numEvents, activeChannels);
   }
   else if(numEvents == 0)
   {
      cout << "no event happended" << endl; 
   }
   else
   {
      cout << "Poller::poll() error" << endl;
   }
   return 0;
}


void PollPoller::removeChannel(Channel* ch)
{
   return;
}


void PollPoller::updateChannel(Channel* ch)
{
   if(ch->index() < 0)
   {
      // a new channel, add it to pollfds
      struct pollfd pfd;
      pfd.fd = ch->fd();
      pfd.events = static_cast<short>(ch->events());
      pfd.revents = 0;
      m_pollfds.push_back(pfd);
      int idx = static_cast<int>(m_pollfds.size()-1);
      ch->setIndex(idx);
      m_channels[pfd.fd] = ch;
   }
   else
   {
      // update existing channel which is in pollfds
      int idx = ch->index();
      struct pollfd &pfd = m_pollfds[idx];
      pfd.events = static_cast<short>(ch->events());
      pfd.revents = 0;
      if(ch->events() == 0) //kNoneEvent
      {
         pfd.fd = -1;
      }
   }
}

void PollPoller::fillActiveChannels(int numEvents, ChannelList *activeChannels)
{
   for(auto pfd : m_pollfds)
   {
      if(numEvents-- <= 0) break;

      if(pfd.revents > 0)
      {
         ChannelMap::const_iterator it = m_channels.find(pfd.fd); // find the iterator
         Channel* channel = it->second; // get the associated channel

         channel->set_revents(pfd.revents);
         activeChannels->push_back(channel);
      }
   }
}

