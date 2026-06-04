#!/bin/bash
# LeetCode C++ 批量编译脚本
# 用法: ./scripts/compile_all.sh [目录]
# 示例: ./scripts/compile_all.sh solutions/binary_tree

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
source "$SCRIPT_DIR/build_common.sh"

# 颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 默认编译 solutions 下所有分类目录
TARGET_DIR="${1:-solutions}"

if [[ "$TARGET_DIR" != /* ]]; then
    TARGET_DIR="$PROJECT_ROOT/$TARGET_DIR"
fi

if [ ! -d "$TARGET_DIR" ]; then
    echo -e "${RED}错误: 目录不存在: $TARGET_DIR${NC}"
    exit 1
fi

TARGET_DIR="$(normalize_path "$PROJECT_ROOT" "$TARGET_DIR")"

# 确定编译模式
BUILD_MODE="$(build_mode)"
OUTPUT_DIR="$(build_output_root "$PROJECT_ROOT")"
CXXFLAGS="$(build_cxxflags)"

if [ "$BUILD_MODE" == "debug" ]; then
    echo -e "${YELLOW}编译模式: Debug${NC}"
else
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
    OUTPUT_FILE="$(output_file_for_source "$PROJECT_ROOT" "$file" "$OUTPUT_DIR")"

    mkdir -p "$(dirname "$OUTPUT_FILE")"

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
