/*
LeetCode 146. LRU 缓存 (LRU Cache)

题目概述 (Problem Summary)
-------------------------
设计一个数据结构，实现 LRU (Least Recently Used，最近最少使用) 缓存机制。

需要实现以下操作：
- LRUCache(int capacity)：以正整数作为容量 capacity 初始化 LRU 缓存
- int get(int key)：如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1
- void put(int key, int value)：如果关键字已经存在，则变更其数据值；如果关键字不存在，则插入该组「关键字-值」。
  当缓存容量达到上限时，应该在写入新数据之前删除最久未使用的数据值。

关键约束 (Key Constraints)
-------------------------
- 1 <= capacity <= 3000
- 0 <= key <= 10^4
- 0 <= value <= 10^5
- 最多调用 2 * 10^5 次 get 和 put
- get 和 put 操作必须在 O(1) 时间复杂度内完成

示例 (Example)
-------------
输入：
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]

输出：
[null, null, null, 1, null, -1, null, -1, 3, 4]

解释：
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // 缓存是 {1=1}
lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
lRUCache.get(1);    // 返回 1
lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
lRUCache.get(2);    // 返回 -1 (未找到)
lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
lRUCache.get(1);    // 返回 -1 (未找到)
lRUCache.get(3);    // 返回 3
lRUCache.get(4);    // 返回 4

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 需要快速查找（O(1)）
- 需要快速插入和删除（O(1)）
- 需要维护访问顺序

关键观察：
1. 哈希表可以实现 O(1) 查找
2. 双向链表可以实现 O(1) 插入和删除
3. 结合两者：哈希表存储 key 到链表节点的映射
4. 链表维护访问顺序：最近使用的放在头部，最久未使用的在尾部

数据结构选择：
- 哈希表 (unordered_map)：key -> 链表迭代器
- 双向链表 (list)：存储 (key, value) 对，按访问时间排序
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <list>

using namespace std;

/*
方法一：我的原始解法 - 哈希表 + 双向链表 (Approach 1: My Original Solution - HashMap + Doubly Linked List)

核心思想
--------
使用 std::list (双向链表) 存储 (key, value) 对，最近使用的放在链表头部。
使用 std::unordered_map 存储 key 到链表迭代器的映射，实现 O(1) 查找。

数据结构：
- list<pair<int, int>> cache：双向链表，存储 (key, value)
  - 头部 (front)：最近使用
  - 尾部 (back)：最久未使用
- unordered_map<int, list<...>::iterator> map：哈希表，key -> 链表节点迭代器

操作流程：
1. get(key)：
   - 在 map 中查找 key
   - 如果不存在，返回 -1
   - 如果存在，将对应节点移到链表头部（标记为最近使用），返回 value

2. put(key, value)：
   - 如果 key 已存在：更新 value，将节点移到链表头部
   - 如果 key 不存在：
     a. 检查容量，如果已满，删除链表尾部节点（最久未使用）
     b. 在链表头部插入新节点
     c. 在 map 中记录映射关系

关键技巧：
- 使用 list::splice() 实现 O(1) 节点移动
- splice(pos, list, it) 将 it 指向的元素移动到 pos 位置

复杂度分析
---------
时间复杂度：O(1)
- get 操作：哈希表查找 O(1) + 链表移动 O(1)
- put 操作：哈希表查找/插入 O(1) + 链表插入/删除 O(1)

空间复杂度：O(capacity)
- 链表最多存储 capacity 个节点
- 哈希表最多存储 capacity 个映射
*/
class LRUCache {
private:
    int cap;  // 缓存容量

    // 双向链表，存储 pair<key, value>
    // 最近使用的放在 front，最久未使用的在 back
    std::list<std::pair<int, int>> cache;

    // 哈希表，存储 key 到链表迭代器的映射
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> map;

    // 辅助函数：将已存在的节点提升到"最近使用"状态
    // 即将节点移动到链表头部
    void makeRecently(int key) {
        auto it = map[key];  // 获取节点的迭代器
        // splice: 将 it 指向的元素从当前位置移动到 cache.begin() 位置
        // 时间复杂度 O(1)
        cache.splice(cache.begin(), cache, it);
    }

public:
    // 构造函数：初始化容量
    LRUCache(int capacity) : cap(capacity) {}

    // 获取 key 对应的 value
    int get(int key) {
        // 如果 key 不存在，返回 -1
        if (map.find(key) == map.end()) {
            return -1;
        }

        // key 存在：将其标记为最近使用
        makeRecently(key);

        // 返回 value
        return map[key]->second;
    }

    // 插入或更新 (key, value)
    void put(int key, int value) {
        // 情况 1：key 已存在
        if (map.find(key) != map.end()) {
            // 更新 value
            map[key]->second = value;
            // 提升为最近使用
            makeRecently(key);
            return;
        }

        // 情况 2：key 不存在
        // 检查容量是否已满
        if (cache.size() >= cap) {
            // 淘汰最久未使用的元素（链表尾部）
            int lastKey = cache.back().first;
            map.erase(lastKey);      // 从哈希表中删除
            cache.pop_back();        // 从链表中删除
        }

        // 插入新节点到链表头部（最近使用）
        cache.push_front({key, value});
        // 在哈希表中记录映射
        map[key] = cache.begin();
    }
};

/*
方法二：朴素实现 - 仅使用哈希表和列表 (Approach 2: Naive Implementation)

这是一个效率较低但更直观的实现，用于对比学习。

核心思想
--------
使用 unordered_map 存储 key-value，使用 list 存储 key 的访问顺序。
每次访问时，使用 list::remove() 删除旧位置，再 push_back() 到尾部。

问题：
- list::remove(key) 需要遍历整个链表，时间复杂度 O(n)
- 不满足题目要求的 O(1) 时间复杂度

复杂度分析
---------
时间复杂度：O(n)
- get 操作：O(1) 查找 + O(n) 删除
- put 操作：O(1) 插入 + O(n) 删除

空间复杂度：O(capacity)

这种方法不符合题目要求，但有助于理解为什么需要使用迭代器。
*/
class LRUCache_Naive {
public:
    int size = 0;
    unordered_map<int, int> Cache;  // key -> value
    list<int> keyList;              // 访问顺序，尾部是最近使用

    LRUCache_Naive(int capacity) {
        size = capacity;
    }

    int get(int key) {
        auto it = Cache.find(key);
        if (it != Cache.end()) {
            // 更新访问顺序：删除旧位置，添加到尾部
            // 问题：remove() 是 O(n) 操作
            keyList.remove(key);
            keyList.push_back(key);
            return it->second;
        }
        return -1;
    }

    void put(int key, int value) {
        auto it = Cache.find(key);
        if (it != Cache.end()) {
            // key 已存在：更新 value 和访问顺序
            it->second = value;
            keyList.remove(key);     // O(n)
            keyList.push_back(key);
        } else {
            // key 不存在：插入新元素
            Cache[key] = value;
            keyList.push_back(key);

            // 检查容量
            if (Cache.size() > size) {
                // 删除最久未使用的（链表头部）
                int delKey = keyList.front();
                keyList.pop_front();
                Cache.erase(delKey);
            }
        }
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
容量 capacity = 2

操作序列：
1. put(1, 1)
   cache: [(1,1)]
   map: {1 -> iter_to_(1,1)}

2. put(2, 2)
   cache: [(2,2), (1,1)]
   map: {1 -> iter, 2 -> iter}

3. get(1)
   返回 1
   cache: [(1,1), (2,2)]  // (1,1) 移到头部
   map: 不变

4. put(3, 3)
   容量已满，删除 (2,2)
   cache: [(3,3), (1,1)]
   map: {1 -> iter, 3 -> iter}

5. get(2)
   返回 -1（已被淘汰）

6. put(4, 4)
   容量已满，删除 (1,1)
   cache: [(4,4), (3,3)]
   map: {3 -> iter, 4 -> iter}
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：哈希表 + 双向链表（使用迭代器）
- 时间复杂度：O(1)
- 空间复杂度：O(capacity)
- 优点：满足题目要求，效率最高
- 缺点：实现稍复杂，需要理解迭代器和 splice

方法二：朴素实现（使用 remove）
- 时间复杂度：O(n)
- 空间复杂度：O(capacity)
- 优点：实现简单直观
- 缺点：不满足 O(1) 要求，效率低

关键优化点：
使用迭代器避免了 O(n) 的链表遍历，将时间复杂度从 O(n) 降低到 O(1)。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. capacity = 1：每次 put 都会淘汰旧元素
2. 重复 put 相同的 key：应该更新 value 并刷新访问时间
3. get 不存在的 key：返回 -1
4. 连续 get 同一个 key：不会改变缓存内容，但会刷新访问时间
*/

int main() {
    // 测试用例 1：基本操作
    LRUCache lRUCache(2);

    lRUCache.put(1, 1);
    lRUCache.put(2, 2);
    cout << "get(1): " << lRUCache.get(1) << " (期望: 1)" << endl;

    lRUCache.put(3, 3);  // 淘汰 key 2
    cout << "get(2): " << lRUCache.get(2) << " (期望: -1)" << endl;

    lRUCache.put(4, 4);  // 淘汰 key 1
    cout << "get(1): " << lRUCache.get(1) << " (期望: -1)" << endl;
    cout << "get(3): " << lRUCache.get(3) << " (期望: 3)" << endl;
    cout << "get(4): " << lRUCache.get(4) << " (期望: 4)" << endl;

    // 测试用例 2：容量为 1
    LRUCache cache2(1);
    cache2.put(2, 1);
    cout << "\n容量为 1 的测试:" << endl;
    cout << "get(2): " << cache2.get(2) << " (期望: 1)" << endl;
    cache2.put(3, 2);  // 淘汰 key 2
    cout << "get(2): " << cache2.get(2) << " (期望: -1)" << endl;
    cout << "get(3): " << cache2.get(3) << " (期望: 2)" << endl;

    return 0;
}
