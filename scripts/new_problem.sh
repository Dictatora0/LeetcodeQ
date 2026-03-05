#!/bin/bash

# 创建新题目模板
# 使用方法: ./scripts/new_problem.sh 题目编号 [题目名称]

if [ $# -lt 1 ]; then
    echo "使用方法: ./scripts/new_problem.sh 题目编号 [题目名称]"
    echo "示例: ./scripts/new_problem.sh 1 两数之和"
    exit 1
fi

PROBLEM_NUM=$1
PROBLEM_NAME=${2:-""}

# 创建C++源文件 (使用中文命名格式)
if [ -n "$PROBLEM_NAME" ]; then
    CPP_FILE="solutions/cpp/${PROBLEM_NUM}_${PROBLEM_NAME}.cpp"
else
    CPP_FILE="solutions/cpp/${PROBLEM_NUM}.cpp"
fi

if [ -f "$CPP_FILE" ]; then
    echo "文件 $CPP_FILE 已存在！"
    exit 1
fi

# 创建C++模板
cat > "$CPP_FILE" << EOF
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    // TODO: 实现解题方法
    
};

int main() {
    Solution solution;
    
    // TODO: 添加测试用例
    
    return 0;
}
EOF

echo "✅ 已创建题目 $PROBLEM_NUM 的源文件: $CPP_FILE"

# 如果提供了题目名称，创建笔记文件
if [ -n "$PROBLEM_NAME" ]; then
    NOTE_FILE="notes/${PROBLEM_NUM}_${PROBLEM_NAME}.md"
    cat > "$NOTE_FILE" << EOF
# $PROBLEM_NUM. $PROBLEM_NAME

## 题目描述
<!-- 在此描述题目 -->

## 解题思路
<!-- 在此记录解题思路 -->

## 复杂度分析
- 时间复杂度: O()
- 空间复杂度: O()

## 关键点
<!-- 记录解题关键点 -->
EOF
    echo "✅ 已创建笔记文件: $NOTE_FILE"
fi
