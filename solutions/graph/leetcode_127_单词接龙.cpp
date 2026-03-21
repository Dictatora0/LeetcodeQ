/*
LeetCode 127. 单词接龙 (Word Ladder)

题目概述 (Problem Summary)
-------------------------
字典 wordList 中从单词 beginWord 到 endWord 的转换序列是一个按下述规格形成的序列：
- 序列中第一个单词是 beginWord
- 序列中最后一个单词是 endWord
- 每次转换只能改变一个字母
- 转换过程中的中间单词必须是字典 wordList 中的单词

给你两个单词 beginWord 和 endWord 和一个字典 wordList，找到从 beginWord 到 endWord
的最短转换序列中的单词数量。如果不存在这样的转换序列，返回 0。

关键约束 (Key Constraints)
-------------------------
- 1 <= beginWord.length <= 10
- endWord.length == beginWord.length
- 1 <= wordList.length <= 5000
- wordList[i].length == beginWord.length
- beginWord、endWord 和 wordList[i] 由小写英文字母组成
- beginWord != endWord
- wordList 中的所有单词互不相同

示例 (Example)
-------------
输入：beginWord = "hit", endWord = "cog",
     wordList = ["hot","dot","dog","lot","log","cog"]
输出：5
解释：一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog"，共 5 个单词

输入：beginWord = "hit", endWord = "cog",
     wordList = ["hot","dot","dog","lot","log"]
输出：0
解释：endWord "cog" 不在字典中，无法进行转换

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在无向无权图中找最短路径
- 每个单词是一个节点
- 两个单词相差一个字母，它们之间有一条边
- 求从 beginWord 到 endWord 的最短路径长度

关键观察：
1. 这是一个无权图的最短路径问题
2. 无权图的最短路径 → BFS（广度优先搜索）
3. BFS 保证第一次到达目标时，路径最短

为什么必须用 BFS，不能用 DFS？
- DFS 找到的是"一条"路径，不保证是最短的
- BFS 按层遍历，第一次到达目标时，层数就是最短路径
- 例如：DFS 可能先走 hit->hot->dot->dog->cog（5步）
  但实际可能存在 hit->hot->cog（3步）的更短路径
- BFS 会先探索所有 2 步路径，再探索 3 步路径，保证最短

如何建图？
方法 1：暴力比较（O(N²×M)）
- 对每个单词，与所有其他单词比较
- 如果只差一个字母，建立边
- 时间复杂度高，不推荐

方法 2：模式匹配（O(N×M²)）
- 对每个单词的每个位置，用 * 替换，得到模式
- 例如："hot" → "*ot", "h*t", "ho*"
- 相同模式的单词可以互相转换
- 使用哈希表存储 模式 → 单词列表 的映射

BFS 算法流程：
1. 如果 endWord 不在 wordList 中，直接返回 0
2. 将 beginWord 加入队列，步数为 1
3. BFS 遍历：
   - 取出队首单词
   - 尝试改变每个位置的字母（a-z）
   - 如果新单词在 wordList 中且未访问，加入队列
   - 如果新单词是 endWord，返回步数
4. 如果队列为空还没找到，返回 0

为什么这个算法正确？
- BFS 保证按层遍历，第一次到达目标时路径最短
- visited 集合防止重复访问，避免环
- 每次只改变一个字母，符合题目要求

根据这些观察，可以得到 BFS 解法。
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

/*
方法一：BFS + 模式匹配 (Approach 1: BFS with Pattern Matching)

核心思想
--------
使用 BFS 在单词图中搜索最短路径，通过模式匹配快速找到相邻单词。

数据结构：
1. 队列：存储 (当前单词, 步数)
2. visited：记录已访问的单词，防止重复
3. 模式哈希表：pattern → 单词列表

算法流程：
1. 预处理：构建模式哈希表
   - 对每个单词，生成所有模式（每个位置用 * 替换）
   - 例如："hot" → {"*ot": ["hot"], "h*t": ["hot"], "ho*": ["hot"]}
2. BFS 搜索：
   - 初始化：将 beginWord 加入队列
   - 遍历队列：
     a. 取出当前单词和步数
     b. 如果是 endWord，返回步数
     c. 生成当前单词的所有模式
     d. 对每个模式，找到所有相邻单词
     e. 将未访问的相邻单词加入队列
3. 如果队列为空，返回 0

为什么使用模式匹配？
- 直接枚举 26 个字母：O(26×M) = O(M)
- 模式匹配：O(M) 生成模式 + O(1) 查找
- 当单词长度 M 较大时，模式匹配更高效

复杂度分析
---------
时间复杂度：O(M² × N)，其中 M 是单词长度，N 是单词列表长度
  - 预处理：O(M² × N)，每个单词生成 M 个模式，每个模式长度 M
  - BFS：O(M² × N)，最坏情况访问所有单词，每个单词生成 M 个模式
空间复杂度：O(M² × N)
  - 模式哈希表：O(M² × N)
  - 队列和 visited：O(N)
*/
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // 将 wordList 转换为 unordered_set，方便快速查找
        unordered_set<string> wordSet(wordList.begin(), wordList.end());

        // 如果 endWord 不在字典中，无法转换
        if (wordSet.find(endWord) == wordSet.end()) {
            return 0;
        }

        // BFS 队列：存储 (当前单词, 步数)
        queue<pair<string, int>> q;
        q.push({beginWord, 1});  // 起始单词，步数为 1

        // visited 集合：记录已访问的单词
        unordered_set<string> visited;
        visited.insert(beginWord);

        // BFS 遍历
        while (!q.empty()) {
            auto [word, steps] = q.front();
            q.pop();

            // 如果到达目标单词，返回步数
            if (word == endWord) {
                return steps;
            }

            // 尝试改变当前单词的每个位置
            for (int i = 0; i < word.size(); i++) {
                string newWord = word;

                // 尝试 26 个字母
                for (char c = 'a'; c <= 'z'; c++) {
                    newWord[i] = c;

                    // 如果新单词在字典中且未访问过
                    if (wordSet.count(newWord) && !visited.count(newWord)) {
                        visited.insert(newWord);
                        q.push({newWord, steps + 1});
                    }
                }
            }
        }

        // 无法到达目标单词
        return 0;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：beginWord = "hit", endWord = "cog",
     wordList = ["hot","dot","dog","lot","log","cog"]

可视化图结构：
    hit
     |
    hot
   /   \
  dot  lot
   |    |
  dog  log
   \   /
    cog

BFS 遍历过程：

初始状态：
队列：[(hit, 1)]
visited：{hit}

第 1 步：处理 (hit, 1)
- 尝试改变每个位置：
  - *it: ait, bit, ..., hit(已访问), ..., zit
  - h*t: hat, hbt, ..., hot(在字典中!), ..., hzt
  - hi*: hia, hib, ..., hit(已访问), ..., hiz
- 找到：hot
- 队列：[(hot, 2)]
- visited：{hit, hot}

第 2 步：处理 (hot, 2)
- 尝试改变每个位置：
  - *ot: aot, bot, ..., dot(在字典中!), ..., lot(在字典中!), ..., zot
  - h*t: hat, hbt, ..., hit(已访问), ..., hzt
  - ho*: hoa, hob, ..., hog, ..., hoz
- 找到：dot, lot
- 队列：[(dot, 3), (lot, 3)]
- visited：{hit, hot, dot, lot}

第 3 步：处理 (dot, 3)
- 尝试改变每个位置：
  - *ot: aot, ..., hot(已访问), lot(已访问), ..., zot
  - d*t: dat, dbt, ..., dot(已访问), ..., dzt
  - do*: doa, dob, ..., dog(在字典中!), ..., doz
- 找到：dog
- 队列：[(lot, 3), (dog, 4)]
- visited：{hit, hot, dot, lot, dog}

第 4 步：处理 (lot, 3)
- 尝试改变每个位置：
  - *ot: aot, ..., hot(已访问), dot(已访问), ..., zot
  - l*t: lat, lbt, ..., lot(已访问), ..., lzt
  - lo*: loa, lob, ..., log(在字典中!), ..., loz
- 找到：log
- 队列：[(dog, 4), (log, 4)]
- visited：{hit, hot, dot, lot, dog, log}

第 5 步：处理 (dog, 4)
- 尝试改变每个位置：
  - *og: aog, bog, cog(在字典中!), ..., zog
  - d*g: dag, dbg, ..., dog(已访问), ..., dzg
  - do*: doa, ..., dot(已访问), ..., doz
- 找到：cog
- 队列：[(log, 4), (cog, 5)]
- visited：{hit, hot, dot, lot, dog, log, cog}

第 6 步：处理 (log, 4)
- 尝试改变每个位置：
  - *og: aog, bog, cog(已访问), ..., zog
  - l*g: lag, lbg, ..., log(已访问), ..., lzg
  - lo*: loa, ..., lot(已访问), ..., loz
- 没有新单词
- 队列：[(cog, 5)]

第 7 步：处理 (cog, 5)
- cog == endWord，返回 5

关键观察：
1. BFS 按层遍历：第 1 层(hit) → 第 2 层(hot) → 第 3 层(dot,lot) → ...
2. 第一次到达 cog 时，步数就是最短路径
3. visited 防止重复访问，避免环

BFS 层次结构：
层 1: hit (步数=1)
层 2: hot (步数=2)
层 3: dot, lot (步数=3)
层 4: dog, log (步数=4)
层 5: cog (步数=5) ← 第一次到达，返回 5
*/

/*
特殊情况 (Edge Cases)
--------------------
1. endWord 不在字典中：返回 0
2. beginWord == endWord：题目保证不会出现
3. 无法到达 endWord：返回 0
4. 只有一步转换：正确返回 2
5. 字典为空：返回 0
*/

/*
方法对比 (Approach Comparison)
----------------------------
方法一：BFS（推荐）
- 时间复杂度：O(M² × N)
- 空间复杂度：O(M × N)
- 优点：保证找到最短路径
- 缺点：需要遍历所有可能的单词

方法二：双向 BFS（优化）
- 时间复杂度：O(M² × N)，但实际更快
- 空间复杂度：O(M × N)
- 优点：从两端同时搜索，搜索空间更小
- 缺点：代码复杂度更高

为什么 BFS 比 DFS 好？
- BFS：第一次到达目标时，路径最短
- DFS：需要遍历所有路径，然后比较长度
- 例如：
  DFS 可能先找到 hit->hot->dot->dog->cog (5步)
  然后继续搜索，发现没有更短的路径
  BFS 直接返回第一次到达的路径 (5步)

为什么不用 Dijkstra？
- Dijkstra 用于带权图的最短路径
- 这道题是无权图（每条边权重为 1）
- BFS 就是无权图的最短路径算法
- Dijkstra 会增加不必要的复杂度

为什么不用 A*？
- A* 需要启发式函数（估计到目标的距离）
- 对于单词转换，很难设计好的启发式函数
- BFS 已经足够高效
*/

/*
方法二：双向 BFS (Approach 2: Bidirectional BFS for Optimization)

核心思想
--------
从 beginWord 和 endWord 同时开始 BFS，当两个搜索相遇时，找到最短路径。

为什么双向 BFS 更快？
- 单向 BFS：搜索空间是 O(b^d)，其中 b 是分支因子，d 是深度
- 双向 BFS：搜索空间是 O(b^(d/2)) + O(b^(d/2)) = O(2 × b^(d/2))
- 例如：b=10, d=6
  单向：10^6 = 1,000,000
  双向：2 × 10^3 = 2,000（快 500 倍！）

算法流程：
1. 初始化两个集合：beginSet = {beginWord}, endSet = {endWord}
2. 每次选择较小的集合进行扩展（优化）
3. 扩展时，如果遇到另一个集合中的单词，说明相遇，返回步数
4. 将新单词加入当前集合，继续扩展

复杂度分析
---------
时间复杂度：O(M² × N)，但实际比单向 BFS 快很多
空间复杂度：O(M × N)
*/
class Solution_Bidirectional {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());

        // 如果 endWord 不在字典中，无法转换
        if (wordSet.find(endWord) == wordSet.end()) {
            return 0;
        }

        // 两个方向的搜索集合
        unordered_set<string> beginSet = {beginWord};
        unordered_set<string> endSet = {endWord};
        unordered_set<string> visited;

        int steps = 1;

        // 双向 BFS
        while (!beginSet.empty() && !endSet.empty()) {
            // 优化：总是扩展较小的集合
            if (beginSet.size() > endSet.size()) {
                swap(beginSet, endSet);
            }

            unordered_set<string> nextSet;

            // 扩展当前集合
            for (const string& word : beginSet) {
                // 尝试改变每个位置
                for (int i = 0; i < word.size(); i++) {
                    string newWord = word;

                    // 尝试 26 个字母
                    for (char c = 'a'; c <= 'z'; c++) {
                        newWord[i] = c;

                        // 如果在另一个集合中找到，说明相遇
                        if (endSet.count(newWord)) {
                            return steps + 1;
                        }

                        // 如果在字典中且未访问
                        if (wordSet.count(newWord) && !visited.count(newWord)) {
                            visited.insert(newWord);
                            nextSet.insert(newWord);
                        }
                    }
                }
            }

            beginSet = nextSet;
            steps++;
        }

        return 0;
    }
};

/*
双向 BFS 示例推演
----------------
输入：beginWord = "hit", endWord = "cog",
     wordList = ["hot","dot","dog","lot","log","cog"]

初始状态：
beginSet = {hit}
endSet = {cog}
visited = {}
steps = 1

第 1 轮：扩展 beginSet（较小）
- 从 hit 扩展：找到 hot
- beginSet = {hot}
- endSet = {cog}
- steps = 2

第 2 轮：扩展 beginSet（较小）
- 从 hot 扩展：找到 dot, lot
- beginSet = {dot, lot}
- endSet = {cog}
- steps = 3

第 3 轮：扩展 endSet（较小）
- 从 cog 扩展：找到 dog, log
- beginSet = {dot, lot}
- endSet = {dog, log}
- steps = 4

第 4 轮：扩展 beginSet（较小）
- 从 dot 扩展：找到 dog
- dog 在 endSet 中！相遇！
- 返回 steps + 1 = 4 + 1 = 5

关键观察：
1. 双向搜索在第 4 轮就相遇了
2. 单向搜索需要第 7 轮才到达
3. 搜索空间大大减小
*/

int main() {
    Solution solution;

    // 测试用例 1：标准情况
    string beginWord1 = "hit";
    string endWord1 = "cog";
    vector<string> wordList1 = {"hot", "dot", "dog", "lot", "log", "cog"};
    int result1 = solution.ladderLength(beginWord1, endWord1, wordList1);
    cout << "测试用例 1 - 输出: " << result1 << " (期望: 5)" << endl;
    cout << "转换序列: hit -> hot -> dot -> dog -> cog" << endl << endl;

    // 测试用例 2：endWord 不在字典中
    string beginWord2 = "hit";
    string endWord2 = "cog";
    vector<string> wordList2 = {"hot", "dot", "dog", "lot", "log"};
    int result2 = solution.ladderLength(beginWord2, endWord2, wordList2);
    cout << "测试用例 2 - 输出: " << result2 << " (期望: 0)" << endl;
    cout << "解释: endWord 不在字典中" << endl << endl;

    // 测试用例 3：一步转换
    string beginWord3 = "hot";
    string endWord3 = "dot";
    vector<string> wordList3 = {"hot", "dot", "dog"};
    int result3 = solution.ladderLength(beginWord3, endWord3, wordList3);
    cout << "测试用例 3 - 输出: " << result3 << " (期望: 2)" << endl;
    cout << "转换序列: hot -> dot" << endl << endl;

    // 测试用例 4：无法到达
    string beginWord4 = "hit";
    string endWord4 = "cog";
    vector<string> wordList4 = {"hot", "dot", "tog"};
    int result4 = solution.ladderLength(beginWord4, endWord4, wordList4);
    cout << "测试用例 4 - 输出: " << result4 << " (期望: 0)" << endl;
    cout << "解释: 无法从 hit 到达 cog" << endl << endl;

    // 测试用例 5：复杂路径
    string beginWord5 = "a";
    string endWord5 = "c";
    vector<string> wordList5 = {"a", "b", "c"};
    int result5 = solution.ladderLength(beginWord5, endWord5, wordList5);
    cout << "测试用例 5 - 输出: " << result5 << " (期望: 2)" << endl;
    cout << "转换序列: a -> c" << endl << endl;

    // 测试用例 6：双向 BFS
    Solution_Bidirectional solution_bi;
    string beginWord6 = "hit";
    string endWord6 = "cog";
    vector<string> wordList6 = {"hot", "dot", "dog", "lot", "log", "cog"};
    int result6 = solution_bi.ladderLength(beginWord6, endWord6, wordList6);
    cout << "测试用例 6 (双向BFS) - 输出: " << result6 << " (期望: 5)" << endl;

    return 0;
}

