#编译器配置
CXX := g++
CXX_STD := c++17
WARNINGS := -Wall -Wextra -pedantic
DEBUG := -g
OPTIMIZE := -O2
CXXFLAGS := $(WARNINGS) $(DEBUG) $(OPTIMIZE) -std=$(CXX_STD) -MMD -MP
LDFLAGS := 

# 文件配置
SRCS := $(wildcard *.cpp)
EXECUTABLES := $(patsubst %.cpp,%,$(SRCS))
DEPFILES := $(patsubst %.cpp,%.d,$(SRCS))

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

# 包含自动生成的依赖关系
-include $(DEPFILES)

clean:
	@echo "[CLEAN]"
	$(Q)$(RM) $(EXECUTABLES) $(DEPFILES)

rebuild: clean all
