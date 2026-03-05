#!/bin/bash

# 基于可执行文件恢复源文件（使用中文题目名称）

# 定义题目名称映射（中文）
problem_names_cn=(
    "3:无重复字符的最长子串"
    "15:三数之和"
    "27:移除元素"
    "41:缺失的第一个正数"
    "42:接雨水"
    "49:字母异位词分组"
    "53:最大子数组和"
    "59:螺旋矩阵II"
    "62:不同路径"
    "63:不同路径II"
    "64:最小路径和"
    "71:简化路径"
    "76:最小覆盖子串"
    "120:三角形最小路径和"
    "128:最长连续序列"
    "134:加油站"
    "135:分发糖果"
    "189:轮转数组"
    "198:打家劫舍"
    "209:长度最小的子数组"
    "221:最大正方形"
    "238:除自身以外数组的乘积"
    "239:滑动窗口最大值"
    "283:移动零"
    "380:O1时间插入删除和获取随机元素"
    "438:找到字符串中所有字母异位词"
    "509:斐波那契数"
    "560:和为K的子数组"
    "704:二分查找"
    "746:使用最小花费爬楼梯"
    "931:下降路径最小和"
    "977:有序数组的平方"
    "1052:爱生气的书店老板"
    "1423:可获得的最大点数"
)

# 获取题目名称的函数
get_problem_name() {
    local num=$1
    for item in "${problem_names_cn[@]}"; do
        if [[ "$item" == "$num:"* ]]; then
            echo "${item#*:}"
            return
        fi
    done
    echo ""
}

echo "开始恢复源文件（使用中文题目名称）..."

cd build/bin

for exec_file in *; do
    if [[ -f "$exec_file" && "$exec_file" =~ ^[0-9]+(_[0-9]+)?$ ]]; then
        problem_num="${exec_file%%_*}"
        suffix=""
        if [[ "$exec_file" =~ _[0-9]+$ ]]; then
            suffix="_${exec_file##*_}"
        fi
        
        problem_name=$(get_problem_name "$problem_num")
        if [[ -n "$problem_name" ]]; then
            cpp_file="../../solutions/cpp/${problem_num}_${problem_name}${suffix}.cpp"
            echo "创建: $cpp_file"
            
            # 创建基本的C++模板
            cat > "$cpp_file" << EOF
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// LeetCode ${problem_num}: ${problem_name}

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
        else
            echo "跳过: $exec_file (未找到题目名称)"
        fi
    fi
done

echo "源文件恢复完成！"
