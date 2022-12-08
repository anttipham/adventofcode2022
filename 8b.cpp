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
    const int N = trees.size();

    vector<vector<int>> scenic;
    scenic.resize(N);
    for (auto&& v : scenic) {
        v.resize(N);
    }
    for (int j = 1; j < N-1; j++) {
        for (int i = 1; i < N-1; i++) {
            int heightLeft = -1;
            int heightRight = -1;
            int heightUp = -1;
            int heightDown = -1;
            int scenicLeft = 0;
            int scenicRight = 0;
            int scenicUp = 0;
            int scenicDown = 0;
            for (int k = 1; k < N; k++) {
                if (!(0 <= i-k && i-k < N)) break;
                scenicLeft++;
                if (trees[j][i-k] >= trees[j][i]) break;
                heightLeft = trees[j][i-k];
            }
            for (int k = 1; k < N; k++) {
                if (!(0 <= i+k && i+k < N)) break;
                scenicRight++;
                if (trees[j][i+k] >= trees[j][i]) break;
                heightRight = trees[j][i+k];
            }
            for (int k = 1; k < N; k++) {
                if (!(0 <= j-k && j-k < N)) break;
                scenicUp++;
                if (trees[j-k][i] >= trees[j][i]) break;
                heightUp = trees[j-k][i];
            }
            for (int k = 1; k < N; k++) {
                if (!(0 <= j+k && j+k < N)) break;
                scenicDown++;
                if (trees[j+k][i] >= trees[j][i]) break;
                heightDown = trees[j+k][i];
            }
            scenic[j][i] = scenicLeft * scenicRight * scenicUp * scenicDown;
        }
    }

    int res = 0;
    for (auto&& a : scenic) {
        for (auto&& b : a) {
            res = max(res, b);
        }
    }
    cout << res << endl;
    return 0;
}
