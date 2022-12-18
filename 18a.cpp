#include <bits/stdc++.h>
using namespace std;

const int xmax = 30;
const int ymax = 30;
const int zmax = 30;
bool grid[xmax][ymax][zmax] = {};

bool get_grid(int i, int j, int k) {
    if (i < 0 || i >= xmax || j < 0 || j >= ymax || k < 0 || k >= zmax) {
        return false;
    }
    return grid[i][j][k];
}

int main() {
    // int x, y, z;
    // int xmax = 0;
    // int ymax = 0;
    // int zmax = 0;
    // while (scanf(" %d,%d,%d", &x, &y, &z) > 0) {
    //     xmax = max(xmax, x);  // 20
    //     ymax = max(ymax, y);  // 21
    //     zmax = max(zmax, z);  // 4
    // }
    // cout << "xmax: " << xmax << " ymax: " << ymax << " zmax: " << z;

    int x, y, z;
    while (scanf(" %d,%d,%d", &x, &y, &z) > 0) {
        grid[x][y][z] = 1;
    }
    int res = 0;
    for (int i = 0; i < xmax; i++) {
        for (int j = 0; j < ymax; j++) {
            for (int k = 0; k < zmax; k++) {
                if (!grid[i][j][k]) {
                    continue;
                }
                res += (!get_grid(i+1, j, k))
                    +  (!get_grid(i-1, j, k))
                    +  (!get_grid(i, j+1, k))
                    +  (!get_grid(i, j-1, k))
                    +  (!get_grid(i, j, k+1))
                    +  (!get_grid(i, j, k-1));
            }
        }
    }
    cout << res << endl;
}
