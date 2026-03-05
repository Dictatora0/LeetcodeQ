#!/bin/bash

# 重命名文件，添加题目名称
cd solutions/cpp

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

echo "开始重命名文件..."

for file in *.cpp; do
    if [[ -f "$file" ]]; then
        # 提取数字部分
        if [[ "$file" =~ ^([0-9]+)(_[0-9]+)?\.cpp$ ]]; then
            problem_num="${BASH_REMATCH[1]}"
            suffix="${BASH_REMATCH[2]}"
            
            # 获取题目名称
            problem_name=$(get_problem_name "$problem_num")
            if [[ -n "$problem_name" ]]; then
                new_name="${problem_num}_${problem_name}${suffix}.cpp"
                
                echo "重命名: $file -> $new_name"
                mv "$file" "$new_name"
            else
                echo "跳过: $file (未找到题目名称)"
            fi
        elif [[ "$file" == "test.cpp" ]]; then
            echo "保留: $file"
        else
            echo "跳过: $file (格式不匹配)"
        fi
    fi
done

echo "文件重命名完成！"
