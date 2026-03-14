#!/bin/bash
# LeetCode C++ 单题编译运行脚本
# 用法: ./scripts/run_cpp.sh <cpp文件路径> [--build-only]
# 示例: ./scripts/run_cpp.sh solutions/binary_tree/leetcode_437_path_sum_iii.cpp

set -e

# 颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# 检查参数
if [ $# -lt 1 ]; then
    echo -e "${RED}错误: 缺少源文件参数${NC}"
    echo "用法: $0 <cpp文件路径> [--build-only]"
    echo "示例: $0 solutions/binary_tree/leetcode_437_path_sum_iii.cpp"
    exit 1
fi

SOURCE_FILE="$1"
BUILD_ONLY=false

# 检查是否只编译不运行
if [ "$2" == "--build-only" ]; then
    BUILD_ONLY=true
fi

# 检查源文件是否存在
if [ ! -f "$SOURCE_FILE" ]; then
    echo -e "${RED}错误: 文件不存在: $SOURCE_FILE${NC}"
    exit 1
fi

# 获取文件名（不含路径和扩展名）
FILENAME=$(basename "$SOURCE_FILE" .cpp)

# 确定编译模式 (release 或 debug)
MODE="${MODE:-release}"

# 创建输出目录
if [ "$MODE" == "debug" ]; then
    OUTPUT_DIR="build/debug"
    CXXFLAGS="-std=c++17 -g -O0 -Wall -Wextra"
    echo -e "${YELLOW}编译模式: Debug (调试模式)${NC}"
else
    OUTPUT_DIR="build/bin"
    CXXFLAGS="-std=c++17 -O2 -Wall"
    echo -e "${YELLOW}编译模式: Release (优化模式)${NC}"
fi

mkdir -p "$OUTPUT_DIR"

OUTPUT_FILE="$OUTPUT_DIR/$FILENAME"

# 编译
echo -e "${GREEN}正在编译: $SOURCE_FILE${NC}"
echo "输出文件: $OUTPUT_FILE"

if g++ $CXXFLAGS "$SOURCE_FILE" -o "$OUTPUT_FILE"; then
    echo -e "${GREEN}✓ 编译成功${NC}"

    # 如果不是只编译模式，则运行
    if [ "$BUILD_ONLY" == false ]; then
        echo -e "${GREEN}正在运行...${NC}"
        echo "----------------------------------------"
        "$OUTPUT_FILE"
        EXIT_CODE=$?
        echo "----------------------------------------"
        if [ $EXIT_CODE -eq 0 ]; then
            echo -e "${GREEN}✓ 运行完成 (退出码: $EXIT_CODE)${NC}"
        else
            echo -e "${YELLOW}⚠ 运行完成 (退出码: $EXIT_CODE)${NC}"
        fi
    fi
else
    echo -e "${RED}✗ 编译失败${NC}"
    exit 1
fi
