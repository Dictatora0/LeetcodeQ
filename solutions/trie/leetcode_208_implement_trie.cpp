/*
LeetCode 208. 实现 Trie (前缀树) (Implement Trie - Prefix Tree)

题目概述 (Problem Summary)
-------------------------
Trie（发音类似 "try"）或者说前缀树是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。
这一数据结构有相当多的应用情景，例如自动补全和拼写检查。

请你实现 Trie 类：
- Trie() 初始化前缀树对象
- void insert(String word) 向前缀树中插入字符串 word
- boolean search(String word) 如果字符串 word 在前缀树中，返回 true；否则，返回 false
- boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix，返回 true；否则，返回 false

关键约束 (Key Constraints)
-------------------------
- 1 <= word.length, prefix.length <= 2000
- word 和 prefix 仅由小写英文字母组成
- insert、search 和 startsWith 调用次数总计不超过 3 * 10^4 次

示例 (Example)
-------------
输入：
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
输出：
[null, null, true, false, true, null, true]

解释：
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // 返回 True
trie.search("app");     // 返回 False
trie.startsWith("app"); // 返回 True
trie.insert("app");
trie.search("app");     // 返回 True

算法思路 (Algorithm Thinking)
----------------------------
什么是 Trie（前缀树）？
- Trie 是一种多叉树结构，专门用于处理字符串
- 每个节点代表一个字符，从根到某个节点的路径表示一个字符串前缀
- 根节点不包含字符，每条边代表一个字符

Trie 的核心特点：
1. 根节点不包含字符，除根节点外每个节点都包含一个字符
2. 从根节点到某一节点，路径上经过的字符连接起来，为该节点对应的字符串
3. 每个节点的所有子节点包含的字符都不相同
4. 节点需要标记是否为某个单词的结尾

Trie 的优势：
1. 查找效率高：O(m)，m 是字符串长度，与存储的字符串数量无关
2. 前缀匹配：天然支持前缀查询
3. 空间共享：公共前缀只存储一次

Trie 的应用场景：
1. 自动补全（搜索引擎、输入法）
2. 拼写检查
3. IP 路由（最长前缀匹配）
4. 字符串排序
5. 词频统计

Trie 的结构示例（插入 "apple", "app", "application"）：
        root
         |
         a
         |
         p
         |
         p (isEnd=true for "app")
        / \
       l   l
       |   |
       e   i
       |   |
    (isEnd) c
       |    |
    "apple" a
            |
            t
            |
            i
            |
            o
            |
            n (isEnd=true for "application")
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*
方法一：数组实现 (Approach 1: Array Implementation)

核心思想
--------
使用固定大小的数组存储子节点，数组索引对应字符。

数据结构设计：
1. children[26]：存储 26 个小写字母对应的子节点
   - children[0] 对应 'a'
   - children[1] 对应 'b'
   - ...
   - children[25] 对应 'z'
2. isEnd：标记当前节点是否为某个单词的结尾

算法流程：

insert(word)：
1. 从根节点开始
2. 对于 word 中的每个字符 c：
   a. 计算索引：idx = c - 'a'
   b. 如果 children[idx] 为空，创建新节点
   c. 移动到 children[idx]
3. 标记最后一个节点的 isEnd = true

search(word)：
1. 从根节点开始
2. 对于 word 中的每个字符 c：
   a. 计算索引：idx = c - 'a'
   b. 如果 children[idx] 为空，返回 false
   c. 移动到 children[idx]
3. 返回最后一个节点的 isEnd

startsWith(prefix)：
1. 与 search 类似
2. 但不需要检查 isEnd，只要能走到最后就返回 true

复杂度分析
---------
时间复杂度：
- insert：O(m)，m 是字符串长度
- search：O(m)
- startsWith：O(m)

空间复杂度：O(n * m * 26)
- n 是插入的字符串数量
- m 是平均字符串长度
- 每个节点需要 26 个指针
- 实际空间取决于公共前缀的数量，通常远小于理论值

其中：
m = word.length
n = 插入的字符串数量
*/
class Trie {
public:
    // children[i] 指向字符 ('a' + i) 对应的子节点
    Trie* children[26];

    // isEnd 标记当前节点是否为某个单词的结尾
    bool isEnd;

    // 构造函数：初始化 Trie 节点
    Trie() {
        isEnd = false;

        // 初始化所有子节点为空
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }

    // 插入字符串 word
    void insert(string word) {
        Trie* node = this;  // 从根节点开始

        // 遍历 word 的每个字符
        for (char c : word) {
            int idx = c - 'a';  // 计算字符对应的索引

            // 如果对应的子节点不存在，创建新节点
            if (node->children[idx] == nullptr) {
                node->children[idx] = new Trie();
            }

            // 移动到子节点
            node = node->children[idx];
        }

        // 标记单词结尾
        node->isEnd = true;
    }

    // 搜索字符串 word 是否存在
    bool search(string word) {
        Trie* node = this;  // 从根节点开始

        // 遍历 word 的每个字符
        for (char c : word) {
            int idx = c - 'a';

            // 如果对应的子节点不存在，说明 word 不在 Trie 中
            if (node->children[idx] == nullptr) {
                return false;
            }

            // 移动到子节点
            node = node->children[idx];
        }

        // 检查最后一个节点是否为单词结尾
        return node->isEnd;
    }

    // 检查是否存在以 prefix 为前缀的字符串
    bool startsWith(string prefix) {
        Trie* node = this;  // 从根节点开始

        // 遍历 prefix 的每个字符
        for (char c : prefix) {
            int idx = c - 'a';

            // 如果对应的子节点不存在，说明不存在该前缀
            if (node->children[idx] == nullptr) {
                return false;
            }

            // 移动到子节点
            node = node->children[idx];
        }

        // 只要能走到最后，就说明存在该前缀
        return true;
    }
};

/*
方法二：哈希表实现 (Approach 2: HashMap Implementation)

核心思想
--------
使用哈希表（unordered_map）存储子节点，更节省空间。

优点：
- 空间效率更高，只存储实际存在的字符
- 支持任意字符集（不限于小写字母）

缺点：
- 哈希表的常数因子较大，实际性能可能略低于数组实现
- 代码稍微复杂一些

复杂度分析
---------
时间复杂度：
- insert：O(m)
- search：O(m)
- startsWith：O(m)

空间复杂度：O(n * m * k)
- k 是实际使用的字符种类数，通常远小于 26
- 比数组实现更节省空间
*/
#include <unordered_map>

class Trie_HashMap {
public:
    unordered_map<char, Trie_HashMap*> children;
    bool isEnd;

    Trie_HashMap() {
        isEnd = false;
    }

    void insert(string word) {
        Trie_HashMap* node = this;

        for (char c : word) {
            // 如果字符不存在，创建新节点
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new Trie_HashMap();
            }

            node = node->children[c];
        }

        node->isEnd = true;
    }

    bool search(string word) {
        Trie_HashMap* node = this;

        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }

            node = node->children[c];
        }

        return node->isEnd;
    }

    bool startsWith(string prefix) {
        Trie_HashMap* node = this;

        for (char c : prefix) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }

            node = node->children[c];
        }

        return true;
    }
};

/*
扩展功能：删除操作 (Extended Feature: Delete Operation)

核心思想
--------
删除操作比插入和查找复杂，需要考虑多种情况。

删除的三种情况：
1. 要删除的单词是另一个单词的前缀
   - 例如：删除 "app"，但 "apple" 仍存在
   - 只需将 "app" 最后一个节点的 isEnd 设为 false

2. 要删除的单词有其他单词作为前缀
   - 例如：删除 "apple"，但 "app" 仍存在
   - 只能删除 "apple" 独有的节点（"le" 部分）

3. 要删除的单词独立存在
   - 可以删除整条路径（如果路径上的节点没有其他子节点）

算法流程：
使用递归实现，从叶子节点向根节点回溯删除。
*/
class Trie_WithDelete {
public:
    Trie_WithDelete* children[26];
    bool isEnd;

    Trie_WithDelete() {
        isEnd = false;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }

    void insert(string word) {
        Trie_WithDelete* node = this;
        for (char c : word) {
            int idx = c - 'a';
            if (node->children[idx] == nullptr) {
                node->children[idx] = new Trie_WithDelete();
            }
            node = node->children[idx];
        }
        node->isEnd = true;
    }

    bool search(string word) {
        Trie_WithDelete* node = this;
        for (char c : word) {
            int idx = c - 'a';
            if (node->children[idx] == nullptr) {
                return false;
            }
            node = node->children[idx];
        }
        return node->isEnd;
    }

    bool startsWith(string prefix) {
        Trie_WithDelete* node = this;
        for (char c : prefix) {
            int idx = c - 'a';
            if (node->children[idx] == nullptr) {
                return false;
            }
            node = node->children[idx];
        }
        return true;
    }

    // 删除单词
    // 返回 true 表示当前节点可以被删除
    bool deleteHelper(Trie_WithDelete* node, string& word, int index) {
        if (index == word.length()) {
            // 到达单词末尾
            if (!node->isEnd) {
                return false;  // 单词不存在
            }

            node->isEnd = false;  // 取消单词结尾标记

            // 如果当前节点没有子节点，可以删除
            return !hasChildren(node);
        }

        int idx = word[index] - 'a';
        Trie_WithDelete* child = node->children[idx];

        if (child == nullptr) {
            return false;  // 单词不存在
        }

        // 递归删除
        bool shouldDeleteChild = deleteHelper(child, word, index + 1);

        if (shouldDeleteChild) {
            delete node->children[idx];
            node->children[idx] = nullptr;

            // 如果当前节点不是单词结尾且没有其他子节点，可以删除
            return !node->isEnd && !hasChildren(node);
        }

        return false;
    }

    // 检查节点是否有子节点
    bool hasChildren(Trie_WithDelete* node) {
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) {
                return true;
            }
        }
        return false;
    }

    void deleteWord(string word) {
        deleteHelper(this, word, 0);
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
操作序列：
1. insert("apple")
2. search("apple")  -> true
3. search("app")    -> false
4. startsWith("app") -> true
5. insert("app")
6. search("app")    -> true

Trie 结构变化：

1. insert("apple")：
        root
         |
         a
         |
         p
         |
         p
         |
         l
         |
         e (isEnd=true)

2. search("apple")：
   - 从 root 开始，依次访问 a -> p -> p -> l -> e
   - 最后节点 isEnd=true，返回 true

3. search("app")：
   - 从 root 开始，依次访问 a -> p -> p
   - 最后节点 isEnd=false，返回 false

4. startsWith("app")：
   - 从 root 开始，依次访问 a -> p -> p
   - 能够走到最后，返回 true

5. insert("app")：
        root
         |
         a
         |
         p
         |
         p (isEnd=true)
         |
         l
         |
         e (isEnd=true)

6. search("app")：
   - 从 root 开始，依次访问 a -> p -> p
   - 最后节点 isEnd=true，返回 true
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
数组实现 vs 哈希表实现：

数组实现：
- 时间复杂度：O(m)，常数因子小
- 空间复杂度：O(n * m * 26)，可能浪费空间
- 优点：访问速度快，代码简单
- 缺点：空间效率低，只支持固定字符集

哈希表实现：
- 时间复杂度：O(m)，常数因子稍大
- 空间复杂度：O(n * m * k)，k 是实际字符种类数
- 优点：空间效率高，支持任意字符集
- 缺点：哈希表开销较大

Trie vs 哈希表（用于字符串存储）：
- Trie 优势：前缀查询 O(m)，哈希表无法高效支持
- 哈希表优势：精确查询常数更小，空间效率可能更高
- 选择依据：如果需要前缀查询，用 Trie；否则用哈希表
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空字符串：根据题目约束，不会出现
2. 单字符：正常处理
3. 重复插入：不影响结果，isEnd 保持 true
4. 删除不存在的单词：返回 false，不影响 Trie 结构
5. 前缀是完整单词：需要正确区分（通过 isEnd 标记）
*/

/*
Trie 优化技巧 (Trie Optimization Techniques)
------------------------------------------
1. 路径压缩（Radix Tree）：
   - 将只有一个子节点的节点链压缩成一个节点
   - 节点存储字符串而不是单个字符
   - 减少节点数量，节省空间

2. 双数组 Trie（Double-Array Trie）：
   - 使用两个数组 base 和 check 实现
   - 空间效率高，访问速度快
   - 实现复杂，适合静态 Trie

3. 三叉树 Trie（Ternary Search Tree）：
   - 每个节点最多三个子节点：小于、等于、大于
   - 空间效率介于 Trie 和 BST 之间
   - 适合字符集较大的情况

4. 懒删除：
   - 删除时只标记 isEnd=false，不实际删除节点
   - 简化删除操作，但可能浪费空间
   - 适合删除操作较少的场景
*/

int main() {
    Trie trie;

    // 测试用例 1：基本操作
    cout << "=== 测试用例 1：基本操作 ===" << endl;
    trie.insert("apple");
    cout << "插入 'apple'" << endl;

    cout << "搜索 'apple': " << (trie.search("apple") ? "true" : "false") << " (期望: true)" << endl;
    cout << "搜索 'app': " << (trie.search("app") ? "true" : "false") << " (期望: false)" << endl;
    cout << "前缀 'app': " << (trie.startsWith("app") ? "true" : "false") << " (期望: true)" << endl;

    trie.insert("app");
    cout << "插入 'app'" << endl;
    cout << "搜索 'app': " << (trie.search("app") ? "true" : "false") << " (期望: true)" << endl;
    cout << endl;

    // 测试用例 2：多个单词
    cout << "=== 测试用例 2：多个单词 ===" << endl;
    Trie trie2;
    trie2.insert("hello");
    trie2.insert("world");
    trie2.insert("hell");

    cout << "搜索 'hello': " << (trie2.search("hello") ? "true" : "false") << " (期望: true)" << endl;
    cout << "搜索 'world': " << (trie2.search("world") ? "true" : "false") << " (期望: true)" << endl;
    cout << "搜索 'hell': " << (trie2.search("hell") ? "true" : "false") << " (期望: true)" << endl;
    cout << "搜索 'hel': " << (trie2.search("hel") ? "true" : "false") << " (期望: false)" << endl;
    cout << "前缀 'hel': " << (trie2.startsWith("hel") ? "true" : "false") << " (期望: true)" << endl;
    cout << "前缀 'wor': " << (trie2.startsWith("wor") ? "true" : "false") << " (期望: true)" << endl;
    cout << "前缀 'abc': " << (trie2.startsWith("abc") ? "true" : "false") << " (期望: false)" << endl;
    cout << endl;

    // 测试用例 3：带删除功能的 Trie
    cout << "=== 测试用例 3：删除操作 ===" << endl;
    Trie_WithDelete trie3;
    trie3.insert("apple");
    trie3.insert("app");
    trie3.insert("application");

    cout << "插入 'apple', 'app', 'application'" << endl;
    cout << "搜索 'app': " << (trie3.search("app") ? "true" : "false") << " (期望: true)" << endl;

    trie3.deleteWord("app");
    cout << "删除 'app'" << endl;
    cout << "搜索 'app': " << (trie3.search("app") ? "true" : "false") << " (期望: false)" << endl;
    cout << "搜索 'apple': " << (trie3.search("apple") ? "true" : "false") << " (期望: true)" << endl;
    cout << "搜索 'application': " << (trie3.search("application") ? "true" : "false") << " (期望: true)" << endl;

    return 0;
}
