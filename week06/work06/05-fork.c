/* (c) 2005-2015 Rahmat M. Samik-Ibrahim, This is Free Software *
 * $Revsion$
 * $Date: 2011-02-27 08:31:46 +0700 (Sun, 27 Feb 2011) $
 * svn propset svn:keywords "Date Revision HeadURL Id Author"
 * JANGAN MENGHAPUS/MENGGANTI NOTA DI ATAS INI                  *
 * HARAP MENGGANTI/SESUAIKAN YANG BERIKUT INI!                  *
 ZCZC B000 Rahmat M. Samik-Ibrahim                              *
 * ************************************************************ */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define DISPLAY1 "PARENT PID* ** pid (%5.5d) ** ***********\n"
#define DISPLAY2 "val1(%5.5d) -- val2(%5.5d) -- val3(%5.5d)\n"
/*************************************************** main ** */
main(void) {
   pid_t val1, val2, val3;
   printf(DISPLAY1, (int) getpid());
   val1 = fork();
   val2 = fork();
   val3 = fork();
   printf(DISPLAY2, (int) val1, (int) val2, (int) val3);
   waitpid(-1,NULL,0);
   waitpid(-1,NULL,0);
   waitpid(-1,NULL,0);
   waitpid(-1,NULL,0);
   waitpid(-1,NULL,0);
   waitpid(-1,NULL,0);
   waitpid(-1,NULL,0);
   exit (0);
}


