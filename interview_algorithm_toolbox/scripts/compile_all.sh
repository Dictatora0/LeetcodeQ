#!/bin/bash

# 面向 interview_algorithm_toolbox 的批量编译脚本
# 目标：
# 1. 遍历本知识库下所有新增 .cpp 文件
# 2. 使用 C++17 + 常用告警参数独立编译
# 3. 编译产物放到临时目录
# 4. 即使遇到失败，也继续检查剩余文件

set -u

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
SOURCE_ROOT="$PROJECT_ROOT/interview_algorithm_toolbox"
BUILD_DIR="$(mktemp -d "${TMPDIR:-/tmp}/interview_algorithm_toolbox_build.XXXXXX")"

CXXFLAGS=(-std=c++17 -Wall -Wextra -O2)

TOTAL=0
SUCCESS=0
FAILED=0

echo "Compile source root: $SOURCE_ROOT"
echo "Temporary build dir: $BUILD_DIR"
echo "Compiler flags: ${CXXFLAGS[*]}"
echo "----------------------------------------"

while IFS= read -r -d '' file; do
    TOTAL=$((TOTAL + 1))
    relative_path="${file#$PROJECT_ROOT/}"
    output_file="$BUILD_DIR/${relative_path%.cpp}"
    mkdir -p "$(dirname "$output_file")"

    echo "[${TOTAL}] compiling $relative_path"
    if g++ "${CXXFLAGS[@]}" "$file" -o "$output_file" >"$BUILD_DIR/compile.stdout" 2>"$BUILD_DIR/compile.stderr"; then
        SUCCESS=$((SUCCESS + 1))
        echo "  OK"
    else
        FAILED=$((FAILED + 1))
        echo "  FAIL"
        echo "  stderr:"
        sed 's/^/    /' "$BUILD_DIR/compile.stderr"
    fi
done < <(find "$SOURCE_ROOT" -type f -name "*.cpp" -print0 | sort -z)

echo "----------------------------------------"
echo "Compile summary"
echo "  total:   $TOTAL"
echo "  success: $SUCCESS"
echo "  failed:  $FAILED"
echo "  build dir: $BUILD_DIR"

if [ "$FAILED" -gt 0 ]; then
    exit 1
fi

exit 0
