#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main(void)
{
   int listen_fd, connect_fd;

   // create a socket for listen
   listen_fd = socket(AF_INET, SOCK_STREAM, 0);

   // bind the socket to a specified IP address
   struct sockaddr_in *server_addr =
       (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
   server_addr->sin_family = AF_INET;
   server_addr->sin_port = htons(7777);
   server_addr->sin_addr.s_addr = inet_addr("172.17.0.120");
   if(bind(listen_fd,(struct sockaddr*)server_addr,sizeof(*server_addr)))
   {
      cout << "bind failed" << endl;
   }

   // start listening
   if(listen(listen_fd, SOMAXCONN) != 0)
   {
      cout << "listen failed" << endl;
   }

   // accept data from client
   struct sockaddr_in *client_addr =
       (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
   socklen_t clilen; 
   char buf[1000];
   // wait for connection
   cout << "Listen on port: 7777" << endl;
   connect_fd = accept(listen_fd, (struct sockaddr *)client_addr, &clilen);
   printf("Connected to %s:%u\n", inet_ntoa(client_addr->sin_addr), ntohs(client_addr->sin_port));
   printf("Numeric: %u\n\n", ntohl(client_addr->sin_addr.s_addr));

   while(1)
   {
      int bytes = read(connect_fd, (void*)buf, 1000);
      if(bytes <= 0)
      {
         close(connect_fd);
         cout << endl << "Connection Closed." << endl;
         return 0;
      }

      printf("Bytes received: %u\n", bytes);
      printf("Text: %s\n", buf);

      // send ack message
      write(connect_fd, buf, bytes);
   }
   return 0;
}

