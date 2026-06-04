#include <bitset>
#include <iostream>

using namespace std;

int main() {
    int x = 13912123;

    cout << bitset<8>(x) << '\n';

    return 0;
}
