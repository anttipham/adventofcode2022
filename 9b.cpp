#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<std::pair<int, int>> snake(10);
    auto& [hx, hy] = snake[0];

    set<std::pair<int, int>> visited;
    visited.insert({0, 0});

    char dir;
    int rep;
    while (scanf("%s %d", &dir, &rep) > 0) {
        // cout << dir << " " << rep << endl;
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

            for (int i = 1; i < snake.size(); i++) {
                auto& [px, py] = snake[i-1];
                auto& [tx, ty] = snake[i];
                if (abs(tx - px) <= 1 && abs(ty - py) <= 1) continue;

                int xmove = tx < px ? 1 : -1;
                int ymove = ty < py ? 1 : -1;
                if (tx != px && ty != py) {
                    tx += xmove;
                    ty += ymove;
                } else if (tx != px) {
                    tx += xmove;
                } else if (ty != py) {
                    ty += ymove;
                }
            }
            // cout << "    " << snake.back().first << " " << snake.back().second << "\n";
            visited.insert({ snake.back().first, snake.back().second });
        }
    }
    cout << visited.size() << endl;
}
