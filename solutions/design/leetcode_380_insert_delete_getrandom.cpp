/*
 * LeetCode 380. O(1) 时间插入、删除和获取随机元素
 * (Insert Delete GetRandom O(1))
 * 难度：Medium
 *
 * 题目描述：
 * 实现 RandomizedSet 类：
 * - RandomizedSet() 初始化 RandomizedSet 对象
 * - bool insert(int val) 当元素 val 不存在时，向集合中插入该项，并返回 true；
 *   否则，返回 false
 * - bool remove(int val) 当元素 val 存在时，从集合中移除该项，并返回 true；
 *   否则，返回 false
 * - int getRandom() 随机返回现有集合中的一项（测试用例保证调用此方法时集合中至少存在一个元素）
 *   每个元素应该有相同的概率被返回
 *
 * 要求：
 * - 每个函数的平均时间复杂度必须为 O(1)
 *
 * 示例：
 * RandomizedSet randomizedSet = new RandomizedSet();
 * randomizedSet.insert(1);    // 返回 true
 * randomizedSet.remove(2);    // 返回 false（2 不存在）
 * randomizedSet.insert(2);    // 返回 true
 * randomizedSet.getRandom();  // 返回 1 或 2，概率相同
 * randomizedSet.remove(1);    // 返回 true
 * randomizedSet.insert(2);    // 返回 false（2 已存在）
 * randomizedSet.getRandom();  // 返回 2
 *
 * ============================================================================
 *
 * 核心问题分析：
 *
 * 1. 三个操作的挑战：
 *    - insert O(1): 哈希表可以做到
 *    - remove O(1): 哈希表可以做到
 *    - getRandom O(1): 需要随机访问，数组可以做到
 *
 *    问题：如何同时满足这三个要求？
 *
 * 2. 单一数据结构的局限：
 *    - 哈希表：insert/remove O(1)，但 getRandom 需要遍历，O(n)
 *    - 数组：getRandom O(1)，但 remove 需要查找和移动，O(n)
 *    - 链表：都不是 O(1)
 *
 * 3. 组合数据结构的思路：
 *    哈希表 + 动态数组
 *
 *    数据结构设计：
 *    ┌─────────────────────────────────────┐
 *    │  哈希表 (unordered_map)             │
 *    │  key: 元素值                        │
 *    │  value: 元素在数组中的索引          │
 *    └─────────────────────────────────────┘
 *              ↓
 *    ┌─────────────────────────────────────┐
 *    │  动态数组 (vector)                  │
 *    │  存储所有元素                       │
 *    │  支持 O(1) 随机访问                 │
 *    └─────────────────────────────────────┘
 *
 * 4. 关键技巧：O(1) 删除数组元素
 *    - 不能直接删除中间元素（需要移动后面的元素，O(n)）
 *    - 技巧：将要删除的元素与数组最后一个元素交换，然后删除最后一个元素
 *
 *    示例：删除元素 2
 *    数组: [1, 2, 3, 4]
 *    哈希表: {1→0, 2→1, 3→2, 4→3}
 *
 *    步骤：
 *    1. 找到 2 的索引：1
 *    2. 将 2 与最后一个元素 4 交换
 *       数组: [1, 4, 3, 2]
 *    3. 更新哈希表中 4 的索引
 *       哈希表: {1→0, 2→1, 3→2, 4→1}
 *    4. 删除数组最后一个元素
 *       数组: [1, 4, 3]
 *    5. 删除哈希表中的 2
 *       哈希表: {1→0, 4→1, 3→2}
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <ctime>

using namespace std;

// ============================================================================
// 方法1：哈希表 + 动态数组（最优解）
// ============================================================================
//
// 算法思路：
// 1. 使用哈希表存储 <元素值, 数组索引> 的映射
// 2. 使用动态数组存储所有元素
// 3. insert: 添加到数组末尾，更新哈希表
// 4. remove: 与数组最后一个元素交换，删除最后一个元素，更新哈希表
// 5. getRandom: 随机生成索引，返回数组中的元素
//
// 时间复杂度：所有操作 O(1)
// 空间复杂度：O(n)
//
class RandomizedSet {
private:
    vector<int> nums;                    // 动态数组：存储所有元素
    unordered_map<int, int> valToIndex;  // 哈希表：元素值 → 数组索引

public:
    RandomizedSet() {
        // 初始化随机数种子
        srand(time(nullptr));
    }

    // 插入元素
    bool insert(int val) {
        // 如果元素已存在，返回 false
        if (valToIndex.count(val)) {
            return false;
        }

        // 将元素添加到数组末尾
        nums.push_back(val);
        // 更新哈希表：元素值 → 数组索引
        valToIndex[val] = nums.size() - 1;

        return true;
    }

    // 删除元素
    bool remove(int val) {
        // 如果元素不存在，返回 false
        if (!valToIndex.count(val)) {
            return false;
        }

        // 获取要删除元素的索引
        int index = valToIndex[val];
        // 获取数组最后一个元素
        int lastElement = nums.back();

        // 将最后一个元素移动到要删除元素的位置
        nums[index] = lastElement;
        // 更新哈希表中最后一个元素的索引
        valToIndex[lastElement] = index;

        // 删除数组最后一个元素
        nums.pop_back();
        // 删除哈希表中的元素
        valToIndex.erase(val);

        return true;
    }

    // 随机获取一个元素
    int getRandom() {
        // 生成随机索引
        int randomIndex = rand() % nums.size();
        // 返回对应的元素
        return nums[randomIndex];
    }
};

// ============================================================================
// 方法2：仅使用哈希表（不满足要求）
// ============================================================================
//
// 说明：
// 这个方法无法实现 O(1) 的 getRandom
// 仅作为对比，说明为什么需要数组
//
// 时间复杂度：
// - insert: O(1)
// - remove: O(1)
// - getRandom: O(n)  ← 不满足要求
//
class RandomizedSet2 {
private:
    unordered_map<int, bool> valSet;

public:
    RandomizedSet2() {
        srand(time(nullptr));
    }

    bool insert(int val) {
        if (valSet.count(val)) {
            return false;
        }
        valSet[val] = true;
        return true;
    }

    bool remove(int val) {
        if (!valSet.count(val)) {
            return false;
        }
        valSet.erase(val);
        return true;
    }

    // 问题：需要遍历哈希表，O(n)
    int getRandom() {
        int randomIndex = rand() % valSet.size();
        auto it = valSet.begin();
        advance(it, randomIndex);
        return it->first;
    }
};

// ============================================================================
// 操作序列演示
// ============================================================================
/*
初始状态：
nums: []
valToIndex: {}

操作1: insert(1)
- 1 不存在，插入
nums: [1]
valToIndex: {1→0}
返回 true

操作2: insert(2)
- 2 不存在，插入
nums: [1, 2]
valToIndex: {1→0, 2→1}
返回 true

操作3: insert(3)
- 3 不存在，插入
nums: [1, 2, 3]
valToIndex: {1→0, 2→1, 3→2}
返回 true

操作4: getRandom()
- 随机生成索引 0/1/2
- 假设生成 1，返回 nums[1] = 2
返回 2

操作5: remove(2)
- 2 存在，索引为 1
- 最后一个元素是 3
- 将 3 移动到索引 1
nums: [1, 3, 3]
valToIndex: {1→0, 2→1, 3→1}
- 删除最后一个元素
nums: [1, 3]
- 删除哈希表中的 2
valToIndex: {1→0, 3→1}
返回 true

操作6: insert(2)
- 2 不存在，插入
nums: [1, 3, 2]
valToIndex: {1→0, 3→1, 2→2}
返回 true

操作7: remove(1)
- 1 存在，索引为 0
- 最后一个元素是 2
- 将 2 移动到索引 0
nums: [2, 3, 2]
valToIndex: {1→0, 3→1, 2→0}
- 删除最后一个元素
nums: [2, 3]
- 删除哈希表中的 1
valToIndex: {2→0, 3→1}
返回 true

操作8: getRandom()
- 随机生成索引 0/1
- 假设生成 0，返回 nums[0] = 2
返回 2
*/

// ============================================================================
// 关键技巧详解：O(1) 删除数组元素
// ============================================================================
/*
问题：如何在 O(1) 时间内删除数组中的任意元素？

常规方法（不满足要求）：
1. 找到元素索引：O(1)（使用哈希表）
2. 删除元素：O(n)（需要移动后面的所有元素）

优化方法（满足要求）：
1. 找到元素索引：O(1)
2. 将该元素与数组最后一个元素交换：O(1)
3. 删除数组最后一个元素：O(1)
4. 更新哈希表：O(1)

关键点：
- 不需要保持数组的顺序
- 删除最后一个元素是 O(1) 操作
- 交换操作是 O(1)

示例：
数组: [10, 20, 30, 40, 50]
删除 30（索引 2）

步骤1：交换 30 和 50
数组: [10, 20, 50, 40, 30]

步骤2：删除最后一个元素
数组: [10, 20, 50, 40]

总时间：O(1)

注意事项：
- 如果删除的是最后一个元素，交换操作是自己和自己交换，不影响正确性
- 需要同步更新哈希表中的索引
*/

// ============================================================================
// 复杂度分析
// ============================================================================
/*
┌──────────────┬────────────┬────────────┬────────────────┐
│   操作       │ 时间复杂度  │ 空间复杂度  │     说明        │
├──────────────┼────────────┼────────────┼────────────────┤
│ insert       │   O(1)     │   O(1)     │ 数组末尾添加    │
├──────────────┼────────────┼────────────┼────────────────┤
│ remove       │   O(1)     │   O(1)     │ 交换 + 删除末尾 │
├──────────────┼────────────┼────────────┼────────────────┤
│ getRandom    │   O(1)     │   O(1)     │ 随机访问数组    │
└──────────────┴────────────┴────────────┴────────────────┘

总空间复杂度：O(n)
- 数组：O(n)
- 哈希表：O(n)

为什么需要两个数据结构？
- 哈希表：提供 O(1) 的查找和删除
- 数组：提供 O(1) 的随机访问

单一数据结构无法同时满足三个 O(1) 的要求
*/

// ============================================================================
// 测试用例
// ============================================================================

void testRandomizedSet() {
    cout << "=== 测试 RandomizedSet ===" << endl;

    RandomizedSet randomizedSet;

    // 测试用例1：基本操作
    cout << "\n测试用例1：基本操作" << endl;
    cout << "insert(1) = " << (randomizedSet.insert(1) ? "true" : "false") << " (期望: true)" << endl;
    cout << "remove(2) = " << (randomizedSet.remove(2) ? "true" : "false") << " (期望: false)" << endl;
    cout << "insert(2) = " << (randomizedSet.insert(2) ? "true" : "false") << " (期望: true)" << endl;
    cout << "getRandom() = " << randomizedSet.getRandom() << " (期望: 1 或 2)" << endl;
    cout << "remove(1) = " << (randomizedSet.remove(1) ? "true" : "false") << " (期望: true)" << endl;
    cout << "insert(2) = " << (randomizedSet.insert(2) ? "true" : "false") << " (期望: false)" << endl;
    cout << "getRandom() = " << randomizedSet.getRandom() << " (期望: 2)" << endl;

    // 测试用例2：重复插入
    cout << "\n测试用例2：重复插入" << endl;
    RandomizedSet set2;
    cout << "insert(1) = " << (set2.insert(1) ? "true" : "false") << " (期望: true)" << endl;
    cout << "insert(1) = " << (set2.insert(1) ? "true" : "false") << " (期望: false)" << endl;
    cout << "insert(1) = " << (set2.insert(1) ? "true" : "false") << " (期望: false)" << endl;

    // 测试用例3：删除不存在的元素
    cout << "\n测试用例3：删除不存在的元素" << endl;
    RandomizedSet set3;
    cout << "remove(1) = " << (set3.remove(1) ? "true" : "false") << " (期望: false)" << endl;
    set3.insert(1);
    cout << "insert(1)" << endl;
    cout << "remove(1) = " << (set3.remove(1) ? "true" : "false") << " (期望: true)" << endl;
    cout << "remove(1) = " << (set3.remove(1) ? "true" : "false") << " (期望: false)" << endl;

    // 测试用例4：随机性测试
    cout << "\n测试用例4：随机性测试" << endl;
    RandomizedSet set4;
    for (int i = 1; i <= 5; i++) {
        set4.insert(i);
    }
    cout << "插入 1-5" << endl;
    cout << "10 次 getRandom(): ";
    for (int i = 0; i < 10; i++) {
        cout << set4.getRandom() << " ";
    }
    cout << endl;

    // 测试用例5：交替插入和删除
    cout << "\n测试用例5：交替插入和删除" << endl;
    RandomizedSet set5;
    set5.insert(1);
    set5.insert(2);
    set5.insert(3);
    cout << "insert(1), insert(2), insert(3)" << endl;
    cout << "remove(2) = " << (set5.remove(2) ? "true" : "false") << " (期望: true)" << endl;
    set5.insert(4);
    cout << "insert(4)" << endl;
    cout << "remove(1) = " << (set5.remove(1) ? "true" : "false") << " (期望: true)" << endl;
    cout << "getRandom() = " << set5.getRandom() << " (期望: 3 或 4)" << endl;
}

int main() {
    testRandomizedSet();

    return 0;
}

/*
设计要点总结：

1. 数据结构选择：
   - 哈希表：快速查找和删除
   - 动态数组：支持随机访问
   - 两者结合，互补优势

2. 关键技巧：
   - 交换删除法：将要删除的元素与最后一个元素交换
   - 避免数组元素移动，保证 O(1) 删除
   - 同步维护哈希表和数组的一致性

3. 实现细节：
   - 哈希表存储 <值, 索引> 映射
   - 数组存储实际元素
   - 删除时需要更新被交换元素的索引

4. 边界情况：
   - 删除最后一个元素（自己和自己交换）
   - 重复插入/删除
   - 空集合（题目保证 getRandom 时非空）

5. 实际应用：
   - 随机抽样
   - 洗牌算法
   - 负载均衡（随机选择服务器）
   - 游戏开发（随机事件）

6. 扩展问题：
   - 如果允许重复元素？（LeetCode 381）
   - 如果需要按权重随机？
   - 如果需要线程安全？

7. 性能优化：
   - 使用 unordered_map 而不是 map（O(1) vs O(log n)）
   - 使用 vector 而不是 list（支持随机访问）
   - 预分配空间（reserve）减少扩容次数
*/
