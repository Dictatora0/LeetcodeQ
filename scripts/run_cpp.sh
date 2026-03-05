#!/bin/bash

# 编译并运行单个 C++ 文件（默认 release）
# 使用方法:
#   ./scripts/run_cpp.sh solutions/cpp/543_二叉树的直径.cpp
#   ./scripts/run_cpp.sh solutions/cpp/543_二叉树的直径.cpp --build-only
# 可选环境变量:
#   MODE=debug

set -u

if [[ $# -lt 1 ]]; then
    echo "用法: $0 <source.cpp> [--build-only]"
    exit 1
fi

SOURCE="$1"
BUILD_ONLY="false"
if [[ "${2:-}" == "--build-only" ]]; then
    BUILD_ONLY="true"
fi

if [[ ! -f "$SOURCE" ]]; then
    echo "❌ 源文件不存在: $SOURCE"
    exit 1
fi

MODE="${MODE:-release}"

if command -v g++ >/dev/null 2>&1; then
    CXX="g++"
elif command -v clang++ >/dev/null 2>&1; then
    CXX="clang++"
else
    echo "❌ 未找到可用编译器（g++/clang++）"
    exit 1
fi

if command -v ccache >/dev/null 2>&1; then
    CXX_CMD=(ccache "$CXX")
else
    CXX_CMD=("$CXX")
fi

if [[ "$MODE" == "debug" ]]; then
    CXXFLAGS=(-std=c++20 -O0 -g3 -fno-omit-frame-pointer)
else
    CXXFLAGS=(-std=c++20 -O2 -pipe -march=native -DNDEBUG)
fi

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"

filename="$(basename "$SOURCE" .cpp)"
if [[ "$filename" =~ ^([0-9]+) ]]; then
    exec_name="${BASH_REMATCH[1]}"
else
    exec_name="$filename"
fi

OUTPUT="$ROOT_DIR/build/bin/$exec_name"
mkdir -p "$ROOT_DIR/build/bin"

echo "编译器: $CXX"
echo "模式: $MODE"
echo "编译: $SOURCE"
"${CXX_CMD[@]}" "${CXXFLAGS[@]}" "$SOURCE" -o "$OUTPUT"

if [[ $? -ne 0 ]]; then
    echo "❌ 编译失败"
    exit 1
fi

echo "✅ 编译成功: $OUTPUT"

if [[ "$BUILD_ONLY" == "false" ]]; then
    echo "运行: $OUTPUT"
    "$OUTPUT"
fi
