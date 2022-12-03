#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    long long r = 0;
    string s;
    while (cin >> s) {
        set<char> c;
        for (int i = 0; i < s.size()/2; i++) {
            c.insert(s[i]);
        }
        for (int i = s.size()/2; i < s.size(); i++) {
            if (c.count(s[i])) {
                if (s[i] >= 'a') {
                    r += s[i] - 'a' + 1;
                } else {
                    r += s[i] - 'A' + 27;
                }
                break;
            }
        }
        cout << r << '\n';
    }
}
