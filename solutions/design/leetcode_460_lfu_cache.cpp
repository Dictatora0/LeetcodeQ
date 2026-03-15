/*
 * LeetCode 460. LFU 缓存 (LFU Cache)
 * 难度：Hard
 *
 * 题目描述：
 * 请你为最不经常使用（LFU）缓存算法设计并实现数据结构。
 *
 * 实现 LFUCache 类：
 * - LFUCache(int capacity) 用数据结构的容量 capacity 初始化对象
 * - int get(int key) 如果键 key 存在于缓存中，则获取键的值，否则返回 -1
 * - void put(int key, int value) 如果键 key 已存在，则变更其值；
 *   如果键不存在，请插入键值对。当缓存达到其容量 capacity 时，
 *   则应该在插入新项之前，移除最不经常使用的项。
 *   在此问题中，当存在平局（即两个或更多个键具有相同使用频率）时，
 *   应该去除最近最久未使用的键。
 *
 * 为了确定最不常使用的键，可以为缓存中的每个键维护一个使用计数器。
 * 使用计数最小的键是最久未使用的键。
 *
 * 当一个键首次插入到缓存中时，它的使用计数器被设置为 1（由于 put 操作）。
 * 对缓存中的键执行 get 或 put 操作，使用计数器的值将会递增。
 *
 * 函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。
 *
 * 示例：
 * LFUCache lfu = new LFUCache(2);
 * lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
 * lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
 * lfu.get(1);      // 返回 1, cache=[1,2], cnt(2)=1, cnt(1)=2
 * lfu.put(3, 3);   // 去除键 2，cache=[3,1], cnt(3)=1, cnt(1)=2
 * lfu.get(2);      // 返回 -1（未找到）
 * lfu.get(3);      // 返回 3, cache=[3,1], cnt(3)=2, cnt(1)=2
 * lfu.put(4, 4);   // 去除键 1，cache=[4,3], cnt(4)=1, cnt(3)=2
 * lfu.get(1);      // 返回 -1（未找到）
 * lfu.get(3);      // 返回 3, cache=[3,4], cnt(3)=3, cnt(4)=1
 * lfu.get(4);      // 返回 4, cache=[4,3], cnt(4)=2, cnt(3)=3
 *
 * ============================================================================
 *
 * 核心问题分析：
 *
 * 1. LFU vs LRU：
 *    LRU (Least Recently Used): 淘汰最近最少使用的
 *    LFU (Least Frequently Used): 淘汰使用频率最低的
 *
 *    LFU 更复杂：
 *    - 需要维护访问频率
 *    - 相同频率时，淘汰最久未使用的（LRU 策略）
 *
 * 2. 需要维护的信息：
 *    - key → value 映射
 *    - key → 访问频率 映射
 *    - 每个频率下的 key 列表（按时间顺序）
 *    - 当前最小频率
 *
 * 3. 数据结构设计：
 *
 *    ┌─────────────────────────────────────────────────────┐
 *    │  keyToVal: unordered_map<int, int>                  │
 *    │  key → value 映射                                   │
 *    └─────────────────────────────────────────────────────┘
 *
 *    ┌─────────────────────────────────────────────────────┐
 *    │  keyToFreq: unordered_map<int, int>                 │
 *    │  key → 访问频率 映射                                │
 *    └─────────────────────────────────────────────────────┘
 *
 *    ┌─────────────────────────────────────────────────────┐
 *    │  freqToKeys: unordered_map<int, list<int>>          │
 *    │  频率 → key 列表（双向链表，维护时间顺序）          │
 *    │                                                     │
 *    │  freq=1: [key3, key1]  ← key3 最久未使用            │
 *    │  freq=2: [key2]                                     │
 *    │  freq=3: [key4, key5]                               │
 *    └─────────────────────────────────────────────────────┘
 *
 *    ┌─────────────────────────────────────────────────────┐
 *    │  keyToIter: unordered_map<int, list<int>::iterator> │
 *    │  key → 在链表中的迭代器（用于 O(1) 删除）           │
 *    └─────────────────────────────────────────────────────┘
 *
 *    ┌─────────────────────────────────────────────────────┐
 *    │  minFreq: int                                       │
 *    │  当前最小频率（用于快速找到要淘汰的 key）           │
 *    └─────────────────────────────────────────────────────┘
 *
 * 4. 关键操作：
 *    - get(key): 增加频率，更新链表位置
 *    - put(key, value):
 *      - 如果 key 存在：更新值，增加频率
 *      - 如果 key 不存在：
 *        - 如果缓存已满：删除 minFreq 对应链表的第一个元素
 *        - 插入新 key，频率设为 1
 *
 * ============================================================================
 */

#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

// ============================================================================
// 方法1：哈希表 + 双向链表 + 频率表（最优解）
// ============================================================================
//
// 算法思路：
// 1. 使用多个哈希表维护不同的映射关系
// 2. 使用双向链表维护每个频率下的 key 列表（按时间顺序）
// 3. 维护最小频率，用于快速淘汰
//
// 关键点：
// - 每次访问（get/put）都会增加频率
// - 相同频率的 key 按访问时间排序（最近访问的在链表末尾）
// - 淘汰时选择最小频率链表的第一个元素（最久未使用）
//
// 时间复杂度：get 和 put 都是 O(1)
// 空间复杂度：O(capacity)
//
class LFUCache {
private:
    int capacity;                                      // 缓存容量
    int minFreq;                                       // 当前最小频率
    unordered_map<int, int> keyToVal;                  // key → value
    unordered_map<int, int> keyToFreq;                 // key → 频率
    unordered_map<int, list<int>> freqToKeys;          // 频率 → key 列表
    unordered_map<int, list<int>::iterator> keyToIter; // key → 链表迭代器

    // 增加 key 的访问频率
    void increaseFreq(int key) {
        int freq = keyToFreq[key];

        // 从旧频率的链表中删除
        freqToKeys[freq].erase(keyToIter[key]);

        // 如果旧频率的链表为空，删除该频率
        if (freqToKeys[freq].empty()) {
            freqToKeys.erase(freq);
            // 如果删除的是最小频率，更新 minFreq
            if (freq == minFreq) {
                minFreq++;
            }
        }

        // 频率加 1
        freq++;
        keyToFreq[key] = freq;

        // 添加到新频率的链表末尾（最近使用）
        freqToKeys[freq].push_back(key);
        keyToIter[key] = --freqToKeys[freq].end();
    }

    // 删除最不经常使用的 key
    void removeMinFreqKey() {
        // 获取最小频率对应的 key 列表
        auto& keyList = freqToKeys[minFreq];
        // 获取链表第一个元素（最久未使用）
        int deletedKey = keyList.front();
        // 从链表中删除
        keyList.pop_front();

        // 如果链表为空，删除该频率
        if (keyList.empty()) {
            freqToKeys.erase(minFreq);
        }

        // 删除相关映射
        keyToVal.erase(deletedKey);
        keyToFreq.erase(deletedKey);
        keyToIter.erase(deletedKey);
    }

public:
    LFUCache(int capacity) : capacity(capacity), minFreq(0) {}

    int get(int key) {
        // 如果 key 不存在，返回 -1
        if (!keyToVal.count(key)) {
            return -1;
        }

        // 增加访问频率
        increaseFreq(key);

        // 返回值
        return keyToVal[key];
    }

    void put(int key, int value) {
        if (capacity <= 0) {
            return;
        }

        // 如果 key 已存在
        if (keyToVal.count(key)) {
            // 更新值
            keyToVal[key] = value;
            // 增加频率
            increaseFreq(key);
            return;
        }

        // 如果缓存已满，删除最不经常使用的 key
        if (keyToVal.size() >= capacity) {
            removeMinFreqKey();
        }

        // 插入新 key
        keyToVal[key] = value;
        keyToFreq[key] = 1;
        freqToKeys[1].push_back(key);
        keyToIter[key] = --freqToKeys[1].end();

        // 最小频率设为 1
        minFreq = 1;
    }
};

// ============================================================================
// 方法2：哈希表 + 优先队列（不推荐）
// ============================================================================
//
// 说明：
// 使用优先队列维护 <频率, 时间戳, key> 的最小堆
// 问题：
// - 无法在 O(1) 时间内更新优先队列中的元素
// - 需要延迟删除，导致空间浪费
// - 实际时间复杂度 O(log n)
//
// 不满足题目要求，仅作为对比
//

// ============================================================================
// 操作序列演示
// ============================================================================
/*
capacity = 2

初始状态：
keyToVal: {}
keyToFreq: {}
freqToKeys: {}
minFreq: 0

操作1: put(1, 1)
- 插入新 key
keyToVal: {1→1}
keyToFreq: {1→1}
freqToKeys: {1: [1]}
minFreq: 1

操作2: put(2, 2)
- 插入新 key
keyToVal: {1→1, 2→2}
keyToFreq: {1→1, 2→1}
freqToKeys: {1: [1, 2]}  (1 在前，2 在后)
minFreq: 1

操作3: get(1)
- key 1 存在，频率从 1 增加到 2
- 从 freq=1 的链表中删除 1
- 添加到 freq=2 的链表
keyToVal: {1→1, 2→2}
keyToFreq: {1→2, 2→1}
freqToKeys: {1: [2], 2: [1]}
minFreq: 1
返回 1

操作4: put(3, 3)
- 缓存已满，需要淘汰
- minFreq = 1，淘汰 freq=1 链表的第一个元素：key 2
- 删除 key 2
keyToVal: {1→1}
keyToFreq: {1→2}
freqToKeys: {2: [1]}
- 插入 key 3
keyToVal: {1→1, 3→3}
keyToFreq: {1→2, 3→1}
freqToKeys: {1: [3], 2: [1]}
minFreq: 1

操作5: get(2)
- key 2 不存在
返回 -1

操作6: get(3)
- key 3 存在，频率从 1 增加到 2
keyToVal: {1→1, 3→3}
keyToFreq: {1→2, 3→2}
freqToKeys: {2: [1, 3]}  (1 在前，3 在后)
minFreq: 2
返回 3

操作7: put(4, 4)
- 缓存已满，需要淘汰
- minFreq = 2，淘汰 freq=2 链表的第一个元素：key 1
- 删除 key 1
keyToVal: {3→3}
keyToFreq: {3→2}
freqToKeys: {2: [3]}
- 插入 key 4
keyToVal: {3→3, 4→4}
keyToFreq: {3→2, 4→1}
freqToKeys: {1: [4], 2: [3]}
minFreq: 1

操作8: get(1)
- key 1 不存在
返回 -1

操作9: get(3)
- key 3 存在，频率从 2 增加到 3
keyToVal: {3→3, 4→4}
keyToFreq: {3→3, 4→1}
freqToKeys: {1: [4], 3: [3]}
minFreq: 1
返回 3

操作10: get(4)
- key 4 存在，频率从 1 增加到 2
keyToVal: {3→3, 4→4}
keyToFreq: {3→3, 4→2}
freqToKeys: {2: [4], 3: [3]}
minFreq: 2
返回 4
*/

// ============================================================================
// 关键技巧详解
// ============================================================================
/*
1. 为什么需要 keyToIter？
   - 需要在 O(1) 时间内从链表中删除元素
   - list::erase(iterator) 是 O(1) 操作
   - 如果没有迭代器，需要遍历链表查找，O(n)

2. 为什么使用 list 而不是 vector？
   - list 支持 O(1) 的插入和删除（任意位置）
   - vector 删除中间元素需要移动后面的元素，O(n)

3. minFreq 的维护：
   - 插入新 key 时，minFreq = 1
   - 增加频率时，如果删除的是 minFreq 对应的最后一个 key，minFreq++
   - 不需要遍历所有频率，因为频率是连续增长的

4. 相同频率的 LRU 策略：
   - 链表头部：最久未使用
   - 链表尾部：最近使用
   - 新访问的 key 添加到链表尾部
   - 淘汰时删除链表头部

5. 时间复杂度分析：
   - get: O(1)
     - 哈希表查找：O(1)
     - 链表删除：O(1)（使用迭代器）
     - 链表插入：O(1)
   - put: O(1)
     - 哈希表操作：O(1)
     - 链表操作：O(1)
     - 淘汰操作：O(1)
*/

// ============================================================================
// 复杂度分析
// ============================================================================
/*
┌──────────────┬────────────┬────────────┬────────────────┐
│   操作       │ 时间复杂度  │ 空间复杂度  │     说明        │
├──────────────┼────────────┼────────────┼────────────────┤
│ get          │   O(1)     │   O(1)     │ 哈希表 + 链表   │
├──────────────┼────────────┼────────────┼────────────────┤
│ put          │   O(1)     │   O(1)     │ 哈希表 + 链表   │
└──────────────┴────────────┴────────────┴────────────────┘

总空间复杂度：O(capacity)
- keyToVal: O(capacity)
- keyToFreq: O(capacity)
- freqToKeys: O(capacity)（所有链表的总长度）
- keyToIter: O(capacity)

数据结构选择：
- unordered_map: O(1) 查找、插入、删除
- list: O(1) 插入、删除（使用迭代器）
- 迭代器：O(1) 定位链表节点
*/

// ============================================================================
// LFU vs LRU 对比
// ============================================================================
/*
┌──────────────┬────────────────────┬────────────────────┐
│   特性       │       LRU          │       LFU          │
├──────────────┼────────────────────┼────────────────────┤
│ 淘汰策略     │ 最近最少使用        │ 使用频率最低        │
├──────────────┼────────────────────┼────────────────────┤
│ 数据结构     │ 哈希表 + 双向链表   │ 哈希表 + 多个链表   │
├──────────────┼────────────────────┼────────────────────┤
│ 实现复杂度   │ 简单               │ 复杂               │
├──────────────┼────────────────────┼────────────────────┤
│ 时间复杂度   │ O(1)               │ O(1)               │
├──────────────┼────────────────────┼────────────────────┤
│ 空间复杂度   │ O(n)               │ O(n)               │
├──────────────┼────────────────────┼────────────────────┤
│ 适用场景     │ 时间局部性强        │ 频率差异大          │
└──────────────┴────────────────────┴────────────────────┘

LRU 优点：
- 实现简单
- 适合大多数场景
- 对突发访问敏感

LFU 优点：
- 更好地反映长期访问模式
- 不容易被突发访问影响
- 适合频率差异明显的场景

LFU 缺点：
- 实现复杂
- 新加入的元素容易被淘汰
- 历史频率可能不代表未来
*/

// ============================================================================
// 测试用例
// ============================================================================

void testLFUCache() {
    cout << "=== 测试 LFUCache ===" << endl;

    // 测试用例1：基本操作
    cout << "\n测试用例1：基本操作" << endl;
    LFUCache lfu1(2);
    lfu1.put(1, 1);
    lfu1.put(2, 2);
    cout << "put(1,1), put(2,2)" << endl;
    cout << "get(1) = " << lfu1.get(1) << " (期望: 1)" << endl;
    lfu1.put(3, 3);
    cout << "put(3,3) - 淘汰 key 2" << endl;
    cout << "get(2) = " << lfu1.get(2) << " (期望: -1)" << endl;
    cout << "get(3) = " << lfu1.get(3) << " (期望: 3)" << endl;
    lfu1.put(4, 4);
    cout << "put(4,4) - 淘汰 key 1" << endl;
    cout << "get(1) = " << lfu1.get(1) << " (期望: -1)" << endl;
    cout << "get(3) = " << lfu1.get(3) << " (期望: 3)" << endl;
    cout << "get(4) = " << lfu1.get(4) << " (期望: 4)" << endl;

    // 测试用例2：更新已存在的 key
    cout << "\n测试用例2：更新已存在的 key" << endl;
    LFUCache lfu2(2);
    lfu2.put(1, 1);
    lfu2.put(2, 2);
    cout << "put(1,1), put(2,2)" << endl;
    lfu2.put(1, 10);
    cout << "put(1,10) - 更新 key 1 的值" << endl;
    cout << "get(1) = " << lfu2.get(1) << " (期望: 10)" << endl;
    lfu2.put(3, 3);
    cout << "put(3,3) - 淘汰 key 2" << endl;
    cout << "get(2) = " << lfu2.get(2) << " (期望: -1)" << endl;

    // 测试用例3：相同频率，淘汰最久未使用
    cout << "\n测试用例3：相同频率，淘汰最久未使用" << endl;
    LFUCache lfu3(2);
    lfu3.put(1, 1);
    lfu3.put(2, 2);
    cout << "put(1,1), put(2,2)" << endl;
    cout << "get(1) = " << lfu3.get(1) << " (期望: 1)" << endl;
    cout << "get(2) = " << lfu3.get(2) << " (期望: 2)" << endl;
    cout << "get(1) = " << lfu3.get(1) << " (期望: 1)" << endl;
    // 此时 key 1 频率为 3，key 2 频率为 2
    lfu3.put(3, 3);
    cout << "put(3,3) - 淘汰 key 2（频率最低）" << endl;
    cout << "get(2) = " << lfu3.get(2) << " (期望: -1)" << endl;

    // 测试用例4：容量为 1
    cout << "\n测试用例4：容量为 1" << endl;
    LFUCache lfu4(1);
    lfu4.put(1, 1);
    cout << "put(1,1)" << endl;
    cout << "get(1) = " << lfu4.get(1) << " (期望: 1)" << endl;
    lfu4.put(2, 2);
    cout << "put(2,2) - 淘汰 key 1" << endl;
    cout << "get(1) = " << lfu4.get(1) << " (期望: -1)" << endl;
    cout << "get(2) = " << lfu4.get(2) << " (期望: 2)" << endl;

    // 测试用例5：容量为 0
    cout << "\n测试用例5：容量为 0" << endl;
    LFUCache lfu5(0);
    lfu5.put(1, 1);
    cout << "put(1,1) - 容量为 0，不插入" << endl;
    cout << "get(1) = " << lfu5.get(1) << " (期望: -1)" << endl;
}

int main() {
    testLFUCache();

    return 0;
}

/*
设计要点总结：

1. 核心数据结构：
   - 4 个哈希表 + 双向链表
   - keyToVal: 存储键值对
   - keyToFreq: 存储访问频率
   - freqToKeys: 频率到 key 列表的映射
   - keyToIter: key 到链表迭代器的映射

2. 关键技巧：
   - 使用迭代器实现 O(1) 链表删除
   - 维护 minFreq 避免遍历所有频率
   - 链表维护相同频率下的 LRU 顺序
   - 频率增加时的链表迁移

3. 实现细节：
   - 增加频率：从旧链表删除，添加到新链表
   - 淘汰策略：删除 minFreq 链表的第一个元素
   - minFreq 更新：只在必要时更新（删除最后一个元素或插入新 key）

4. 边界情况：
   - 容量为 0
   - 容量为 1
   - 更新已存在的 key
   - 相同频率的多个 key

5. 性能优化：
   - 使用 unordered_map 而不是 map
   - 使用 list 而不是 vector
   - 使用迭代器避免查找
   - 延迟更新 minFreq

6. 实际应用：
   - 数据库查询缓存
   - CDN 内容缓存
   - 操作系统页面置换
   - 浏览器缓存策略

7. 扩展思考：
   - 如何实现 LRU-K（考虑最近 K 次访问）？
   - 如何实现 2Q（两个队列）？
   - 如何实现 ARC（自适应缓存替换）？
   - 如何实现线程安全的 LFU？

8. 与 LRU 的对比：
   - LFU 实现更复杂，但更能反映长期访问模式
   - LRU 对突发访问敏感，LFU 更稳定
   - 实际应用中，可以结合两者优点（LRU-K, 2Q 等）
*/
