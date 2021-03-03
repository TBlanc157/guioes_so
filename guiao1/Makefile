CC=gcc
FLAGS=-g -Wall

all: readln pessoas mycat mycp

readln: readln.c
		$(CC) $(FLAGS) -o readln.out readln.c

pessoas: pessoas.c
		 $(CC) $(FLAGS) -o pessoas.out pessoas.c

mycat: mycat.c
	   $(CC) $(FLAGS) -o mycat.out mycat.c

mycp: mycp.c
	  $(CC) $(FLAGS) -o mycp.out mycp.c

clean:
	rm -f *.out