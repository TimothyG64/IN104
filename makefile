CC=gcc
CFLAGS=Wall -Wfatal-errors
SRC=Qlearn.c functions.c main.c mazeEnv.c
INC=functions.h Qlearn.h mazeEnv.h
OBJ=$(SRC:.c=.o)

prog: $(OBJ)
	$(CC) -o prog $(OBJ) 
	make clean1

%.o: %.c
	$(CC) -c -$(CFLAGS) $(SRC)

clean:
	rm -rf prog $(OBJ)

clean1:
	rm -rf $(OBJ)