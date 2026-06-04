/*
题目 / 示例名称：最长连续相同字符段
核心知识点：字符串扫描、分组统计、连续段
适用场景：题目问“最长连续多少个相同字符”
关键思路：维护当前连续段长度和历史最大值，遇到不同字符就重新开始计数
时间复杂度：O(n)
空间复杂度：O(1)
常见错误：
1. 忘记在循环结束后更新最后一段答案。
2. 把“字符种类最多”误解成“连续最长”。
3. 空字符串没有单独考虑。
示例输入：
aaabbccccd
示例输出：
c 4
手动推演：
连续段依次是 a3、b2、c4、d1，最长的是 c4。
对比说明：
- 这种题不需要栈，也不需要哈希，线性扫描就够。
- 如果题目改成“出现次数最多”，那就不是连续段问题了。
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

    if (s.empty()) {
        cout << "EMPTY 0\n";
        return 0;
    }

    char best_char = s[0];
    int best_len = 1;
    char current_char = s[0];
    int current_len = 1;

    for (int i = 1; i < static_cast<int>(s.size()); ++i) {
        if (s[i] == current_char) {
            ++current_len;
        } else {
            current_char = s[i];
            current_len = 1;
        }

        if (current_len > best_len) {
            best_len = current_len;
            best_char = current_char;
        }
    }

    cout << best_char << ' ' << best_len << '\n';
    return 0;
}
