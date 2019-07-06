SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))//替换通配符
ELF:=server
CC:=gcc
CFLAGS:=-Wall -I../include//用于C编译器的选项，指定头文件的路径CXXFLAGS是用于cpp编译的选项，包含了编译和汇编两个步骤
$(ELF):$(OBJS)//目标 依赖
	gcc $^ -o $@ -lpthrad
.PYONY:clean
clean:
	rm -rf $(OBJS) $(ELF)
