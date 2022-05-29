CC=gcc
CFLAGS=Wall -Wfatal-errors
SRC=Qlearn.c functions.c  mazeEnv.c main.c
INC=functions.h Qlearn.h mazeEnv.h
OBJ=$(SRC:.c=.o)

prog: $(OBJ)
	$(CC) -o prog $(OBJ) -lm
	make clean1

%.o: %.c
	$(CC) -c -$(CFLAGS) $(SRC)

clean:
	rm -rf prog $(OBJ)

clean1:
	rm -rf $(OBJ)