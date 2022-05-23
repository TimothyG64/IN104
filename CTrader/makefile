CC=gcc
CFLAGS=Wall -Wfatal-errors
SRC=data.c main.c
INC=data.h 
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