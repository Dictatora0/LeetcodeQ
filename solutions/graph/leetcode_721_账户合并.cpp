/*
LeetCode 721. 账户合并 (Accounts Merge)

题目概述 (Problem Summary)
-------------------------
给定一个列表 accounts，每个元素 accounts[i] 是一个字符串列表，其中第一个元素
accounts[i][0] 是名称 (name)，其余元素是 emails 表示该账户的邮箱地址。

现在，我们想合并这些账户。如果两个账户都有一些共同的邮箱地址，则两个账户必定属于
同一个人。请注意，即使两个账户具有相同的名称，它们也可能属于不同的人，因为人们可能
具有相同的名称。一个人最初可以拥有任意数量的账户，但其所有账户都具有相同的名称。

合并账户后，按以下格式返回账户：每个账户的第一个元素是名称，其余元素是按字符顺序
排列的邮箱地址。账户本身可以以任意顺序返回。

关键约束 (Key Constraints)
-------------------------
- accounts.length <= 1000
- 2 <= accounts[i].length <= 10
- 1 <= accounts[i][j].length <= 30
- accounts[i][0] 由英文字母组成
- accounts[i][j] (for j > 0) 是有效的邮箱地址

示例 (Example)
-------------
输入：
accounts = [["John","johnsmith@mail.com","john_newyork@mail.com"],
            ["John","johnsmith@mail.com","john00@mail.com"],
            ["Mary","mary@mail.com"],
            ["John","johnnybravo@mail.com"]]

输出：
[["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],
 ["Mary","mary@mail.com"],
 ["John","johnnybravo@mail.com"]]

解释：
第一个和第二个 John 是同一个人，因为他们有共同的邮箱 "johnsmith@mail.com"。
第三个 John 和 Mary 是不同的人，因为他们的邮箱地址中没有被其他账户使用。
可以以任何顺序返回这些列表，例如答案 [['Mary', 'mary@mail.com'], ['John',
'johnnybravo@mail.com'], ['John', 'john00@mail.com', 'john_newyork@mail.com',
'johnsmith@mail.com']] 也是正确的。

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 根据共同的邮箱地址，将账户分组
- 这是一个连通性问题：如果两个账户有共同邮箱，它们连通
- 需要找到所有连通分量

关键观察：
1. 这是一个图的连通性问题
2. 如果两个账户有共同邮箱，它们属于同一个人
3. 传递性：A 和 B 有共同邮箱，B 和 C 有共同邮箱，则 A、B、C 属于同一个人
4. Union Find（并查集）天然支持传递性合并

为什么使用 Union Find？
- 需要动态合并集合（账户）
- 需要查询两个元素是否在同一集合
- Union Find 的时间复杂度接近 O(1)
- 完美匹配这道题的需求

如何建模？
错误建模：以账户为节点
- 问题：如何判断两个账户是否有共同邮箱？需要 O(n²) 比较

正确建模：以邮箱为节点
- 每个邮箱是一个节点
- 同一个账户中的邮箱互相连通
- 使用 Union Find 合并同一账户中的邮箱
- 最后，属于同一集合的邮箱属于同一个人

算法流程：
阶段 1：构建 Union Find
1. 遍历所有账户
2. 对于每个账户，将其所有邮箱合并到同一集合
3. 记录每个邮箱对应的账户名

阶段 2：收集结果
1. 遍历所有邮箱
2. 找到每个邮箱的根节点（集合代表）
3. 将邮箱加入对应集合
4. 对每个集合的邮箱排序
5. 添加账户名，返回结果

为什么这个算法正确？
- Union Find 保证传递性：A-B, B-C → A-C
- 同一集合的邮箱属于同一个人
- 排序保证输出格式正确

根据这些观察，可以得到 Union Find 解法。
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

/*
方法一：Union Find + 邮箱映射 (Approach 1: Union Find with Email Mapping)

核心思想
--------
使用并查集以邮箱为单位进行合并，最后收集属于同一集合的邮箱。

数据结构：
1. parent：并查集的父节点数组（以邮箱为索引）
2. emailToId：邮箱 → ID 的映射
3. emailToName：邮箱 → 账户名的映射

算法流程：
阶段 1：构建并查集
1. 遍历所有账户
2. 为每个邮箱分配唯一 ID
3. 将同一账户中的所有邮箱合并
   - 将第 2 个邮箱与第 1 个邮箱合并
   - 将第 3 个邮箱与第 1 个邮箱合并
   - ...
4. 记录每个邮箱对应的账户名

阶段 2：收集结果
1. 遍历所有邮箱
2. 找到每个邮箱的根节点
3. 将邮箱加入根节点对应的集合
4. 对每个集合：
   - 对邮箱排序
   - 添加账户名
   - 加入结果

为什么以第一个邮箱为代表？
- 同一账户中的邮箱需要合并
- 选择第一个邮箱作为代表，其他邮箱都与它合并
- 这样可以保证同一账户的所有邮箱在同一集合

复杂度分析
---------
时间复杂度：O(N × K × α(N) + N × K × log(K))，其中 N 是账户数，K 是平均邮箱数
  - 构建并查集：O(N × K × α(N))
  - 排序邮箱：O(N × K × log(K))
空间复杂度：O(N × K)
  - 并查集：O(N × K)
  - 哈希表：O(N × K)
*/
class UnionFind {
public:
    vector<int> parent;
    vector<int> rank;

    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // 查找操作：路径压缩
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // 合并操作：按秩合并
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) {
            return;
        }

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        // 邮箱 → ID 的映射
        unordered_map<string, int> emailToId;
        // 邮箱 → 账户名的映射
        unordered_map<string, string> emailToName;

        int emailCount = 0;

        // 阶段 1：构建并查集
        // 遍历所有账户，为每个邮箱分配 ID
        for (const auto& account : accounts) {
            string name = account[0];

            // 遍历账户中的所有邮箱
            for (int i = 1; i < account.size(); i++) {
                string email = account[i];

                // 如果邮箱第一次出现，分配新 ID
                if (emailToId.find(email) == emailToId.end()) {
                    emailToId[email] = emailCount++;
                    emailToName[email] = name;
                }
            }
        }

        // 创建并查集
        UnionFind uf(emailCount);

        // 合并同一账户中的邮箱
        for (const auto& account : accounts) {
            // 将账户中的所有邮箱与第一个邮箱合并
            int firstEmailId = emailToId[account[1]];

            for (int i = 2; i < account.size(); i++) {
                int emailId = emailToId[account[i]];
                uf.unite(firstEmailId, emailId);
            }
        }

        // 阶段 2：收集结果
        // 根节点 → 邮箱列表的映射
        unordered_map<int, vector<string>> components;

        // 遍历所有邮箱，按根节点分组
        for (const auto& [email, id] : emailToId) {
            int root = uf.find(id);
            components[root].push_back(email);
        }

        // 构建最终结果
        vector<vector<string>> result;

        for (auto& [root, emails] : components) {
            // 对邮箱排序
            sort(emails.begin(), emails.end());

            // 添加账户名
            vector<string> account;
            account.push_back(emailToName[emails[0]]);

            // 添加所有邮箱
            for (const string& email : emails) {
                account.push_back(email);
            }

            result.push_back(account);
        }

        return result;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：
accounts = [["John","johnsmith@mail.com","john_newyork@mail.com"],
            ["John","johnsmith@mail.com","john00@mail.com"],
            ["Mary","mary@mail.com"],
            ["John","johnnybravo@mail.com"]]

阶段 1：构建并查集

步骤 1：分配邮箱 ID
emailToId = {
    "johnsmith@mail.com": 0,
    "john_newyork@mail.com": 1,
    "john00@mail.com": 2,
    "mary@mail.com": 3,
    "johnnybravo@mail.com": 4
}

emailToName = {
    "johnsmith@mail.com": "John",
    "john_newyork@mail.com": "John",
    "john00@mail.com": "John",
    "mary@mail.com": "Mary",
    "johnnybravo@mail.com": "John"
}

初始并查集：
parent: [0, 1, 2, 3, 4]
rank:   [1, 1, 1, 1, 1]

可视化：
  0   1   2   3   4
  ↓   ↓   ↓   ↓   ↓
  0   1   2   3   4

步骤 2：处理第一个账户 ["John","johnsmith@mail.com","john_newyork@mail.com"]
- 第一个邮箱：johnsmith@mail.com (ID=0)
- 第二个邮箱：john_newyork@mail.com (ID=1)
- 合并：unite(0, 1)

parent: [0, 0, 2, 3, 4]
rank:   [2, 1, 1, 1, 1]

可视化：
    0   2   3   4
   / \  ↓   ↓   ↓
  0   1 2   3   4

步骤 3：处理第二个账户 ["John","johnsmith@mail.com","john00@mail.com"]
- 第一个邮箱：johnsmith@mail.com (ID=0)
- 第二个邮箱：john00@mail.com (ID=2)
- 合并：unite(0, 2)

parent: [0, 0, 0, 3, 4]
rank:   [2, 1, 1, 1, 1]

可视化：
      0       3   4
    / | \     ↓   ↓
   0  1  2    3   4

步骤 4：处理第三个账户 ["Mary","mary@mail.com"]
- 只有一个邮箱，不需要合并

步骤 5：处理第四个账户 ["John","johnnybravo@mail.com"]
- 只有一个邮箱，不需要合并

最终并查集：
parent: [0, 0, 0, 3, 4]

可视化：
      0       3   4
    / | \     ↓   ↓
   0  1  2    3   4

阶段 2：收集结果

步骤 1：按根节点分组
- johnsmith@mail.com (ID=0) → root=0
- john_newyork@mail.com (ID=1) → root=0
- john00@mail.com (ID=2) → root=0
- mary@mail.com (ID=3) → root=3
- johnnybravo@mail.com (ID=4) → root=4

components = {
    0: ["johnsmith@mail.com", "john_newyork@mail.com", "john00@mail.com"],
    3: ["mary@mail.com"],
    4: ["johnnybravo@mail.com"]
}

步骤 2：排序并添加账户名
- 根节点 0：
  排序：["john00@mail.com", "john_newyork@mail.com", "johnsmith@mail.com"]
  添加名称：["John", "john00@mail.com", "john_newyork@mail.com", "johnsmith@mail.com"]

- 根节点 3：
  排序：["mary@mail.com"]
  添加名称：["Mary", "mary@mail.com"]

- 根节点 4：
  排序：["johnnybravo@mail.com"]
  添加名称：["John", "johnnybravo@mail.com"]

最终结果：
[["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],
 ["Mary","mary@mail.com"],
 ["John","johnnybravo@mail.com"]]

关键观察：
1. 第一个和第二个 John 被合并（共同邮箱 johnsmith@mail.com）
2. 第三个 John 独立（没有共同邮箱）
3. Mary 独立
4. Union Find 自动处理传递性
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 单个账户：正确返回
2. 所有账户独立：每个账户单独返回
3. 所有账户属于同一人：合并为一个账户
4. 传递性合并：A-B, B-C → A-B-C
5. 相同名字不同人：正确区分
*/

/*
方法对比 (Approach Comparison)
----------------------------
方法一：Union Find（推荐）
- 时间复杂度：O(N × K × α(N) + N × K × log(K))
- 空间复杂度：O(N × K)
- 优点：代码清晰，自动处理传递性
- 缺点：需要额外的并查集数据结构

方法二：DFS
- 时间复杂度：O(N × K × log(K))
- 空间复杂度：O(N × K)
- 优点：不需要并查集
- 缺点：需要构建图，代码复杂

为什么 Union Find 更适合？
1. 自动处理传递性：A-B, B-C → A-C
2. 动态合并：可以随时添加新的连接
3. 查询高效：O(α(N)) ≈ O(1)
4. 代码清晰：逻辑分为两个阶段

为什么以邮箱为节点，而不是账户？
- 以账户为节点：需要 O(N²) 比较所有账户对
- 以邮箱为节点：只需 O(N × K) 遍历所有邮箱
- 邮箱是连接的桥梁，以邮箱为节点更自然

Union Find 的两个阶段：
阶段 1：Union（合并）
- 遍历所有账户
- 将同一账户的邮箱合并

阶段 2：Collect（收集）
- 遍历所有邮箱
- 按根节点分组
- 排序并添加账户名
*/

/*
传递性合并示例
-------------
输入：
accounts = [["John","a@mail.com","b@mail.com"],
            ["John","b@mail.com","c@mail.com"],
            ["John","c@mail.com","d@mail.com"]]

Union 过程：
账户 1：unite(a, b)
    a
   / \
  a   b

账户 2：unite(b, c)
- find(b) = a（路径压缩后）
- unite(a, c)
      a
    / | \
   a  b  c

账户 3：unite(c, d)
- find(c) = a（路径压缩后）
- unite(a, d)
        a
      / | \ \
     a  b  c d

结果：所有邮箱在同一集合
输出：[["John","a@mail.com","b@mail.com","c@mail.com","d@mail.com"]]

关键：Union Find 自动处理传递性，不需要手动判断
*/

/*
为什么要对邮箱排序？
------------------
题目要求：邮箱按字符顺序排列

例如：
错误输出：["John","johnsmith@mail.com","john00@mail.com"]
正确输出：["John","john00@mail.com","johnsmith@mail.com"]

排序保证输出格式符合要求
*/

int main() {
    Solution solution;

    // 测试用例 1：标准情况（传递性合并）
    cout << "测试用例 1：标准情况" << endl;
    vector<vector<string>> accounts1 = {
        {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
        {"John", "johnsmith@mail.com", "john00@mail.com"},
        {"Mary", "mary@mail.com"},
        {"John", "johnnybravo@mail.com"}
    };
    vector<vector<string>> result1 = solution.accountsMerge(accounts1);

    cout << "输出:" << endl;
    for (const auto& account : result1) {
        cout << "[";
        for (int i = 0; i < account.size(); i++) {
            cout << "\"" << account[i] << "\"";
            if (i < account.size() - 1) cout << ",";
        }
        cout << "]" << endl;
    }
    cout << endl;

    // 测试用例 2：单个账户
    cout << "测试用例 2：单个账户" << endl;
    vector<vector<string>> accounts2 = {
        {"John", "john@mail.com"}
    };
    vector<vector<string>> result2 = solution.accountsMerge(accounts2);

    cout << "输出:" << endl;
    for (const auto& account : result2) {
        cout << "[";
        for (int i = 0; i < account.size(); i++) {
            cout << "\"" << account[i] << "\"";
            if (i < account.size() - 1) cout << ",";
        }
        cout << "]" << endl;
    }
    cout << endl;

    // 测试用例 3：所有账户独立
    cout << "测试用例 3：所有账户独立" << endl;
    vector<vector<string>> accounts3 = {
        {"John", "john1@mail.com"},
        {"John", "john2@mail.com"},
        {"John", "john3@mail.com"}
    };
    vector<vector<string>> result3 = solution.accountsMerge(accounts3);

    cout << "输出:" << endl;
    for (const auto& account : result3) {
        cout << "[";
        for (int i = 0; i < account.size(); i++) {
            cout << "\"" << account[i] << "\"";
            if (i < account.size() - 1) cout << ",";
        }
        cout << "]" << endl;
    }
    cout << endl;

    // 测试用例 4：所有账户属于同一人
    cout << "测试用例 4：所有账户属于同一人（传递性）" << endl;
    vector<vector<string>> accounts4 = {
        {"John", "a@mail.com", "b@mail.com"},
        {"John", "b@mail.com", "c@mail.com"},
        {"John", "c@mail.com", "d@mail.com"}
    };
    vector<vector<string>> result4 = solution.accountsMerge(accounts4);

    cout << "输出:" << endl;
    for (const auto& account : result4) {
        cout << "[";
        for (int i = 0; i < account.size(); i++) {
            cout << "\"" << account[i] << "\"";
            if (i < account.size() - 1) cout << ",";
        }
        cout << "]" << endl;
    }
    cout << "解释: 通过传递性，a-b-c-d 都连通" << endl;
    cout << endl;

    // 测试用例 5：相同名字不同人
    cout << "测试用例 5：相同名字不同人" << endl;
    vector<vector<string>> accounts5 = {
        {"John", "john1@mail.com"},
        {"John", "john2@mail.com"},
        {"Mary", "mary@mail.com"}
    };
    vector<vector<string>> result5 = solution.accountsMerge(accounts5);

    cout << "输出:" << endl;
    for (const auto& account : result5) {
        cout << "[";
        for (int i = 0; i < account.size(); i++) {
            cout << "\"" << account[i] << "\"";
            if (i < account.size() - 1) cout << ",";
        }
        cout << "]" << endl;
    }
    cout << "解释: 两个 John 没有共同邮箱，是不同的人" << endl;
    cout << endl;

    // 测试用例 6：复杂传递性
    cout << "测试用例 6：复杂传递性" << endl;
    vector<vector<string>> accounts6 = {
        {"David", "david0@mail.com", "david1@mail.com"},
        {"David", "david3@mail.com", "david4@mail.com"},
        {"David", "david4@mail.com", "david5@mail.com"},
        {"David", "david2@mail.com", "david3@mail.com"},
        {"David", "david1@mail.com", "david2@mail.com"}
    };
    vector<vector<string>> result6 = solution.accountsMerge(accounts6);

    cout << "输出:" << endl;
    for (const auto& account : result6) {
        cout << "[";
        for (int i = 0; i < account.size(); i++) {
            cout << "\"" << account[i] << "\"";
            if (i < account.size() - 1) cout << ",";
        }
        cout << "]" << endl;
    }
    cout << "解释: 通过多次传递，所有邮箱最终连通" << endl;
    cout << "连接链: 0-1, 1-2, 2-3, 3-4, 4-5" << endl;

    return 0;
}

