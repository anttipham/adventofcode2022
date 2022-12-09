#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int hx = 0;
    int hy = 0;
    int tx = 0;
    int ty = 0;

    set<std::pair<int, int>> visited;
    visited.insert({0, 0});

    char dir;
    int rep;
    while (scanf("%s %d", &dir, &rep) > 0) {
        cout << dir << " " << rep << endl;
        while (rep--) {
            if (dir == 'U') {
                hy++;
            } else if (dir == 'R') {
                hx++;
            } else if (dir == 'D') {
                hy--;
            } else if (dir == 'L') {
                hx--;
            }

            if (abs(tx - hx) <= 1 && abs(ty - hy) <= 1) continue;

            int xmove = tx < hx ? 1 : -1;
            int ymove = ty < hy ? 1 : -1;
            if (tx != hx && ty != hy) {
                tx += xmove;
                ty += ymove;
            } else if (tx != hx) {
                tx += xmove;
            } else if (ty != hy) {
                ty += ymove;
            }
            visited.insert({ tx, ty });
            cout << "    " << tx << " " << ty << "\n";
        }
    }
    cout << visited.size() << endl;
}
