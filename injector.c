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
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>


  int main(int argc, char *argv[]) {
  
    if(argc < 2) {
     printf("Usage: ./injector <PID>\n");
     return 1;
    }
  
   pid_t target = atoi(argv[1]);
  
    if(ptrace(PTRACE_ATTACH, target, NULL, NULL) < 0) {
     perror("ptrace attach");
     return 1;
     }
   
    wait(NULL);
  
    printf("PID attach\n");
    
    if(ptrace(PTRACE_POKEDATA, target, (void*)"address of running program", (void*)0x9090909090909090) < 0) {
     perror("ptrace pokedata");
     return 1;
    }
  
   printf("injected NOPs at program address\n");
   
   ptrace(PTRACE_CONT, target, NULL, NULL);
   printf("Services killed\n");
   
  
  return 0;
  }
