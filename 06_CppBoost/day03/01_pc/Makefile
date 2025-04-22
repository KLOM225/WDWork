SRCS := $(wildcard *.cpp)
OUTS := $(patsubst %.cpp,%,$(SRCS))
CXX := g++
COM_OP := -Wall -g 
.PHONY: clean rebuild all

all: $(OUTS)                      
% : %.cpp
	$(CXX) $^ -o $@ $(COM_OP)

clean:
	$(RM) $(OUTS)

rebuild: clean all
