CC=gcc
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
INC=function.h

all : exec

%.o : %.c $(INC)

exec : $(OBJ)
	$(CC) -fsanitize=address $^ -o $@

debug:
	@echo $(SRC)
	@echo $(OBJ)

clean : 
	rm -f *.o
	rm -f exec

doxygen	:
	xdg-open html/index.html