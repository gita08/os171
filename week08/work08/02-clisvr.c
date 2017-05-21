/*
 * (c) 2007-2016 Tadeus Prastowo -- This is free software
 * This program was copased from the net and hacked until it works.
 * Feel free to copy and/or modify and/or distribute it, 
 * provided this notice, and the copyright notice, are preserved. 
 * REV00 Tue Nov  8 10:10:25 WIB 2016
 * START Xxx Xxx XX XX:XX:XX UTC 2007
 *
 * This program serves as both a client and a server. Three modes of
 * operation are available:
 *  - initiating mode
 *  - bridging mode
 *  - terminating mode
 *
 * The following are how to run thisprogram for each mode:
 *  - Initiating mode:  client_server null ANOTHER_HOST ANOTHER_PORT
 *  - Bridging mode:    client_server CURRENT_PORT ANOTHER_HOST ANOTHER_PORT
 *  - Terminating mode: client_server CURRENT_PORT null null
 *
 * The program having the initiating mode _MUST_ run last after all other
 * instances of this program with other operational modes has been started.
 *
 * In initiating mode, this program just simply sends a hello message to
 * another instance of this program that operates either as a bridge or
 * as a terminator that this program points to as specified in
 * ANOTHER_HOST and ANOTHER_PORT. After that this program will quit
 * without printing out any message.
 *
 * In bridging mode, this program just simply waits for an incoming hello
 * message in CURRENT_PORT. Once it receives a hello message, it prints
 * out the message in a certain format. Next, this program forwards the
 * modified message to another instance of this program that acts either as
 * a bridge or as a terminator that this program points to as specified
 * in ANOTHER_HOST and ANOTHER_PORT. After that this program will quit.
 *
 * In terminating mode, this program just simply waits for an incoming hello
 * message in CURRENT_PORT. Once it receives a hello message, it prints out
 * the message in a certain format, and then quits.
 *
 * The following illustrates the idea above:
 * 192.168.10.18 (alvin)
 * $ ./client_server 8888 localhost 7777
 * 192.168.10.18 (user)$
 * $ ./client_server 7777 null null
 * 192.168.12.17 (eus)$
 * $ ./client_server null 192.168.10.18 8888
 * The print out will be:
 * 192.168.10.18 (alvin):
 *   From eus to alvin: Hello
 * 192.168.10.18 (user):
 *   From eus to alvin to user: Hello
 */


char pesan[]="[FROM SERVER] ACK MESSAGE...\n";
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
/*
#include <stddef.h>
#include <sys/types.h>
#include <netinet/in.h>
*/
typedef struct sockaddr    sockad;
typedef struct sockaddr_in sockadin;
typedef struct hostent     shostent;

void error(char *msg){
   perror(msg);
   exit(0);
}

#define BUFFER_SIZE 256

int main (int argc, char *argv []) {
   int sockfd, newsockfd, portno, clilen, count, nn;
   char buffer [BUFFER_SIZE], temp_buffer [BUFFER_SIZE], *colon_pos;
   struct sockaddr_in serv_addr, cli_addr;
   struct hostent *server;

   if (argc < 4) {
      fprintf (stderr,"\nUsage: %s this_port  next_sever next_server_port\n\n"
               "Start the chain with `this_port' = `null'\n\n"
               "Terminte the chain with `next_server' = `next_server_port'"
               " = `null'\n\n", argv [0]);
      exit (1);
   }
   if (strcmp (argv [1], "null") == 0) {
      portno = atoi   (argv [3]);
      sockfd = socket (AF_INET, SOCK_STREAM, 0);
      if (sockfd < 0) {
         error ("ERROR opening socket");
      }
      server = gethostbyname(argv[2]);
      if (server == NULL) {
         fprintf (stderr, "ERROR, no such host\n");
         exit (1);
      }
      memset (&serv_addr, 0, sizeof (serv_addr));
      serv_addr.sin_family = AF_INET;
      memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
      serv_addr.sin_port = htons(portno);
      if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))< 0){
         error ("ERROR connecting");
      }
      /* Begin: action */
      memset (buffer, 0, BUFFER_SIZE);
      snprintf (buffer, BUFFER_SIZE, "From %s: Hello", getenv ("USER"));
      nn = write (sockfd, buffer, strlen (buffer));
      if (nn < 0) {
        error ("ERROR writing to socket");
      }
      /* End: action */
      exit (0);
   }

   sockfd = socket(AF_INET,SOCK_STREAM,0);
   if (sockfd < 0) {
      error ("ERROR opening socket");
   }
   memset(&serv_addr,0,sizeof(serv_addr));
   portno = atoi (argv [1]);
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons (portno);
   if (bind (sockfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
      error ("ERROR on binding");
   }
   listen (sockfd, 5);
   clilen    = sizeof (cli_addr);
   newsockfd = accept (sockfd, (struct sockaddr *) &cli_addr,
               (socklen_t *) &clilen);
   if (newsockfd < 0) {
      error ("ERROR on accept");
   }
   memset (buffer, 0, BUFFER_SIZE);
   nn = read(newsockfd,buffer,BUFFER_SIZE-1);
   if (nn < 0) {
      error ("ERROR reading from socket");
   }
   /* Modify buffer's message */
   colon_pos = strchr (buffer, ':');
   nn        = colon_pos - buffer;
   memset (temp_buffer, 0, BUFFER_SIZE);
   strncpy (temp_buffer, buffer, nn);
   memset (buffer, 0, BUFFER_SIZE);
   strncpy (buffer, temp_buffer, nn);
   snprintf (buffer + nn, BUFFER_SIZE-nn, " to %s: Hello", getenv ("USER"));
   /*End of modifying buffer's message*/
   if (strcmp (argv [2], "null") != 0 && strcmp (argv [3], "null") != 0) {
      portno = atoi (argv [3]);
      sockfd=socket(AF_INET,SOCK_STREAM,0);
      if (sockfd < 0) {
         error ("ERROR opening socket");
      }
      server = gethostbyname (argv [2]);
      if (server == NULL) {
         fprintf (stderr, "ERROR, no such host\n");
         exit (1);
      }
      serv_addr.sin_family = AF_INET;
      memcpy (&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
      serv_addr.sin_port = htons (portno);
      if (connect (sockfd,(struct sockaddr *)&serv_addr,sizeof (serv_addr))<0){
         error ("ERROR connecting");
      }
      /* Begin: action */
      printf ("%s\n", buffer);
      nn=write(sockfd,buffer,strlen(buffer));
      if (nn < 0) {
        error ("ERROR writing to socket");
      }
      /* End: action */
   } else {
      printf ("%s\n", buffer);
   }
   return 0;
}

