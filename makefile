CC=gcc
CFLAGS=Wall -Wfatal-errors
SRC=Qlearn.c functions.c main.c 
INC=functions.h Qlearn.h 
OBJ=$(SRC:.c=.o)

prog: $(OBJ)
	$(CC) -o prog $(OBJ) 

%.o: %.c
	$(CC) -c -$(CFLAGS) $(SRC)

clean:
	rm -rf prog $(OBJ)