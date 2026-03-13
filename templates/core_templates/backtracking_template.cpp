
/*
算法名称：回溯 Backtracking

算法核心思想
-----------
回溯是在搜索树中进行“选择 -> 递归 -> 撤销”的过程。
通过剪枝减少无效搜索，常用于排列、组合、子集问题。

思路要点
-------
- 先确定“路径”表示什么
- 递归函数负责扩展路径
- 回溯时恢复状态（path/used）
- 剪枝条件越早越好

什么时候使用
-----------
适用场景：
- 枚举所有可能解
- 排列/组合/子集
- 路径搜索、棋盘问题

常见算法变体
-----------
1) 全排列
2) 组合选择
3) 子集枚举
4) 带剪枝的 DFS
5) 去重排列（排序 + used 跳过）

复杂度分析
---------
时间复杂度：O(搜索空间大小)
空间复杂度：O(递归深度)

ASCII 示例
---------
nums = [1,2]
搜索树：
[]
├─ [1]
│  └─ [1,2]
└─ [2]
   └─ [2,1]

典型题目扩展
-----------
- 46 Permutations
- 47 Permutations II
- 39 Combination Sum
- 78 Subsets
- 79 Word Search

可直接使用的代码模板
------------------
见下方 Backtracking_Template

常见错误
--------
- 忘记撤销状态
- 剪枝条件不正确
- visited 标记遗漏
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Backtracking_Template {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> path;
        vector<int> used(nums.size(), 0);
        dfsPerm(nums, used, path, res);
        return res;
    }

    // 组合选择（从 1..n 选 k 个）
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> path;
        dfsCombine(1, n, k, path, res);
        return res;
    }

    // 去重全排列
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        vector<int> path;
        vector<int> used(nums.size(), 0);
        dfsPermUnique(nums, used, path, res);
        return res;
    }

private:
    void dfsPerm(const vector<int>& nums, vector<int>& used, vector<int>& path, vector<vector<int>>& res) {
        if (path.size() == nums.size()) {
            res.push_back(path);
            return;
        }
        for (int i = 0; i < (int)nums.size(); ++i) {
            if (used[i]) continue;
            used[i] = 1;
            path.push_back(nums[i]);
            dfsPerm(nums, used, path, res);
            path.pop_back();
            used[i] = 0;
        }
    }

    void dfsCombine(int start, int n, int k, vector<int>& path, vector<vector<int>>& res) {
        if ((int)path.size() == k) {
            res.push_back(path);
            return;
        }
        for (int i = start; i <= n; ++i) {
            path.push_back(i);
            dfsCombine(i + 1, n, k, path, res);
            path.pop_back();
        }
    }

    void dfsPermUnique(const vector<int>& nums, vector<int>& used, vector<int>& path, vector<vector<int>>& res) {
        if (path.size() == nums.size()) {
            res.push_back(path);
            return;
        }
        for (int i = 0; i < (int)nums.size(); ++i) {
            if (used[i]) continue;
            if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue; // 去重
            used[i] = 1;
            path.push_back(nums[i]);
            dfsPermUnique(nums, used, path, res);
            path.pop_back();
            used[i] = 0;
        }
    }
};

int main() {
    Backtracking_Template solver;
    vector<int> nums = {1, 2, 3};
    auto res = solver.permute(nums);
    cout << "全排列数量: " << res.size() << endl;
    return 0;
}
