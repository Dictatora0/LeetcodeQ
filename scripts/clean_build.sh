#!/bin/bash
# 清理编译产物脚本

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/build"

if [ -d "$BUILD_DIR" ]; then
    echo "正在清理 build 目录..."
    rm -rf "$BUILD_DIR"
    echo "✓ 清理完成"
else
    echo "build 目录不存在，无需清理"
fi
