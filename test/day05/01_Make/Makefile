OUT := main
SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o , $(SRCS))
#OBJS := main.o add.o sub.o
COM_OP := -Wall -g
CC := gcc 

$(OUT): $(OBJS)
	$(CC) $^ -o $@
%.o : %.c compute.h 
	$(CC) -c $< -o $@ $(COM_OP)

#main.o: main.c compute.h
#	gcc -c $< -o $@ $(COM_OP)

.PHONY: clean rebuild 
clean:
	$(RM)  $(OUT) $(OBJS)
rebuild: clean $(OUT)
