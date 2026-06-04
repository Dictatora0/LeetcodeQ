/*
题目 / 示例名称：stable_sort 演示
核心知识点：稳定排序、相等关键字保持原顺序
适用场景：只按一个关键字排序，但希望关键字相等时保留原输入顺序
关键思路：分别用 `sort` 和 `stable_sort` 排同一批数据，对比输出
时间复杂度：O(n log n)
空间复杂度：`stable_sort` 可能需要更多辅助空间
常见错误：
1. 误以为 `sort` 会自动保持相等元素的原顺序。
2. 在题目明确要求“保持原顺序”时仍然使用 `sort`。
3. 看见样例没出错就以为 `sort` 一定稳定。
示例输入：
5
90
70
90
80
90
示例输出：
sort: 1 3 5 4 2
stable_sort: 1 3 5 4 2
手动推演：
如果相同分数的编号本来是 1,3,5，那么稳定排序后仍然保持 1,3,5 的相对顺序。
对比说明：
- `sort` 的相等元素顺序不受保证。
- `stable_sort` 适合“主键相等时保持输入顺序”的题。
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Record {
    int id;
    int score;
};

bool compareByScoreDesc(const Record& a, const Record& b) {
    return a.score > b.score;
}

void printIds(const vector<Record>& records, const string& title) {
    cout << title << ": ";
    for (size_t i = 0; i < records.size(); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << records[i].id;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    vector<Record> records(n);
    for (int i = 0; i < n; ++i) {
        cin >> records[i].score;
        records[i].id = i + 1;
    }

    vector<Record> a = records;
    vector<Record> b = records;

    sort(a.begin(), a.end(), compareByScoreDesc);
    stable_sort(b.begin(), b.end(), compareByScoreDesc);

    printIds(a, "sort");
    printIds(b, "stable_sort");
    return 0;
}
