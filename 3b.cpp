#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    long long r = 0;
    string s1, s2, s3;
    while (cin >> s1 && cin >> s2 && cin >> s3) {
        // set<char> c1, c2, c3;
        // for (auto i : s1) {
        //     c1.insert(i);
        // }
        // for (auto i : s2) {
        //     c2.insert(i);
        // }
        // for (auto i : s3) {
        //     c3.insert(i);
        // }
        // c1.
        sort(s1.begin(), s1.end());
        sort(s2.begin(), s2.end());
        sort(s3.begin(), s3.end());

        vector<char> v, v2;
        set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(v));
        sort(v.begin(), v.end());
        set_intersection(v.begin(), v.end(), s3.begin(), s3.end(), back_inserter(v2));

        // if (v2.size() != 1) {
        //     cout << "wtf\n";
        //     cout << v2.size() << endl;
        //     cout << s1 << endl;
        //     cout << s2 << endl;
        //     cout << s3 << endl;
        //     cout << v2[0] << endl;
        //     cout << v2[1] << endl;
        // }

        char s = v2[0];
        if (s >= 'a') {
            r += s - 'a' + 1;
        } else {
            r += s - 'A' + 27;
        }

        cout << r << '\n';
    }
}
