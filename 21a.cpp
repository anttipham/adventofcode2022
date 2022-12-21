#include <bits/stdc++.h>
using namespace std;

map<string, long long> nums;
map<string, tuple<string, char, string>> calc;

long long recursive(string m) {
    if (nums.count(m)) return nums[m];

    auto [m1, c, m2] = calc[m];
    long long num1 = recursive(m1);
    long long num2 = recursive(m2);
    if (c == '+') return num1 + num2;
    if (c == '-') return num1 - num2;
    if (c == '*') return num1 * num2;
    if (c == '/') return num1 / num2;
    cout << "ö" << endl;
    return INT_MIN;
}

int main() {
    string s;
    while (getline(cin, s)) {
        string m, m1, m2;
        char c;
        int num;
        stringstream ss(s);
        ss >> m;
        m.pop_back();
        if (s.size() == 17) {
            ss >> m1 >> c >> m2;
            calc[m] = { m1, c, m2 };
        } else {
            ss >> num;
            nums[m] = num;
        }
    }
    cout << recursive("root") << endl;
}
