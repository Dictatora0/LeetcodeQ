
/*
算法名称：并查集 Union Find

算法核心思想
-----------
用父节点数组表示集合，支持快速合并与查询同一集合。
路径压缩与按秩合并可将复杂度降为近似 O(1)。

思路要点
-------
- find：寻找根节点并路径压缩
- unite：合并两个集合（按秩/按大小）
- same：判断是否连通
- 维护 components 可快速得到连通分量数量

什么时候使用
-----------
适用场景：
- 连通性问题
- 动态连通图
- Kruskal 最小生成树
- 并集合并与查询

常见算法变体
-----------
1) 路径压缩
2) 按秩/按大小合并
3) 记录集合大小
4) 维护连通分量数量

复杂度分析
---------
时间复杂度：近似 O(1)（Ackermann 反函数）
空间复杂度：O(n)

ASCII 示例
---------
初始：1 2 3 4
合并(1,2) -> {1,2}
合并(3,4) -> {3,4}

典型题目扩展
-----------
- 547 Number of Provinces
- 684 Redundant Connection
- 721 Accounts Merge
- 1202 Smallest String With Swaps

可直接使用的代码模板
------------------
见下方 UnionFind

常见错误
--------
- 忘记路径压缩导致退化
- 合并时未按秩/大小
- 节点编号与数组索引错位
*/

#include <iostream>
#include <vector>

using namespace std;

class UnionFind {
public:
    explicit UnionFind(int n) : parent(n), rank(n, 0), size(n, 1), components(n) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return false;
        if (rank[ra] < rank[rb]) swap(ra, rb);
        parent[rb] = ra;
        size[ra] += size[rb];
        if (rank[ra] == rank[rb]) rank[ra]++;
        components--;
        return true;
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    int getSize(int x) {
        return size[find(x)];
    }

    int count() const {
        return components;
    }

private:
    vector<int> parent;
    vector<int> rank;
    vector<int> size;
    int components;
};

int main() {
    UnionFind uf(5);
    uf.unite(1, 2);
    uf.unite(3, 4);
    cout << boolalpha << uf.same(1, 2) << " " << uf.same(1, 3) << endl;
    cout << "size(1) = " << uf.getSize(1) << ", components = " << uf.count() << endl;
    return 0;
}
