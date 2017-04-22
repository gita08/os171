/* (c) 2005-2011 Rahmat M. Samik-Ibrahim, This is Free Software *
 * $Revision: 135 $
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
main(void) {
   int ii=0;
   if (fork() == 0) ii++;
   waitpid(-1,NULL,0);
   if (fork() == 0) ii++;
   waitpid(-1,NULL,0);
   if (fork() == 0) ii++;
   waitpid(-1,NULL,0);
   printf ("Result = %3.3d \n",ii);
   exit(0);
}

