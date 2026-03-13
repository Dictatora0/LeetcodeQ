
/*
快速输入输出模板

适用：需要大输入量的题目
*/

#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    if (cin >> a >> b) {
        cout << (a + b) << "\n";
    }
    return 0;
}
