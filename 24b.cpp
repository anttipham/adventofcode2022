#include <bits/stdc++.h>
using namespace std;

using xy = pair<int, int>;

struct Blizzard {
    xy place;
    xy diff;

    bool operator<(Blizzard const& other) const {
        if (place != other.place) return place < other.place;
        return diff < other.diff;
    }
};
int height = 0;
int width = 0;
int cycle = INT_MAX;
vector<set<Blizzard>> blizzards;

set<Blizzard> getBliz(int time) {
    time %= cycle;
    while (time >= blizzards.size()) {
        set<Blizzard> newBliz;
        for (auto& [place, diff] : blizzards.back()) {
            auto [placex, placey] = place;
            auto [diffx, diffy] = diff;
            int newx = placex+diffx;
            int newy = placey+diffy;
            if (newx == 0) newx = width - 2;
            if (newy == 0) newy = height - 2;
            if (newx == width - 1) newx = 1;
            if (newy == height - 1) newy = 1;
            newBliz.insert({ { newx, newy }, diff });
        }
        blizzards.push_back(newBliz);
    }
    return blizzards[time];
}

int main() {
    set<Blizzard> bliz;
    string s;
    for (int j = 0;; j++) {
        if (!getline(std::cin, s)) break;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '>') bliz.insert({ { i, j }, {1, 0} });
            if (s[i] == 'v') bliz.insert({ { i, j }, {0, 1} });
            if (s[i] == '<') bliz.insert({ { i, j }, {-1, 0} });
            if (s[i] == '^') bliz.insert({ { i, j }, {0, -1} });
        }
        height++;
        width = s.size();
    }
    cycle = lcm(width - 2, height - 2);
    blizzards.push_back(bliz);

    set<pair<int, xy>> q;
    q.insert({ 0, { 1, 0 } });
    int res;
    int state = 0;
    int const goalx[3] = { width - 2, 1, width - 2 };
    int const goaly[3] = { height - 1, 0, height - 1 };
    while (q.size()) {
        auto [time, place] = *q.begin();
        auto [x, y] = place;
        q.erase(q.begin());
        if (x == goalx[state] && y == goaly[state]) {
            if (state == 2) {
                res = time;
                break;
            }
            q.clear();
            state++;
        }
        time++;
        auto nextbliz = getBliz(time);

        auto isPossible = [&](xy const& place_) {
            auto [x_, y_] = place_;
            if (x_ == goalx[state] && y_ == goaly[state]) return true;
            if (x_ <= 0 || x_ >= width - 1) return false;
            if (y_ <= 0 || y_ >= height - 1) return false;

            auto it = nextbliz.lower_bound({ place_, { -2, -2 } });
            if (it == nextbliz.end()) return true;
            return place_ != it->place;
        };
        if (isPossible({ x+1, y })) q.insert({ time, { x+1, y } });
        if (isPossible({ x, y+1 })) q.insert({ time, { x, y+1 } });
        if (isPossible({ x-1, y })) q.insert({ time, { x-1, y } });
        if (isPossible({ x, y-1 })) q.insert({ time, { x, y-1 } });
        if (isPossible({ x, y }))   q.insert({ time, { x, y } });
        cout << time << " " << x << " " << y << "\n";
    }
    std::cout << res;
}
