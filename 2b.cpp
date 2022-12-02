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

        n += y*3;
        if (y == 0) {
            int xx = (x-1)%3;
            if (xx < 0) xx += 3;
            n += xx+1;
        } else if (y == 1) {
            n += x+1;
        } else {
            n += ((x+1)%3)+1;
        }
        // cout << n << '\n';
    }
    cout << n << endl;
    return 0;
}
