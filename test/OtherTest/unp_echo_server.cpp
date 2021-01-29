#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> // bzero
#include <stddef.h>

ssize_t writen(int fd, const void *vptr, size_t n) // Write "n" bytes to a descriptor.
{
   size_t  nleft;
   ssize_t nwritten;
   const char * ptr;

   ptr = (const char *)vptr;
   nleft = n;
   while(nleft > 0) {
      if((nwritten = write(fd, ptr, nleft)) <= 0) {
         if(nwritten < 0 && errno == EINTR)
            nwritten = 0; // and call write() again
         else
            return(-1); // error
      }
      
      nleft -= nwritten;
      ptr += nwritten;
   }
   return(n);
}

void str_echo(int sockfd)
{
#define MAXLINE 1000
   ssize_t n;
   char buf[MAXLINE];

again:
   while((n = read(sockfd, buf, MAXLINE)) > 0)
      writen(sockfd, buf, n);

   if(n<0 && errno == EINTR){
      goto again;
   } else if(n<0) {
      puts("str_echo: read error");
   }
}

int main(int argc, char **argv, char **env)
{
   int listenfd, connfd;
   pid_t childpid;
   socklen_t clilen;
   struct sockaddr_in cliaddr, servaddr;

   listenfd = socket(AF_INET, SOCK_STREAM, 0);

   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(7777);
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
   listen(listenfd, SOMAXCONN);

   puts("Listen on port: 7777");

   while(1)
   {
      clilen = sizeof(cliaddr);
      connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

      if((childpid = fork()) == 0)
      {
         close(listenfd);
         str_echo(connfd);
         exit(0);
      }
      close(connfd);
   }
   return 0;
}

