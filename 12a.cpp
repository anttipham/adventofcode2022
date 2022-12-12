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

    queue<Elem> p;
    p.push({0, si, sj});
    while (!p.empty()) {
        auto [depth, i, j] = p.front();
        p.pop();
        if (i == ei && j == ej) {
            cout << depth << endl;
            break;
        }
        if (visited.count({i, j})) {
            continue;
        }
        visited.insert({i, j});

        if (i+1 < n && abs(q[i+1][j] - q[i][j] <= 1))
            p.push({ depth+1, i+1, j });
        if (0 <= i-1 && abs(q[i-1][j] - q[i][j] <= 1))
            p.push({ depth+1, i-1, j });
        if (j+1 < m && abs(q[i][j+1] - q[i][j] <= 1))
            p.push({ depth+1, i, j+1 });
        if (0 <= j-1 && abs(q[i][j-1] - q[i][j] <= 1))
            p.push({ depth+1, i, j-1 });
    }
}
