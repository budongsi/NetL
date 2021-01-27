#include "NetL/EventLoop.h"
#include <iostream>
#include <thread>

using namespace std;

EventLoop* g_loop; 

void threadFunc()
{
   cout << "threadFunc(): pid = " << std::this_thread::get_id() << endl;
   g_loop->loop();
}

int main()
{
   cout << "main(): pid = " << std::this_thread::get_id() << endl;

   EventLoop loop;
   g_loop = &loop;

   std::thread my_thread(threadFunc);
   my_thread.join();

   return 0;
}
