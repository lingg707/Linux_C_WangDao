SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=server
CC:=gcc
CFLAGS:=-Wall
$(ELF):$(OBJS)
	gcc $^ -o $@
.PYONY:clean
clean:
	rm -rf $(OBJS) $(ELF)
