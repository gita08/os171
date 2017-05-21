# (c) 2007-2016 Rahmat M. Samik-Ibrahim -- This is free software
# Feel free to copy and/or modify and/or distribute it, 
# provided this notice, and the copyright notice, are preserved. 
#
# REV01 Tue Nov  8 12:00:27 WIB 2016
# START Xxx Mar 30 02:13:01 UTC 2007

CC=gcc
 
EXECS= \
	00-server \
	01-client \
	02-clisvr \


all:	$(EXECS)


00-server: 00-server.c
	gcc 00-server.c -o 00-server

01-client: 01-client.c
	gcc 01-client.c -o 01-client

02-clisvr: 02-clisvr.c
	gcc 02-clisvr.c -o 02-clisvr

clean:
	rm -f $(EXECS)

