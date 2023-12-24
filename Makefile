CC=gcc
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
INC=function.h

all : exec

%.o : %.c $(INC)

exec : $(OBJ)
	$(CC) -fsanitize=address $^ -o $@
	doxygen Doxyfile

debug:
	@echo $(SRC)
	@echo $(OBJ)

clean : 
	rm -f *.o
	rm -f exec
	rm -r html/
	rm -r latex/

doxygen	:
	xdg-open html/index.html