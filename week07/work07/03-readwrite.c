/*
 * (c) 2011-2016 Rahmat M. Samik-Ibrahim -- This is free software
 * Feel free to copy and/or modify and/or distribute it, 
 * provided this notice, and the copyright notice, are preserved. 
 * REV01 Wed Nov  2 13:49:55 WIB 2016
 * REV00 Xxx Sep 30 XX:XX:XX UTC 2015
 * START Xxx Mar 30 02:13:01 UTC 2011
 */

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include "99-myutils.h"

extern sem_t    mutex, db, empty, full, rmutex, wmutex;

#define R_REHAT 4000
#define R_READ  2000
#define R_JUMLAH   3

#define W_REHAT 3000
#define W_WRITE 2000
#define W_JUMLAH   2

int reader_ID = 0;
int writer_ID = 0;

void* Reader (void* a) {
   int  my_ID;

   sem_wait (&rmutex);
   my_ID  = reader_ID++;
   sem_post (&rmutex);

   printf   ("                        READER %d: SIAP  ******\n", my_ID);
   while (TRUE) {
      printf("                        READER %d: REHAT ******\n", my_ID);
      rehat_acak(R_REHAT);
      printf("                        READER %d: MAU  MEMBACA\n", my_ID);
      printf("                        ***** JUMLAH PEMBACA %d\n", startRead());
      printf("                        READER %d:=SEDANG==BACA\n", my_ID);
      rehat_acak(R_READ);
      printf("                        READER %d: SELESAI BACA\n", my_ID);
      printf("                        ***** SISA PEMBACA %d\n", endRead());
   }
}

void* Writer (void* a) {
   int  my_ID;

   sem_wait (&wmutex);
   my_ID  = writer_ID++;
   sem_post (&wmutex);

   printf   ("WRITER %d: SIAP  *******\n", my_ID);
   while (TRUE) {
      printf("WRITER %d: REHAT *******\n", my_ID);
      rehat_acak(W_REHAT);
      printf("WRITER %d: MAU   MENULIS\n", my_ID);
      startWrite();
      printf("WRITER %d:=SEDANG==NULIS\n", my_ID);
      rehat_acak(W_WRITE);
      endWrite();
      printf("WRITER %d: SELESAI NULIS\n", my_ID);
   }
}

int main(int argc, char * argv[])
{
   int ii;
   init_rw();
   for (ii = 0 ; ii < R_JUMLAH; ii++)
      daftar_trit(Reader);
   for (ii = 0 ; ii < W_JUMLAH; ii++)
      daftar_trit(Writer);
   jalankan_trit();
   beberes_trit("Selese...");
}

