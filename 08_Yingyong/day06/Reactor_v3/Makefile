INC_DIR:= ./
SRC_DIR:= ./
SRCS:= $(wildcard *.cpp)
OBJS:= $(patsubst %.cpp, %.o, $(SRCS))
LIBS:= 

CXX:=g++

CXXFLAGS:= -w -g  $(addprefix -I, $(INC_DIR)) $(LIBS) 

EXE:=./server.exe

$(EXE):$(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)

