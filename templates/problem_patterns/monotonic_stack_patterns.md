
# 单调栈模式指南

## 一眼识别信号（3 秒判断）
- 题目出现“下一个更大/更小”“最近更大/更小”
- 要为每个位置快速找到左右边界
- 需要把原本 O(n^2) 的“向两边找第一个满足条件”优化到 O(n)
- 常见于数组、柱状图、温度变化、雨水、子数组贡献值

## 常见题型分类
- Next Greater / Next Smaller：
  找右侧第一个更大（或更小）元素
- Previous Greater / Previous Smaller：
  找左侧最近边界
- 区间贡献型：
  每个元素作为“最小值/最大值”时能覆盖的范围（如 LC 907）
- 柱状图与雨水：
  通过边界与宽度计算面积或体积（LC 84 / LC 42）

## 栈类型怎么选
- 找“下一个更大”：
  维护单调递减栈（栈顶到栈底递减），遇到更大值触发弹栈
- 找“下一个更小”：
  维护单调递增栈，遇到更小值触发弹栈
- 需要左右边界：
  通常用两次扫描，或一次扫描配合哨兵统一结算

## 为什么通常存索引
- 需要计算距离/宽度，索引比数值更通用
- 有重复值时，索引能区分“哪个位置”的贡献
- 可通过索引回到原数组拿值，灵活性更高

## 通用模板（找右侧第一个更大）
```cpp
vector<int> ans(n, -1);
stack<int> st; // 存索引，栈内对应值单调递减

for (int i = 0; i < n; i++) {
    while (!st.empty() && nums[i] > nums[st.top()]) {
        ans[st.top()] = i; // 或 ans[st.top()] = nums[i]
        st.pop();
    }
    st.push(i);
}
```

## 左右边界模板（以“最小值贡献”为例）
```cpp
vector<int> left(n), right(n);
stack<int> st;

// 左边第一个严格更小的位置
for (int i = 0; i < n; i++) {
    while (!st.empty() && nums[st.top()] >= nums[i]) st.pop();
    left[i] = st.empty() ? -1 : st.top();
    st.push(i);
}

while (!st.empty()) st.pop();

// 右边第一个小于等于的位置（处理重复，防止重复计数）
for (int i = n - 1; i >= 0; i--) {
    while (!st.empty() && nums[st.top()] > nums[i]) st.pop();
    right[i] = st.empty() ? n : st.top();
    st.push(i);
}
```

## 高频易错点
- 把“找更大”与“找更小”的栈单调性写反
- 栈里存值导致无法计算宽度
- 忽略重复元素的去重策略，导致贡献重复计算
- 柱状图题忘记加哨兵，末尾元素未结算

## 面试口述模板（30 秒）
- “这题本质是找每个元素最近边界，暴力会 O(n^2)。”
- “我用单调栈保证每个索引只入栈出栈一次，总复杂度 O(n)。”
- “栈里存索引，便于算距离与宽度。”
- “重复值用 `>=` / `>` 做不对称处理，避免重复统计。”

## 推荐刷题路径
- 入门：
  LC 496, LC 739, LC 503
- 进阶：
  LC 84, LC 42, LC 901
- 综合：
  LC 907, LC 2104（贡献法）

## 对应算法模板
- `core_templates/monotonic_stack_template.cpp`
- `interview_ready/monotonic_stack_template.cpp`
