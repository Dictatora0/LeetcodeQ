#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/*
LeetCode 347. 前 K 个高频元素
题型：哈希表 + 桶排序
核心思路：先统计频率，再把相同频率的元素放入桶中，从高频桶往低频桶收集前 k 个答案。
复杂度：时间 O(n)，空间 O(n)
*/
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> cnt;
        for (int num : nums) {
            cnt[num]++;
        }

        int n = static_cast<int>(nums.size());
        vector<vector<int>> bucket(n + 1);

        for (auto& [num, freq] : cnt) {
            bucket[freq].push_back(num);
        }

        vector<int> ans;
        for (int i = n; i >= 0 && ans.size() < static_cast<size_t>(k); --i) {
            for (int num : bucket[i]) {
                ans.push_back(num);
                if (ans.size() == static_cast<size_t>(k)) {
                    break;
                }
            }
        }
        return ans;
    }
};

static void printVector(const vector<int>& nums) {
    cout << "[";
    for (size_t i = 0; i < nums.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << nums[i];
    }
    cout << "]" << endl;
}

int main() {
    Solution s;
    vector<int> nums = {1, 1, 1, 2, 2, 3};
    vector<int> ans = s.topKFrequent(nums, 2);

    cout << "top 2 frequent of [1,1,1,2,2,3]: ";
    printVector(ans);

    return 0;
}
