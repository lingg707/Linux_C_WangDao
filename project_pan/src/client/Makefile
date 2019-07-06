SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=client
CC:=gcc
CFLAGS:=-w
$(ELF):$(OBJS)
	gcc $^ -o $@
.PYONY:clean
clean:
	rm -rf $(OBJS) $(ELF) file
