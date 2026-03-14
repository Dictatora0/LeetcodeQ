/*
 * ============================================================================
 * 并查集算法 - 面试必备完整模板
 * Union Find (Disjoint Set Union) - Complete Interview Template
 * ============================================================================
 *
 */

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
 * ============================================================================
 * 第一部分：算法概述
 * ============================================================================
 */

/*
 * 【核心思想】
 * 并查集是一种树形数据结构，用于处理不相交集合的合并和查询问题。
 *
 * 【通俗解释】
 * 想象你在管理朋友圈：
 * - 每个人最初是独立的
 * - 两个人成为朋友，合并他们的朋友圈
 * - 查询两个人是否在同一个朋友圈
 *
 * 【两个核心操作】
 * 1. Find：查找元素所属的集合（找根节点）
 * 2. Union：合并两个集合
 *
 * 【两个优化】
 * 1. 路径压缩：Find 时将路径上的节点直接连到根
 * 2. 按秩合并：Union 时将小树连到大树
 *
 * 【与其他算法对比】
 * - vs DFS/BFS：并查集更高效，近乎 O(1)
 * - vs 图算法：并查集专门处理连通性
 */

/*
 * ============================================================================
 * 第二部分：识别题型
 * ============================================================================
 */

/*
 * 【如何快速识别并查集题目】
 *
 * ✅ 关键词识别：
 * 1. "连通性" - 90% 是并查集
 * 2. "朋友圈" - 并查集
 * 3. "省份数量" - 并查集
 * 4. "岛屿数量"（动态） - 并查集
 * 5. "冗余连接" - 并查集
 *
 * ✅ 题目特征：
 * - 判断连通性
 * - 动态合并集合
 * - 查询集合数量
 * - 检测环
 *
 * ❌ 不适合并查集：
 * - 需要路径信息（用 BFS）
 * - 需要删除边
 * - 有向图问题
 */

/*
 * ============================================================================
 * 第三部分：核心模板
 * ============================================================================
 */

// ============================================================================
// 模板 1：基础并查集
// Find：O(α(n)) 近乎 O(1)
// Union：O(α(n)) 近乎 O(1)
// 空间：O(n)
// ============================================================================

class UnionFind {
private:
    vector<int> parent;  // parent[i] 表示 i 的父节点
    vector<int> rank;    // rank[i] 表示以 i 为根的树的高度
    int count;           // 连通分量数量

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        count = n;

        // 初始化：每个元素的父节点是自己
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // 查找根节点（带路径压缩）
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // 路径压缩
        }
        return parent[x];
    }

    // 合并两个集合（按秩合并）
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return;

        // 按秩合并：将小树连到大树
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }

        count--;
    }

    // 判断是否连通
    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    // 获取连通分量数量
    int getCount() {
        return count;
    }
};

// ============================================================================
// 模板 2：带权并查集（记录到根节点的距离）
// 适用于：关系传递、食物链等问题
// ============================================================================

class WeightedUnionFind {
private:
    vector<int> parent;
    vector<int> weight;  // weight[i] 表示 i 到 parent[i] 的权值

public:
    WeightedUnionFind(int n) {
        parent.resize(n);
        weight.resize(n, 0);

        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            int root = find(parent[x]);
            weight[x] += weight[parent[x]];  // 更新权值
            parent[x] = root;
        }
        return parent[x];
    }

    void unite(int x, int y, int w) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return;

        parent[rootX] = rootY;
        weight[rootX] = weight[y] - weight[x] + w;
    }

    int getWeight(int x, int y) {
        if (find(x) != find(y)) return -1;
        return weight[x] - weight[y];
    }
};

/*
 * ============================================================================
 * 第四部分：常见变体
 * ============================================================================
 */

// ============================================================================
// 变体 1：省份数量
// LeetCode 547: Number of Provinces
// ============================================================================

class Solution_FindCircleNum {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        UnionFind uf(n);

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (isConnected[i][j] == 1) {
                    uf.unite(i, j);
                }
            }
        }

        return uf.getCount();
    }
};

// ============================================================================
// 变体 2：冗余连接
// LeetCode 684: Redundant Connection
// ============================================================================

class Solution_FindRedundantConnection {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        UnionFind uf(n + 1);

        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];

            if (uf.connected(u, v)) {
                return edge;  // 找到冗余边
            }

            uf.unite(u, v);
        }

        return {};
    }
};

// ============================================================================
// 变体 3：账户合并
// LeetCode 721: Accounts Merge
// ============================================================================

class Solution_AccountsMerge {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, int> emailToId;
        unordered_map<string, string> emailToName;
        int id = 0;

        // 给每个邮箱分配 ID
        for (auto& account : accounts) {
            string name = account[0];
            for (int i = 1; i < account.size(); i++) {
                string email = account[i];
                if (!emailToId.count(email)) {
                    emailToId[email] = id++;
                    emailToName[email] = name;
                }
            }
        }

        UnionFind uf(id);

        // 合并同一账户的邮箱
        for (auto& account : accounts) {
            int firstId = emailToId[account[1]];
            for (int i = 2; i < account.size(); i++) {
                uf.unite(firstId, emailToId[account[i]]);
            }
        }

        // 收集结果
        unordered_map<int, vector<string>> groups;
        for (auto& [email, id] : emailToId) {
            groups[uf.find(id)].push_back(email);
        }

        vector<vector<string>> result;
        for (auto& [id, emails] : groups) {
            sort(emails.begin(), emails.end());
            vector<string> account = {emailToName[emails[0]]};
            account.insert(account.end(), emails.begin(), emails.end());
            result.push_back(account);
        }

        return result;
    }
};

// ============================================================================
// 变体 4：等式方程的可满足性
// LeetCode 990: Satisfiability of Equality Equations
// ============================================================================

class Solution_EquationsPossible {
public:
    bool equationsPossible(vector<string>& equations) {
        UnionFind uf(26);

        // 先处理相等关系
        for (auto& eq : equations) {
            if (eq[1] == '=') {
                int x = eq[0] - 'a';
                int y = eq[3] - 'a';
                uf.unite(x, y);
            }
        }

        // 再检查不等关系
        for (auto& eq : equations) {
            if (eq[1] == '!') {
                int x = eq[0] - 'a';
                int y = eq[3] - 'a';
                if (uf.connected(x, y)) {
                    return false;
                }
            }
        }

        return true;
    }
};

// ============================================================================
// 变体 5：最长连续序列
// LeetCode 128: Longest Consecutive Sequence
// ============================================================================

class Solution_LongestConsecutive {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;

        unordered_map<int, int> parent;
        unordered_map<int, int> size;

        // 初始化
        for (int num : nums) {
            if (parent.count(num)) continue;
            parent[num] = num;
            size[num] = 1;

            // 与相邻数字合并
            if (parent.count(num - 1)) {
                unite(parent, size, num, num - 1);
            }
            if (parent.count(num + 1)) {
                unite(parent, size, num, num + 1);
            }
        }

        int maxLen = 0;
        for (auto& [num, s] : size) {
            maxLen = max(maxLen, s);
        }

        return maxLen;
    }

private:
    int find(unordered_map<int, int>& parent, int x) {
        if (parent[x] != x) {
            parent[x] = find(parent, parent[x]);
        }
        return parent[x];
    }

    void unite(unordered_map<int, int>& parent, unordered_map<int, int>& size,
               int x, int y) {
        int rootX = find(parent, x);
        int rootY = find(parent, y);

        if (rootX == rootY) return;

        parent[rootX] = rootY;
        size[rootY] += size[rootX];
    }
};

/*
 * ============================================================================
 * 第五至十部分：面试技巧、易错点、复杂度、真题、示例、速查表
 * ============================================================================
 */

/*
 * 【面试技巧】
 * 1. 说明两个优化：路径压缩 + 按秩合并
 * 2. 强调近乎 O(1) 的时间复杂度
 * 3. 画图解释合并过程
 *
 * 【易错点】
 * ❌ 忘记路径压缩
 * ❌ Union 时没有判断是否已连通
 * ❌ 初始化时 parent[i] = i
 * ❌ Find 时没有返回根节点
 *
 * 【复杂度】
 * Find：O(α(n)) 近乎 O(1)
 * Union：O(α(n)) 近乎 O(1)
 * 空间：O(n)
 *
 * 【高频题目】
 * ⭐⭐⭐⭐⭐ LC 547, LC 684, LC 200（动态）
 * ⭐⭐⭐⭐ LC 721, LC 990, LC 128
 *
 * 【速查表】
 * class UnionFind {
 *     vector<int> parent, rank;
 *     int count;
 *
 *     UnionFind(int n) {
 *         parent.resize(n);
 *         rank.resize(n, 1);
 *         count = n;
 *         for (int i = 0; i < n; i++) parent[i] = i;
 *     }
 *
 *     int find(int x) {
 *         if (parent[x] != x) {
 *             parent[x] = find(parent[x]);  // 路径压缩
 *         }
 *         return parent[x];
 *     }
 *
 *     void unite(int x, int y) {
 *         int rootX = find(x), rootY = find(y);
 *         if (rootX == rootY) return;
 *
 *         if (rank[rootX] < rank[rootY]) {
 *             parent[rootX] = rootY;
 *         } else if (rank[rootX] > rank[rootY]) {
 *             parent[rootY] = rootX;
 *         } else {
 *             parent[rootY] = rootX;
 *             rank[rootX]++;
 *         }
 *         count--;
 *     }
 *
 *     bool connected(int x, int y) {
 *         return find(x) == find(y);
 *     }
 * };
 */

int main() {
    UnionFind uf(5);

    uf.unite(0, 1);
    uf.unite(1, 2);
    uf.unite(3, 4);

    cout << "0 和 2 是否连通: " << (uf.connected(0, 2) ? "是" : "否") << endl;
    cout << "0 和 3 是否连通: " << (uf.connected(0, 3) ? "是" : "否") << endl;
    cout << "连通分量数量: " << uf.getCount() << endl;

    cout << "并查集算法模板测试完成" << endl;
    return 0;
}

/*
 * 编译运行：
 * g++ -std=c++11 -o union_find union_find_template.cpp && ./union_find
 */
