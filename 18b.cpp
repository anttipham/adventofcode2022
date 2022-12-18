#include <bits/stdc++.h>
using namespace std;

const int xmax = 30;
const int ymax = 30;
const int zmax = 30;
bool grid[xmax][ymax][zmax] = {};
int reachsteam[xmax][ymax][zmax] = {};

void set_reaches_steam(int i, int j, int k) {
    if (i < 0 || i >= xmax || j < 0 || j >= ymax || k < 0 || k >= zmax)
        return;
    if (reachsteam[i][j][k] >= 0)
        return;
    reachsteam[i][j][k] = 1;
    set_reaches_steam(i+1, j, k);
    set_reaches_steam(i-1, j, k);
    set_reaches_steam(i, j+1, k);
    set_reaches_steam(i, j-1, k);
    set_reaches_steam(i, j, k+1);
    set_reaches_steam(i, j, k-1);
}

bool reaches_steam(int i, int j, int k) {
    if (i < 0 || i >= xmax || j < 0 || j >= ymax || k < 0 || k >= zmax)
        return 1;
    if (grid[i][j][k])
        return 0;
    if (reachsteam[i][j][k] == -1)
        return 0;
    if (reachsteam[i][j][k] == 1)
        return 1;

    reachsteam[i][j][k] = -1;
    if (reaches_steam(i+1, j, k) ||
            reaches_steam(i-1, j, k) ||
            reaches_steam(i, j+1, k) ||
            reaches_steam(i, j-1, k) ||
            reaches_steam(i, j, k+1) ||
            reaches_steam(i, j, k-1)) {
        reachsteam[i][j][k] = 1;
        set_reaches_steam(i+1, j, k);
        set_reaches_steam(i-1, j, k);
        set_reaches_steam(i, j+1, k);
        set_reaches_steam(i, j-1, k);
        set_reaches_steam(i, j, k+1);
        set_reaches_steam(i, j, k-1);
        return 1;
    }
    return 0;
}

int main() {
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
                res += reaches_steam(i+1, j, k)
                    +  reaches_steam(i-1, j, k)
                    +  reaches_steam(i, j+1, k)
                    +  reaches_steam(i, j-1, k)
                    +  reaches_steam(i, j, k+1)
                    +  reaches_steam(i, j, k-1);
            }
        }
    }
    cout << res << endl;
}
