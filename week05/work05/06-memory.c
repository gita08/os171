/*
 * (c) 2016 Rahmat M. Samik-Ibrahim -- This is free software
 * REV00 Mon Oct  3 13:27:14 WIB 2016
 * START Mon Oct  3 09:26:51 WIB 2016
 */

#define MSIZE1 0x10000
#define MSIZE2 0x20000
#define MSIZE3 0x50000
#define MSIZE4 0x100000
#define MSIZE5 0x1000000
#define MSIZE6 0x10000000
#define LINE   75
#define MAXSTR 80
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void printLine(int line) {
   while(line-- > 0) putchar('x');
   putchar('\n');
}

void main (void) {
   char  strSYS2[MAXSTR], strSYS1[MAXSTR];
   char* chrStr = &strSYS1[0];
   int   ii, myPID  = getpid();
   sprintf(strSYS2, "top -b -n 1 -p%d | tail -5", myPID);
   sprintf(strSYS1, "top -b -n 1 -p%d | tail -1", myPID);
   printLine(LINE);
   system(strSYS2);
   chrStr = malloc(MSIZE1);
   system(strSYS1);
   free(chrStr);
   chrStr = malloc(MSIZE2);
   system(strSYS1);
   free(chrStr);
   chrStr = malloc(MSIZE3);
   system(strSYS1);
   free(chrStr);
   chrStr = malloc(MSIZE4);
   system(strSYS1);
   free(chrStr);
   chrStr = malloc(MSIZE5);
   for (ii = 0; ii < MSIZE5; ii++) {
      chrStr[ii]='a';
   }
   system(strSYS1);
   free(chrStr);
   chrStr = malloc(MSIZE6);
   system(strSYS1);
   free(chrStr);
   chrStr = malloc(MSIZE1);
   for (ii = 0; ii < MSIZE1; ii++) {
      chrStr[ii]='a';
   }
   system(strSYS1);
   free(chrStr);
   printLine(LINE);
}

