/*
 * ============================================================================
 * 滑动窗口算法 - 面试必备完整模板
 * Sliding Window Algorithm - Complete Interview Template
 * ============================================================================
 *
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

/*
 * ============================================================================
 * 第一部分：算法概述
 * ============================================================================
 */

/*
 * 【核心思想】
 * 滑动窗口是一种优化暴力枚举的技巧，通过维护一个"窗口"在数组/字符串上滑动，
 * 避免重复计算，将 O(n²) 或 O(n³) 的时间复杂度优化到 O(n)。
 *
 * 【通俗解释】
 * 想象你站在一扇窗户前看风景：
 * - 窗口有左边界和右边界
 * - 你可以向右移动窗口（扩大范围）
 * - 也可以收缩左边界（缩小范围）
 * - 每次移动都记录窗口内的信息
 *
 * 【为什么有效】
 * 1. 避免重复计算：窗口滑动时，只需要处理新进入和离开的元素
 * 2. 单向遍历：通常只需要一次遍历，left 和 right 指针都只向右移动
 * 3. 空间换时间：用哈希表等数据结构记录窗口状态
 *
 * 【与其他算法对比】
 * - vs 双指针：滑动窗口是双指针的特殊形式，窗口大小可变
 * - vs 动态规划：滑动窗口更简单，不需要状态转移方程
 * - vs 前缀和：滑动窗口可以处理更复杂的条件（如去重、最值）
 */

/*
 * ============================================================================
 * 第二部分：识别题型
 * ============================================================================
 */

/*
 * 【如何快速识别滑动窗口题目】
 *
 * ✅ 关键词识别：
 * 1. "连续子数组/子字符串" - 90% 是滑动窗口
 * 2. "最长/最短" + "满足某条件" - 典型滑动窗口
 * 3. "包含所有..." - 固定窗口或可变窗口
 * 4. "不重复" - 通常用哈希表 + 滑动窗口
 * 5. "至多/至少 K 个..." - 可变窗口
 *
 * ✅ 题目特征：
 * - 输入是数组或字符串
 * - 要求连续元素
 * - 需要优化暴力解法
 * - 有明确的窗口收缩条件
 *
 * ❌ 不适合滑动窗口：
 * - 需要排序的问题
 * - 子序列问题（不要求连续）
 * - 需要回溯的问题
 * - 二维数组问题（通常用 DFS/BFS）
 *
 * 【常见题目描述模式】
 * 1. "找出最长的连续子数组，使得..."
 * 2. "找出最短的连续子串，包含..."
 * 3. "找出所有长度为 K 的子数组..."
 * 4. "计算有多少个子数组满足..."
 */

/*
 * ============================================================================
 * 第三部分：核心模板
 * ============================================================================
 */

// ============================================================================
// 模板 1：固定窗口大小（最简单）
// 适用场景：窗口大小固定为 K
// 时间复杂度：O(n)
// 空间复杂度：O(1) 或 O(K)
// ============================================================================

class FixedWindowTemplate {
public:
    // 通用固定窗口模板
    vector<int> fixedWindow(vector<int>& nums, int k) {
        vector<int> result;
        if (nums.empty() || k <= 0 || k > nums.size()) return result;

        // 1. 初始化窗口状态（根据题目需求调整）
        int windowSum = 0;  // 示例：维护窗口和

        // 2. 构建第一个窗口
        for (int i = 0; i < k; i++) {
            windowSum += nums[i];
        }
        result.push_back(windowSum);  // 记录第一个窗口的结果

        // 3. 滑动窗口：移除左边，加入右边
        for (int right = k; right < nums.size(); right++) {
            int left = right - k;  // 左边界
            windowSum -= nums[left];      // 移除左边元素
            windowSum += nums[right];     // 加入右边元素
            result.push_back(windowSum);  // 记录当前窗口结果
        }

        return result;
    }
};

// ============================================================================
// 模板 2：可变窗口 - 求最大长度（最常用）
// 适用场景：找最长的满足某条件的子数组/子串
// 时间复杂度：O(n)
// 空间复杂度：O(k) k 为字符集大小
// ============================================================================

class MaxLengthWindowTemplate {
public:
    int maxLengthWindow(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        int left = 0;           // 左指针
        int maxLen = 0;         // 记录最大长度
        unordered_map<int, int> window;  // 窗口状态（根据题目调整）

        // 右指针遍历整个数组
        for (int right = 0; right < n; right++) {
            // 1. 扩大窗口：将 nums[right] 加入窗口
            window[nums[right]]++;

            // 2. 收缩窗口：当窗口不满足条件时
            while (left <= right && !isValid(window)) {
                // 移除 nums[left]
                window[nums[left]]--;
                if (window[nums[left]] == 0) {
                    window.erase(nums[left]);
                }
                left++;  // 左指针右移
            }

            // 3. 更新结果：当前窗口满足条件
            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }

private:
    // 判断窗口是否满足条件（根据具体题目实现）
    bool isValid(unordered_map<int, int>& window) {
        // 示例：窗口内元素不重复
        return true;  // 需要根据题目修改
    }
};

// ============================================================================
// 模板 3：可变窗口 - 求最小长度
// 适用场景：找最短的满足某条件的子数组/子串
// 时间复杂度：O(n)
// 空间复杂度：O(k)
// ============================================================================

class MinLengthWindowTemplate {
public:
    int minLengthWindow(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 0) return 0;

        int left = 0;
        int minLen = INT_MAX;   // 初始化为最大值
        int windowSum = 0;      // 窗口状态（根据题目调整）

        for (int right = 0; right < n; right++) {
            // 1. 扩大窗口
            windowSum += nums[right];

            // 2. 收缩窗口：当窗口满足条件时，尝试缩小
            while (left <= right && windowSum >= target) {
                // 更新最小长度
                minLen = min(minLen, right - left + 1);

                // 移除左边元素，尝试找更小的窗口
                windowSum -= nums[left];
                left++;
            }
        }

        return minLen == INT_MAX ? 0 : minLen;
    }
};

// ============================================================================
// 模板 4：字符串匹配窗口（高频面试题）
// 适用场景：找包含所有目标字符的最小子串
// 时间复杂度：O(n + m)
// 空间复杂度：O(k) k 为字符集大小
// ============================================================================

class StringMatchWindowTemplate {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty()) return "";

        // 1. 统计目标字符串 t 中每个字符的频率
        unordered_map<char, int> need;
        for (char c : t) {
            need[c]++;
        }

        // 2. 初始化窗口状态
        unordered_map<char, int> window;
        int left = 0, right = 0;
        int valid = 0;  // 窗口中满足条件的字符种类数
        int start = 0, minLen = INT_MAX;  // 记录最小覆盖子串的起始位置和长度

        // 3. 移动右指针扩大窗口
        while (right < s.size()) {
            char c = s[right];
            right++;

            // 更新窗口数据
            if (need.count(c)) {
                window[c]++;
                if (window[c] == need[c]) {
                    valid++;  // 该字符的频率满足要求
                }
            }

            // 4. 判断是否需要收缩窗口
            while (valid == need.size()) {
                // 更新最小覆盖子串
                if (right - left < minLen) {
                    start = left;
                    minLen = right - left;
                }

                // 移除左边字符
                char d = s[left];
                left++;

                // 更新窗口数据
                if (need.count(d)) {
                    if (window[d] == need[d]) {
                        valid--;  // 该字符不再满足要求
                    }
                    window[d]--;
                }
            }
        }

        return minLen == INT_MAX ? "" : s.substr(start, minLen);
    }
};

/*
 * ============================================================================
 * 第四部分：常见变体
 * ============================================================================
 */

// ============================================================================
// 变体 1：无重复字符的最长子串
// LeetCode 3: Longest Substring Without Repeating Characters
// ============================================================================

class Solution_LongestSubstringWithoutRepeating {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        if (n == 0) return 0;

        unordered_set<char> window;  // 用 set 检测重复
        int left = 0, maxLen = 0;

        for (int right = 0; right < n; right++) {
            // 如果有重复，收缩左边界直到无重复
            while (window.count(s[right])) {
                window.erase(s[left]);
                left++;
            }

            // 加入当前字符
            window.insert(s[right]);
            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }

    // 优化版本：用哈希表记录字符位置，可以直接跳转
    int lengthOfLongestSubstring_Optimized(string s) {
        unordered_map<char, int> lastPos;  // 字符 -> 最后出现位置
        int left = 0, maxLen = 0;

        for (int right = 0; right < s.size(); right++) {
            char c = s[right];

            // 如果字符重复，直接跳转 left 到重复位置的下一个
            if (lastPos.count(c) && lastPos[c] >= left) {
                left = lastPos[c] + 1;
            }

            lastPos[c] = right;
            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};

// ============================================================================
// 变体 2：长度最小的子数组（和 >= target）
// LeetCode 209: Minimum Size Subarray Sum
// ============================================================================

class Solution_MinSubArrayLen {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        int left = 0, sum = 0, minLen = INT_MAX;

        for (int right = 0; right < n; right++) {
            sum += nums[right];

            // 当和 >= target 时，尝试收缩窗口
            while (sum >= target) {
                minLen = min(minLen, right - left + 1);
                sum -= nums[left];
                left++;
            }
        }

        return minLen == INT_MAX ? 0 : minLen;
    }
};

// ============================================================================
// 变体 3：找到字符串中所有字母异位词
// LeetCode 438: Find All Anagrams in a String
// ============================================================================

class Solution_FindAnagrams {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> result;
        if (s.size() < p.size()) return result;

        // 统计 p 中字符频率
        unordered_map<char, int> need, window;
        for (char c : p) need[c]++;

        int left = 0, right = 0, valid = 0;

        while (right < s.size()) {
            char c = s[right];
            right++;

            // 更新窗口
            if (need.count(c)) {
                window[c]++;
                if (window[c] == need[c]) valid++;
            }

            // 窗口大小达到 p 的长度
            while (right - left >= p.size()) {
                // 检查是否找到异位词
                if (valid == need.size()) {
                    result.push_back(left);
                }

                // 收缩窗口
                char d = s[left];
                left++;
                if (need.count(d)) {
                    if (window[d] == need[d]) valid--;
                    window[d]--;
                }
            }
        }

        return result;
    }
};

// ============================================================================
// 变体 4：至多包含 K 个不同字符的最长子串
// LeetCode 340: Longest Substring with At Most K Distinct Characters
// ============================================================================

class Solution_LongestSubstringKDistinct {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        if (k == 0 || s.empty()) return 0;

        unordered_map<char, int> window;
        int left = 0, maxLen = 0;

        for (int right = 0; right < s.size(); right++) {
            window[s[right]]++;

            // 当不同字符数 > k 时，收缩窗口
            while (window.size() > k) {
                window[s[left]]--;
                if (window[s[left]] == 0) {
                    window.erase(s[left]);
                }
                left++;
            }

            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};

// ============================================================================
// 变体 5：水果成篮（至多两种类型）
// LeetCode 904: Fruit Into Baskets
// ============================================================================

class Solution_TotalFruit {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> basket;  // 水果类型 -> 数量
        int left = 0, maxFruits = 0;

        for (int right = 0; right < fruits.size(); right++) {
            basket[fruits[right]]++;

            // 超过 2 种水果，收缩窗口
            while (basket.size() > 2) {
                basket[fruits[left]]--;
                if (basket[fruits[left]] == 0) {
                    basket.erase(fruits[left]);
                }
                left++;
            }

            maxFruits = max(maxFruits, right - left + 1);
        }

        return maxFruits;
    }
};

// ============================================================================
// 变体 6：替换后的最长重复字符
// LeetCode 424: Longest Repeating Character Replacement
// ============================================================================

class Solution_CharacterReplacement {
public:
    int characterReplacement(string s, int k) {
        vector<int> count(26, 0);  // 统计每个字符出现次数
        int left = 0, maxCount = 0, maxLen = 0;

        for (int right = 0; right < s.size(); right++) {
            // 更新当前字符计数
            count[s[right] - 'A']++;
            maxCount = max(maxCount, count[s[right] - 'A']);

            // 窗口大小 - 最多字符数 > k，说明需要替换的字符太多
            while (right - left + 1 - maxCount > k) {
                count[s[left] - 'A']--;
                left++;
            }

            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};

// ============================================================================
// 变体 7：最大连续 1 的个数 III（最多翻转 K 个 0）
// LeetCode 1004: Max Consecutive Ones III
// ============================================================================

class Solution_LongestOnes {
public:
    int longestOnes(vector<int>& nums, int k) {
        int left = 0, zeros = 0, maxLen = 0;

        for (int right = 0; right < nums.size(); right++) {
            if (nums[right] == 0) zeros++;

            // 0 的个数超过 k，收缩窗口
            while (zeros > k) {
                if (nums[left] == 0) zeros--;
                left++;
            }

            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};

/*
 * ============================================================================
 * 第五部分：面试技巧
 * ============================================================================
 */

/*
 * 【如何向面试官解释思路】
 *
 * 1. 先说暴力解法（展示你的思考过程）
 *    "最直接的方法是枚举所有子数组，时间复杂度 O(n²)..."
 *
 * 2. 指出优化点
 *    "但我们发现，当窗口右移时，大部分元素都是重复计算的..."
 *
 * 3. 引入滑动窗口
 *    "我们可以用滑动窗口优化，维护一个窗口在数组上滑动，
 *     只处理新进入和离开的元素，时间复杂度降到 O(n)"
 *
 * 4. 说明窗口收缩条件（关键！）
 *    "当窗口不满足条件时（比如出现重复字符），我们收缩左边界..."
 *
 * 5. 边写边说
 *    - "我用 left 和 right 两个指针表示窗口边界"
 *    - "用哈希表记录窗口内的元素状态"
 *    - "right 指针负责扩大窗口，left 指针负责收缩窗口"
 *
 * 【时间复杂度分析技巧】
 *
 * 面试官常问："为什么是 O(n) 而不是 O(n²)？"
 *
 * 标准回答：
 * "虽然有两层循环，但 left 和 right 指针都只会向右移动，
 *  每个元素最多被访问两次（一次被 right 加入，一次被 left 移除），
 *  所以总的时间复杂度是 O(n)"
 */
