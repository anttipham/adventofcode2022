#include <bits/stdc++.h>
using namespace std;

vector<string> q;
int si, sj, ei, ej, n, m;

set<pair<int, int>> visited;

struct Elem {
    int steps;
    int i, j;
};

int main() {
    string str;
    while (cin >> str) {
        q.push_back(str);
    }
    n = q.size();
    m = q[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (q[i][j] == 'S') {
                q[i][j] = 'a';
                si = i;
                sj = j;
            }
            if (q[i][j] == 'E') {
                q[i][j] = 'z';
                ei = i;
                ej = j;
            }
        }
    }

    // vector<string> a = q;

    queue<Elem> p;
    p.push({0, ei, ej});
    while (!p.empty()) {
        auto [depth, i, j] = p.front();
        p.pop();
        if (q[i][j] == 'a') {
            cout << depth << endl;
            break;
        }
        if (visited.count({i, j})) {
            continue;
        }
        visited.insert({i, j});
        // a[i][j] = '#';

        if (i+1 < n && q[i][j] - q[i+1][j] <= 1) {
            p.push({ depth+1, i+1, j });
        }
        if (0 <= i-1 && q[i][j] - q[i-1][j] <= 1) {
            p.push({ depth+1, i-1, j });
        }
        if (j+1 < m && q[i][j] - q[i][j+1] <= 1) {
            p.push({ depth+1, i, j+1 });
        }
        if (0 <= j-1 && q[i][j] - q[i][j-1] <= 1) {
            p.push({ depth+1, i, j-1 });
        }
    }
    // cout << p.size() << endl;
    // for (auto& aa : a) cout << aa << endl;
}
