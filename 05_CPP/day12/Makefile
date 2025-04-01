# 编译器配置
CXX := g++
CXX_STD := c++17
WARNINGS := -Wall -Wextra -pedantic
DEBUG := -g
OPTIMIZE := -O2
CXXFLAGS := $(WARNINGS) $(DEBUG) $(OPTIMIZE) -std=$(CXX_STD)
LDFLAGS := 

# 文件配置
SRCS := $(wildcard *.cpp)
EXECUTABLES := $(patsubst %.cpp,%,$(SRCS))

# 构建控制
V ?= 0
ifeq ($(V),1)
    Q :=
else
    Q := @
endif

.PHONY: all clean rebuild

all: $(EXECUTABLES)

# 可执行文件构建规则
%: %.cpp
	@echo "[CXX] $@"
	$(Q)$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

clean:
	@echo "[CLEAN]"
	$(Q)$(RM) $(EXECUTABLES)

rebuild: clean all
