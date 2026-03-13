/*
LeetCode 380. O(1) 时间插入、删除和获取随机元素 (Insert Delete GetRandom O(1))

题目概述 (Problem Summary)
-------------------------
设计一个数据结构，支持以下操作，且平均时间复杂度为 O(1)：
1. insert(val)：若 val 不存在则插入并返回 true，否则返回 false
2. remove(val)：若 val 存在则删除并返回 true，否则返回 false
3. getRandom()：随机返回当前集合中的一个元素

关键约束 (Key Constraints)
-------------------------
- 该结构不允许重复元素
- getRandom 的概率应为均匀分布

示例 (Example)
-------------
操作序列：
insert(1) -> true
remove(2) -> false
insert(2) -> true
getRandom() -> 1 或 2
remove(1) -> true
getRandom() -> 2

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 需要在 O(1) 时间内完成插入、删除、随机访问

关键观察：
1. 随机访问需要数组（vector）
2. O(1) 删除需要知道元素在数组中的位置
3. 使用哈希表维护值到索引的映射

根据这些观察，可以得到两种典型解法：
1. 数组 + 哈希表（最优）
2. 纯数组线性查找（对比方法）
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
用 vector 存储元素，unordered_map 记录元素索引。
删除时将目标与末尾元素交换，再弹出末尾。

算法流程：
1. insert：若不存在，push_back，并记录索引
2. remove：用末尾元素覆盖要删除的位置，更新索引，再 pop_back
3. getRandom：随机索引访问 vector

复杂度分析
---------
时间复杂度：O(1) 平均
空间复杂度：O(n)
*/
class RandomizedSet {
public:
    RandomizedSet() {}

    bool insert(int val) {
        if (pos.count(val)) return false;
        data.push_back(val);
        pos[val] = static_cast<int>(data.size()) - 1;
        return true;
    }

    bool remove(int val) {
        auto it = pos.find(val);
        if (it == pos.end()) return false;

        int idx = it->second;
        int lastVal = data.back();
        data[idx] = lastVal;
        pos[lastVal] = idx;

        data.pop_back();
        pos.erase(it);
        return true;
    }

    int getRandom() {
        int idx = rand() % data.size();
        return data[idx];
    }

private:
    vector<int> data;
    unordered_map<int, int> pos;
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Naive Vector)

优化思路
--------
仅使用 vector 存储，插入前线性查重，删除时线性查找并删除。
该方法用于对比，复杂度较高。

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n)
*/
class RandomizedSet_Optimized {
public:
    RandomizedSet_Optimized() {}

    bool insert(int val) {
        for (int x : data) if (x == val) return false;
        data.push_back(val);
        return true;
    }

    bool remove(int val) {
        for (int i = 0; i < static_cast<int>(data.size()); ++i) {
            if (data[i] == val) {
                data.erase(data.begin() + i);
                return true;
            }
        }
        return false;
    }

    int getRandom() {
        int idx = rand() % data.size();
        return data[idx];
    }

private:
    vector<int> data;
};

/*
示例推演 (Example Walkthrough)
-----------------------------
insert(1)：data=[1], pos[1]=0
insert(2)：data=[1,2], pos[2]=1
remove(1)：用末尾 2 覆盖索引 0，data=[2], pos[2]=0
getRandom() -> 2
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：数组 + 哈希表
- 时间复杂度：O(1) 平均
- 空间复杂度：O(n)
- 优点：满足题目要求
- 缺点：需要维护映射

方法二：纯数组
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：实现简单
- 缺点：不满足 O(1)
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 对空集合调用 remove：返回 false
2. 重复 insert：返回 false
3. getRandom 需保证集合非空
*/

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    RandomizedSet rs;
    cout << boolalpha;

    // 测试用例 1
    cout << "insert(1) -> " << rs.insert(1) << " (期望: true)" << endl;
    cout << "remove(2) -> " << rs.remove(2) << " (期望: false)" << endl;
    cout << "insert(2) -> " << rs.insert(2) << " (期望: true)" << endl;
    cout << "getRandom() -> " << rs.getRandom() << " (期望: 1 或 2)" << endl;
    cout << "remove(1) -> " << rs.remove(1) << " (期望: true)" << endl;
    cout << "getRandom() -> " << rs.getRandom() << " (期望: 2)" << endl;

    return 0;
}
