#
all:	all1 all2 
all1:	04-fork 
all2:	05-fork 06-fork 10-fork 11-fork 

04-fork: 04-fork.c
	cc -o 04-fork 04-fork.c

05-fork: 05-fork.c
	cc -o 05-fork 05-fork.c

06-fork: 06-fork.c
	cc -o 06-fork 06-fork.c

10-fork: 10-fork.c
	cc -o 10-fork 10-fork.c

11-fork: 11-fork.c
	cc -o 11-fork 11-fork.c

clean:
	/bin/rm -f *.o *.c~  
	/bin/rm -f 04-fork 05-fork 06-fork
	/bin/rm -f 10-fork 11-fork

