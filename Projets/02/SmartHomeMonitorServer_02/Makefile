# 编译器和编译选项
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g -Iinclude
LDFLAGS := -llog4cpp -lpthread  # 添加log4cpp链接

# 目标可执行文件名
TARGET := server

# 目录定义
SRC_DIR := src
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
DEPS_DIR := $(BUILD_DIR)/deps

# 自动获取所有源文件并生成对象文件列表
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(patsubst $(SRC_DIR)/%.cpp,$(DEPS_DIR)/%.d,$(SRCS))

# 默认构建目标
all: $(TARGET)

# 包含自动生成的依赖文件
-include $(DEPS)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJS)
	@echo "Linking $@..."
	@$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Build successful! Linked with log4cpp"

# 编译规则：生成对象文件和依赖文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR) $(DEPS_DIR)
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -MMD -MP -MF $(DEPS_DIR)/$*.d -c $< -o $@

# 创建构建目录
$(OBJ_DIR) $(DEPS_DIR):
	@mkdir -p $@

# 清理生成的文件
clean:
	@rm -rf $(BUILD_DIR) $(TARGET)
	@echo "Clean complete."

.PHONY: all clean