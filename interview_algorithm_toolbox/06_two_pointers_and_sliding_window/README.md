# 06 - 双指针与滑动窗口

这一目录解决“连续区间”和“有序数组夹逼”两类高频题。

## 建议阅读顺序

1. `two_pointers_sorted_array.cpp`
2. `remove_duplicates_sorted_array.cpp`
3. `longest_subarray_basic_window.cpp`
4. `fixed_length_window_max_sum.cpp`
5. `longest_substring_without_repeat.cpp`

## 本目录重点

- 有序数组找配对：双指针夹逼
- 原地去重：慢指针写答案，快指针负责扫描
- 所有数非负时：滑动窗口最稳
- 固定长度窗口优先考虑“减左加右”
- 无重复子串：窗口 + 上次出现位置
