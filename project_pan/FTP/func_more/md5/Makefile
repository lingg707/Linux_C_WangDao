SRCS:=$(wildcard *.c)
OBJ:=$(patsubst %.c,%.o,$(SRCS))
ELF:=md5_test
$(ELF):$(SRCS)
	gcc $^ -o $@ 
CFLAGS:=-Wall -o
CC:gcc
.PHONY:clean
clean:
	rm -rf $(OBJ) $(ELF)
