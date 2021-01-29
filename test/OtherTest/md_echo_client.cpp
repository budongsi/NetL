#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

using namespace std;

int main(void)
{
   // create a socket for connecting
   int sockfd = socket(AF_INET, SOCK_STREAM, 0);

   // bind the socket to a specified IP address
   struct sockaddr_in *server_addr =
       (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
   bzero(server_addr, sizeof(*server_addr));
   server_addr->sin_family = AF_INET;
   server_addr->sin_port = htons(7777);
   server_addr->sin_addr.s_addr = inet_addr("172.17.0.120");

   connect(sockfd, (struct sockaddr *)server_addr, sizeof(*server_addr));

   // send message
   char* msg = "Hello, NetL!";
   cout << "Send Message: " << msg << endl << endl;
   write(sockfd, msg, strlen(msg));

   // receive
   char* buf = (char*)malloc(1000);
   int bytes = read(sockfd, (void*)buf, 1000);

   cout << "Bytes received: " << bytes << endl;
   cout << "Text: " << buf << endl;

   close(sockfd);
   return 0;
}
