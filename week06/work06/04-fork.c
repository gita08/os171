/* (c) 2005-2016 Rahmat M. Samik-Ibrahim, This is Free Software */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*************************************************** main ** */
main(void) {
   pid_t val1, val2, val3;
   val3 = val2 = val1 = (pid_t) 999;
   printf("PID==%5.5d ====\n", (int) getpid());
   fflush(stdout);
   val1 = fork();
   waitpid(-1,NULL,0);
   val2 = fork();
   waitpid(-1,NULL,0);
   val3 = fork();
   waitpid(-1,NULL,0);
/*
*/
   printf("VAL1=%5.5d VAL2=%5.5d VAL3=%5.5d\n", val1, val2, val3);
   exit (0);
}

/* ****************
   val1 = fork();
   waitpid(-1,NULL,0);
 ****************** */

