
/*
算法名称：滑动窗口 Sliding Window

算法核心思想
-----------
用左右指针维护一个区间，右指针扩展窗口，
左指针在满足条件时收缩，从而在线性时间内找到最优答案。

思路要点
-------
- 窗口维护的是“可行解/统计状态”
- 右扩左缩保证每个元素最多进出一次 -> O(n)
- 常见目标：最短/最长满足条件区间
- 复杂条件常用哈希表/数组维护频次

什么时候使用
-----------
适用场景：
- 连续子数组/子串问题
- 最长/最短满足条件区间
- 固定窗口统计

常见算法变体
-----------
1) 固定窗口（大小固定）
2) 可变窗口（满足条件时收缩）
3) 计数型窗口（哈希表/数组维护频次）
4) 单调队列窗口（维护最大/最小）

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(字符集/状态规模)

ASCII 示例
---------
s = "abcabcbb"
窗口扩展到 "abc"，长度 3 为当前最优

典型题目扩展
-----------
- 3 Longest Substring Without Repeating Characters
- 76 Minimum Window Substring
- 209 Minimum Size Subarray Sum
- 239 Sliding Window Maximum
- 438 Find All Anagrams in a String

可直接使用的代码模板
------------------
见下方 SlidingWindow_Template

常见错误
--------
- 收缩时未正确更新统计
- 条件判断方向错误（>= / <=）
- 忘记处理空串与边界
*/

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <unordered_map>

using namespace std;

class SlidingWindow_Template {
public:
    // 示例 1：最长无重复子串长度
    int longestWithoutRepeat(const string& s) {
        vector<int> last(256, -1);
        int left = 0, best = 0;
        for (int right = 0; right < static_cast<int>(s.size()); ++right) {
            unsigned char c = static_cast<unsigned char>(s[right]);
            if (last[c] >= left) left = last[c] + 1;
            last[c] = right;
            best = max(best, right - left + 1);
        }
        return best;
    }

    // 示例 2：固定窗口最大和
    int maxSumFixedWindow(const vector<int>& nums, int k) {
        if (k <= 0 || nums.empty()) return 0;
        int n = static_cast<int>(nums.size());
        int sum = 0;
        for (int i = 0; i < k && i < n; ++i) sum += nums[i];
        int best = sum;
        for (int i = k; i < n; ++i) {
            sum += nums[i] - nums[i - k];
            best = max(best, sum);
        }
        return best;
    }

    // 示例 3：最短子数组长度（和 >= target）
    int minSubArrayLen(int target, const vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        int left = 0, sum = 0, ans = n + 1;
        for (int right = 0; right < n; ++right) {
            sum += nums[right];
            while (sum >= target) {
                ans = min(ans, right - left + 1);
                sum -= nums[left++];
            }
        }
        return ans == n + 1 ? 0 : ans;
    }

    // 示例 4：最小覆盖子串（need/window 模板）
    string minWindow(string s, string t) {
        if (t.empty() || s.size() < t.size()) return "";
        vector<int> need(256, 0), window(256, 0);
        int required = 0;
        for (char c : t) {
            if (need[(unsigned char)c] == 0) required++;
            need[(unsigned char)c]++;
        }

        int left = 0, formed = 0;
        int bestLen = (int)s.size() + 1;
        int bestL = 0;

        for (int right = 0; right < (int)s.size(); ++right) {
            unsigned char c = (unsigned char)s[right];
            window[c]++;
            if (need[c] > 0 && window[c] == need[c]) formed++;

            while (left <= right && formed == required) {
                if (right - left + 1 < bestLen) {
                    bestLen = right - left + 1;
                    bestL = left;
                }
                unsigned char d = (unsigned char)s[left];
                window[d]--;
                if (need[d] > 0 && window[d] < need[d]) formed--;
                left++;
            }
        }

        return bestLen > (int)s.size() ? "" : s.substr(bestL, bestLen);
    }

    // 示例 5：滑动窗口最大值（单调队列）
    vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
        deque<int> dq; // 存索引，保持递减
        vector<int> res;
        for (int i = 0; i < (int)nums.size(); ++i) {
            if (!dq.empty() && dq.front() <= i - k) dq.pop_front();
            while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();
            dq.push_back(i);
            if (i >= k - 1) res.push_back(nums[dq.front()]);
        }
        return res;
    }
};

int main() {
    SlidingWindow_Template solver;
    cout << "最长无重复子串长度: " << solver.longestWithoutRepeat("abcabcbb") << endl;
    vector<int> nums = {1, 3, -1, 5, 9};
    cout << "固定窗口最大和(k=3): " << solver.maxSumFixedWindow(nums, 3) << endl;
    cout << "最短子数组长度(target=8): " << solver.minSubArrayLen(8, nums) << endl;
    return 0;
}
