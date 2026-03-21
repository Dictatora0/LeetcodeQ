#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int expand(string& s, int left, int right) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            left--;
            right++;
        }
        return right - left - 1;
    }

    string longestPalindrome(string s) {
        int n = s.size();
        if (n < 2) return s;

        int start = 0;
        int maxLen = 1;

        for (int i = 0; i < n; i++) {
            int len1 = expand(s, i, i);       // 奇数长度
            int len2 = expand(s, i, i + 1);   // 偶数长度
            int len = max(len1, len2);

            if (len > maxLen) {
                maxLen = len;
                start = i - (len - 1) / 2;
            }
        }

        return s.substr(start, maxLen);
    }
};

int main() {
    Solution solution;

    cout << INT16_MIN << endl;
    // TODO: 添加测试用例
    
    return 0;
}
