SRC:=$(wildcard *.c)
OBJ:=$(patsubst %.c,%.o,$(SRC))
ELF:=server
$(ELF):$(OBJ)
	gcc $^ -o $@ -lpthread
CFLAGS:=-Wall -g -I../server
CC:gcc
.PHONY:clean
clean:
	rm -rf $(OBJ) $(ELF)
