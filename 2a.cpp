#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n = 0;

    char a, b;
    while (std::cin >> a && std::cin >> b) {
        int x = a - 'A';
        int y = b - 'X';

        n += y+1;
        if (x == y) {
            n += 3;
        } else if ((x+1)%3 == y) {
            n += 6;
        }
        // cout << n << '\n';
    }
    cout << n << endl;
    return 0;
}
