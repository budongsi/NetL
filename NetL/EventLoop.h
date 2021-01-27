#include <boost/noncopyable.hpp>


// EventLoop for the Loop and dispatching a Event to its Event Handler
class EventLoop : boost::noncopyable
{
// Constructor
public:
   EventLoop();

   void loop();
   
   //inline bool isInLoopThread() const { return m_threadId == CurrentThread::tid();}
   EventLoop* getEventLoopOfCurrentThread();

   bool isLooping() { return m_isLooping; }

   public:
   ~EventLoop();

private:
   void abortIfNotInLoopThread() const;

// Data
private:
   const int m_threadId;
   bool m_isLooping;
}; 


