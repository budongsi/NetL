#include "NetL/EventLoop.h"
#include <iostream>
#include <thread>

using namespace std;

void threadFunc()
{
   cout << "threadFunc(): pid = " << std::this_thread::get_id() << endl;

   EventLoop loop;
   loop.loop();
}

int main()
{
   cout << "main(): pid = " << std::this_thread::get_id() << endl;

   EventLoop loop;

   std::thread my_thread(threadFunc);
   
   loop.loop();
   my_thread.join();

   return 0;
}
