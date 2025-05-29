# 定义变量
SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%, $(SRCS))

all:$(OBJS)

%:%.c
	gcc -o $@ $^

clean:
	rm -rf $(OBJS)

# 打印变量的信息
echo:
	@echo $(SRCS)
	@echo $(OBJS)
