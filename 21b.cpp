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
    for (auto i = 10000000000000LL; i > 0; i /= 2) {
        nums["humn"] += i;
        while (recursive(get<0>(calc["root"])) > recursive(get<2>(calc["root"]))) {
            nums["humn"] += i;
        }
        nums["humn"] -= i;
    }
    cout << ++nums["humn"] << endl;
    cout << recursive(get<0>(calc["root"])) << " " << recursive(get<2>(calc["root"])) << "\n";
}