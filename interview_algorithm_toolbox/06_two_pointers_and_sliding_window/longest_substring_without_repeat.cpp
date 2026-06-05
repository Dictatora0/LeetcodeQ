/*
题目 / 示例名称：无重复字符的最长子串
核心知识点：滑动窗口、最近出现位置、字符串窗口
适用场景：题目出现“连续子串”“不能重复”这两个信号
关键思路：记录每个字符上次出现的位置，左端点不能回退，只能向右推进
时间复杂度：O(n)
空间复杂度：O(字符集大小)
常见错误：
1. 左端点被错误回退，窗口失去单调性。
2. 用 `set` 暴力删字符，写法更绕。
3. 忘记字符可能重复多次，需要取 `max(left, last_pos + 1)`。
示例输入：
abcabcbb
示例输出：
3
手动推演：
最长无重复子串可以是 abc，长度为 3。
对比说明：
- 记录最近位置通常比窗口里逐个删除字符更稳。
- 如果字符集只有小写字母，也可以用数组代替哈希表。
*/

#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) {
        return 0;
    }

    unordered_map<char, int> last_position;
    int left = 0;
    int best_length = 0;

    for (int right = 0; right < static_cast<int>(s.size()); ++right) {
        if (last_position.count(s[right])) {
            // left 只能右移不能左移，所以要取 max 防止窗口回退。
            left = max(left, last_position[s[right]] + 1);
        }

        // 更新当前字符的最近出现位置。
        last_position[s[right]] = right;
        // 当前窗口 [left, right] 内没有重复字符。
        best_length = max(best_length, right - left + 1);
    }

    cout << best_length << '\n';
    return 0;
}
