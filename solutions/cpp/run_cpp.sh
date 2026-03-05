#!/bin/bash

# 在 solutions/cpp 目录中转发到仓库根目录脚本
# 用法:
#   ./run_cpp.sh 543_二叉树的直径.cpp
#   MODE=debug ./run_cpp.sh 543_二叉树的直径.cpp

set -u

if [[ $# -lt 1 ]]; then
    echo "用法: $0 <source.cpp> [--build-only]"
    exit 1
fi

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"

SOURCE="$1"
if [[ "$SOURCE" != /* ]]; then
    SOURCE="$SCRIPT_DIR/$SOURCE"
fi

"$ROOT_DIR/scripts/run_cpp.sh" "$SOURCE" "${2:-}"
