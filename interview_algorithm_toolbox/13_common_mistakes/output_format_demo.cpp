/*
题目 / 示例名称：输出格式防错示例
核心知识点：空格控制、换行、格式一致性
适用场景：题目要求输出一行数组、一行答案，或严格区分大小写的字符串
关键思路：
1. 打印一行数组时，用 `if (i > 0) cout << ' ';` 控制分隔空格。
2. 每组答案后统一输出换行。
3. 输出内容必须和题面大小写完全一致。
时间复杂度：O(n)
空间复杂度：O(1)
常见错误：
1. 行尾多出说明文字，例如把 `YES` 写成 `Yes`。
2. 多个数字之间少空格或多空格。
3. 忘记最后换行，调试时不明显，提交后很难看。
示例输入：
4
7 8 9 10
示例输出：
7 8 9 10
DONE
手动推演：
第一行输出数组，元素之间正好一个空格；第二行输出固定字符串 DONE。
对比说明：
- 很多 OJ 容忍行尾空格，但不建议依赖这种宽容。
- 统一用 `'\n'` 收尾，格式最稳。
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            // 只在元素之间输出空格，避免行首和行尾多空格。
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
    cout << "DONE\n";

    return 0;
}
