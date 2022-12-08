#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<vector<int>> trees;
    string s;
    while (cin >> s) {
        trees.push_back({});
        for (char c : s) {
            trees.back().push_back(c - '0');
        }
    }
    const int Y = trees.size();
    const int X = trees.front().size();

    vector<vector<bool>> visible;
    visible.resize(Y);
    for (auto&& v : visible) {
        v.resize(X);
    }
    for (int j = 0; j < Y; j++) {
        int heightLeft = -1;
        int heightRight = -1;
        int heightUp = -1;
        int heightDown = -1;
        for (int i = 0; i < X; i++) {
            if (trees[j][i] > heightLeft) {
                heightLeft = trees[j][i];
                visible[j][i] = true;
            }
            if (trees[j][X-i-1] > heightRight) {
                heightRight = trees[j][X-i-1];
                visible[j][X-i-1] = true;
            }
            if (trees[i][j] > heightUp) {
                heightUp = trees[i][j];
                visible[i][j] = true;
            }
            if (trees[Y-i-1][j] > heightDown) {
                heightDown = trees[Y-i-1][j];
                visible[Y-i-1][j] = true;
            }
        }
    }

    int res = 0;
    for (auto&& a : visible) {
        for (auto&& b : a) {
            res += b;
        }
    }
    cout << res << endl;
    return 0;
}
