#!/bin/bash
# LeetCode C++ 批量编译脚本
# 用法: ./scripts/compile_all.sh [目录]
# 示例: ./scripts/compile_all.sh solutions/binary_tree

set -e

# 颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 默认编译 solutions 下所有分类目录
TARGET_DIR="${1:-solutions}"

# 确定编译模式
MODE="${MODE:-release}"

if [ "$MODE" == "debug" ]; then
    OUTPUT_DIR="build/debug"
    CXXFLAGS="-std=c++17 -g -O0 -Wall -Wextra"
    echo -e "${YELLOW}编译模式: Debug${NC}"
else
    OUTPUT_DIR="build/bin"
    CXXFLAGS="-std=c++17 -O2 -Wall"
    echo -e "${YELLOW}编译模式: Release${NC}"
fi

mkdir -p "$OUTPUT_DIR"

# 统计变量
TOTAL=0
SUCCESS=0
FAILED=0

echo -e "${BLUE}开始批量编译: $TARGET_DIR${NC}"
echo "========================================"

# 查找所有 leetcode_*.cpp 文件
while IFS= read -r -d '' file; do
    TOTAL=$((TOTAL + 1))
    FILENAME=$(basename "$file" .cpp)
    OUTPUT_FILE="$OUTPUT_DIR/$FILENAME"

    echo -n "[$TOTAL] 编译 $file ... "

    if g++ $CXXFLAGS "$file" -o "$OUTPUT_FILE" 2>/dev/null; then
        echo -e "${GREEN}✓${NC}"
        SUCCESS=$((SUCCESS + 1))
    else
        echo -e "${RED}✗${NC}"
        FAILED=$((FAILED + 1))
        echo -e "${RED}  编译失败: $file${NC}"
    fi
done < <(find "$TARGET_DIR" -name "leetcode_*.cpp" -type f -print0 | sort -z)

echo "========================================"
echo -e "${BLUE}编译完成${NC}"
echo -e "总计: $TOTAL 个文件"
echo -e "${GREEN}成功: $SUCCESS${NC}"
if [ $FAILED -gt 0 ]; then
    echo -e "${RED}失败: $FAILED${NC}"
    exit 1
else
    echo -e "失败: 0"
    echo -e "${GREEN}✓ 所有文件编译成功！${NC}"
fi
