#!/bin/bash

# 批量编译所有 C++ 解题文件
# 使用方法:
#   ./scripts/compile_all.sh
# 可选环境变量:
#   MODE=debug   # 默认 release

set -u

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

echo "开始批量编译 Leetcode 题目..."
echo "编译器: $CXX"
echo "模式: $MODE"

# 创建输出目录
mkdir -p build/bin
mkdir -p build/debug

# 进入源码目录
cd solutions/cpp || exit 1

success=0
failed=0

# 编译所有 .cpp 文件
for cpp_file in *.cpp; do
    if [[ -f "$cpp_file" ]]; then
        filename="${cpp_file%.cpp}"
        if [[ "$filename" =~ ^([0-9]+) ]]; then
            exec_name="${BASH_REMATCH[1]}"
        else
            exec_name="$filename"
        fi

        if [[ ! -s "$cpp_file" ]]; then
            echo "跳过空文件: $cpp_file"
            continue
        fi

        echo "编译: $cpp_file -> $exec_name"

        "${CXX_CMD[@]}" "${CXXFLAGS[@]}" -o "../../build/bin/$exec_name" "$cpp_file"

        if [[ $? -eq 0 ]]; then
            echo "✅ $exec_name 编译成功"
            success=$((success + 1))
        else
            echo "❌ $exec_name 编译失败"
            failed=$((failed + 1))
        fi
    fi
done

echo "批量编译完成！"
echo "成功: $success, 失败: $failed"
echo "可执行文件位置: build/bin/"
