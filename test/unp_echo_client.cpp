#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> // bzero
#include <stddef.h>

#if 0
/* int
 * inet_pton4(src, dst)
 *	like inet_aton() but without all the hexadecimal and shorthand.
 * return:
 *	1 if `src' is a valid dotted quad, else 0.
 * notice:
 *	does not touch `dst' unless it's returning 1.
 * author:
 *	Paul Vixie, 1996.
 */
static int inet_pton4(const char *src, u_char *dst)
{
   static const char digits[] = "0123456789";
   int saw_digit, octets, ch;
   u_char tmp[INADDRSZ], *tp;

   saw_digit = 0;
   octets = 0;
   *(tp = tmp) = 0;
   while ((ch = *src++)!= '\0')
   {
      const char *pch;

      if ((pch = strchr(digits, ch))!= NULL)
      {
         u_int new = *tp * 10 +(pch - digits);

         if (new > 255)
         return (0);
         *tp = new;
         if (! saw_digit)
         {
            if (++octets > 4)
            return (0);
            saw_digit = 1;
         }
      } else if (ch == '.' && saw_digit)
      {
         if (octets == 4)
         return (0);
         *++tp = 0;
         saw_digit = 0;
      } else
      return (0);
   }
   if (octets < 4)
   return (0);
   /* bcopy(tmp, dst, INADDRSZ); */
   memcpy(dst, tmp, INADDRSZ);
   return (1);
}

int inet_pton(int af, const char *src, void *dst)
{
   switch (af)
   {
      case AF_INET:
      return (inet_pton4(src, dst));
      case AF_INET6:
      return (inet_pton6(src, dst));
      default:
      errno = EAFNOSUPPORT;
      return (-1);
   }
   /* NOTREACHED */
}
#endif

#define MAXLINE 1000
static int	read_cnt;
static char	*read_ptr;
static char	read_buf[MAXLINE];

static ssize_t
my_read(int fd, char *ptr)
{

   if(read_cnt <= 0)
   {
   again:
      if((read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0)
      {
         if(errno == EINTR) goto again;
         return (-1);
      } else if(read_cnt == 0) return (0);
      read_ptr = read_buf;
   }

   read_cnt--;
   *ptr = *read_ptr++;
   return (1);
}

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
   ssize_t	n, rc;
   char	c, *ptr;

   ptr = (char*)vptr;
   for(n = 1; n < maxlen; n++)
   {
      if((rc = my_read(fd, &c)) == 1)
      {
         *ptr++ = c;
         if(c == '\n') break;   /* newline is stored, like fgets() */
      } else if(rc == 0)
      {
         *ptr = 0;
         return (n - 1); /* EOF, n - 1 bytes were read */
      } else return (-1);    /* error, errno set by read() */
   }

   *ptr = 0;   /* null terminate like fgets() */
   return (n);
}

ssize_t writen(int fd, const void *vptr, size_t n) // Write "n" bytes to a descriptor.
{
   size_t  nleft;
   ssize_t nwritten;
   const char *ptr;

   ptr = (const char *)vptr;
   nleft = n;
   while(nleft > 0)
   {
      if((nwritten = write(fd, ptr, nleft)) <= 0)
      {
         if(nwritten < 0 && errno == EINTR) nwritten = 0; // and call write() again
         else return (-1); // error
      }

      nleft -= nwritten;
      ptr += nwritten;
   }
   return (n);
}

void str_cli(FILE *fp, int socket)
{
   char sendline[MAXLINE], recvline[MAXLINE];

   while(fgets(sendline, MAXLINE, fp)!=NULL)
   {
      writen(socket, sendline, strlen(sendline));

      if(readline(socket, recvline, MAXLINE) == 0)
      {
         puts("str_cli: server terminated prematurely");
         return;
      }

      fputs(recvline, stdout);
   }
}

int main(int argc, char **argv, char **env)
{
   int sockfd;
   struct sockaddr_in servaddr;

#if 0
   if(argc != 2)
   {
      puts("usage: unp_echo_client <IPaddress>");
      return 0;
   }
#endif

   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(7777);
   servaddr.sin_addr.s_addr = inet_addr("172.17.0.120");

   connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
   str_cli(stdin, sockfd);

   return 0;
}


