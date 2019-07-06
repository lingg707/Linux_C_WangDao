SRCS:=$(wildcard *.c)
TARGETS:=$(SRCS:%.c=%)
all:$(TARGETS)
%:%.c
	gcc $< -g -o $@ -lpthread
clean:
	rm $(TARGETS)

