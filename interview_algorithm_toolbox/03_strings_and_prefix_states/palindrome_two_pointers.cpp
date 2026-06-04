/*
题目 / 示例名称：双指针判断回文串
核心知识点：双指针、首尾逼近
适用场景：判断字符串是否左右对称
关键思路：左右指针同时向中间移动，只要发现一对字符不同就立即返回 false
时间复杂度：O(n)
空间复杂度：O(1)
常见错误：
1. 把 `left < right` 写成 `left <= right` 后又多做无效比较。
2. 漏掉了单字符和空串的情况。
3. 明明只需判断真伪，却额外开新字符串翻转，浪费空间。
示例输入：
level
示例输出：
YES
手动推演：
比较 l-l、e-e，最终中间剩下 v，不影响回文性。
对比说明：
- 双指针是最直接的写法。
- 反转后比较也能做，但空间开销更大。
*/

#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) {
        return 0;
    }

    int left = 0;
    int right = static_cast<int>(s.size()) - 1;

    while (left < right) {
        if (s[left] != s[right]) {
            cout << "NO\n";
            return 0;
        }
        ++left;
        --right;
    }

    cout << "YES\n";
    return 0;
}
