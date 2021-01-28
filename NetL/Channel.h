#ifndef NETL_NET_CHANNEL_H
#define NETL_NET_CHANNEL_H

#include <poll.h>

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>

class EventLoop;

// This class is assosiated with one file descriptor(fd)
// which could be a sockfd, an eventfd, a timerfd, or a
// signalfd.
class Channel
{
public:
   // Define a type which is the "void()" prototype
   using EventCallback = boost::function<void()>; 

   // A Channel belongs to its own EventLoop, that means
   // a Channel can only be handled in one EventLoop
   // thread. but One EventLoop can handle multiple Channels
   Channel(EventLoop *loop, int fd);

   inline void setWriteCallback(const EventCallback& cb) { m_writeCallback = cb; }
   inline void setReadCallback(const EventCallback &cb) { m_readCallback = cb; }
   inline void setErrorCallback(const EventCallback &cb) { m_errorCallback = cb; }

   // pollfd
   int fd() const { return m_fd; }
   int events() const { return m_events; }
   void set_revents(int revt) { m_revents = revt;}
   bool isNoneEvent() const { return m_events == kNoneEvent; }

   EventLoop* ownerLoop() { return m_loop; }

   int index() { return m_indexInPollfdArray; }
   void setIndex(int index) { m_indexInPollfdArray = index; }

   // The core function of this class.
   // HandleEvent is used for handling the received events from "poll" operation.
   void handleEvent(); 

   // trigger the event handler
   void enableReading() { m_events |= kReadEvent; update(); }
   void disableReading() { m_events &= ~kReadEvent; update(); }
   void enableWriting() { m_events |= kWriteEvent; update(); }
   void disableWriting() { m_events &= ~kWriteEvent; update(); }
   void disableALL() { m_events = kNoneEvent; update(); }

   // status check
   bool isWriting() const { return m_events & kWriteEvent; }

public:
   ~Channel(){}

private:
   // Update the concern events for the Channel.
   void update(void);

private:
   // The callback handler of events:
   // -------------------------------
   // POLLIN
   // POLLRDNORM
   // POLLRDBAND
   // POLLPRI
   // POLLOUT
   // POLLWRNORM
   // POLLWRBAND
   // POLLERR
   // POLLHUP
   // POLLNVAL
   // -------------------------------
   EventCallback m_writeCallback;
   EventCallback m_readCallback; 
   EventCallback m_errorCallback;

   // Associated EventLoop
   EventLoop* m_loop;

   // int poll(struct pollfd *fdarray, unsigned long nfds, inttimeout)
   // 
   // struct pollfd {
   //    int   fd;      /* descriptor to check */
   //    short events;  /* events of interest on fd */
   //    short revents  /* events that occurred on fd */
   // }
   const int m_fd;
   int m_events;
   int m_revents;

   // There is no including POSIX header, so some const value should be
   // defined here.
   const int kWriteEvent = POLLOUT;
   const int kNoneEvent = 0;
   const int kReadEvent = POLLIN | POLLPRI;

   // Specify where(index) is this channel in the pollfd array which is
   // the parameter of "poll" function.
   int m_indexInPollfdArray; // -1: it's a new channel for pollfd array
};

#endif
