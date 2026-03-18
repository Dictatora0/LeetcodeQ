#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

/*
LeetCode 763. 划分字母区间
题型：贪心 / 区间合并
核心思路：先记录每个字符最后一次出现的位置，再扫描字符串并维护当前分段右边界，走到边界就能切一段。
复杂度：时间 O(n)，空间 O(1)
*/
class Solution {
public:
    vector<int> partitionLabels(string s) {
        vector<int> ans;
        int lastIndex[26] = {};
        for (int i = 0; i < static_cast<int>(s.size()); ++i) {
            lastIndex[s[i] - 'a'] = i;
        }
        int start = 0;
        int end = 0;
        for (int i = 0; i < static_cast<int>(s.size()); ++i) {
            end = max(lastIndex[s[i] - 'a'], end);
            if (i == end) {
                ans.push_back(end - start + 1);
                start = i + 1;
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
    Solution solution;
    vector<int> ans = solution.partitionLabels("ababcbacadefegdehijhklij");

    cout << "partitions: ";
    printVector(ans);

    return 0;
}
