#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<vector<char>> stacks = {};
    stacks.resize(9);
    string str;
    while (true) {
        getline(cin, str);
        if (str[1] == '1') {
            break;
        }

        for (int i = 0; i < stacks.size(); i++) {
            int charindex = 1 + i * 4;
            if (charindex < str.size() && str[charindex] != ' ') {
                stacks[i].push_back(str[charindex]);
            }
        }
    }

    getline(cin, str);

    int count, from, to;
    auto print = [&]() {
        for (auto stack : stacks[from]) cout << stack << " ";
        cout << endl;
        for (auto stack : stacks[to]) cout << stack << " ";
        cout << endl;
    };
    while (scanf("move %d from %d to %d\n", &count, &from, &to) > 0) {
        from -= 1;
        to -= 1;

        stacks[to].insert(stacks[to].begin(), stacks[from].rend() - count, stacks[from].rend());
        stacks[from].erase(stacks[from].begin(), stacks[from].begin() + count);
    }

    for (auto &stack : stacks) cout << stack.front();
}
