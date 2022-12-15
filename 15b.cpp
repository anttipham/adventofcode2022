#include <bits/stdc++.h>
using namespace std;

// const int Y = 20;
const int Y = 4000000;

struct Sensor {
    int x;
    int y;
    int radius;
    int bx;
    int by;
};

int main() {
    vector<Sensor> sensors;
    int x, y, bx, by;
    while (scanf(" Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", &x, &y, &bx, &by) > 0) {
        sensors.push_back({ x, y, abs(bx-x) + abs(by-y), bx, by });
    }

    for (int y = 0; y < Y; y++) {
        vector<pair<int, int>> beginend;
        for (auto& sensor : sensors) {
            int diffy = abs(sensor.y - y);
            if (diffy > sensor.radius) continue;
            int diffx = sensor.radius - diffy;
            int leftx = sensor.x - diffx;
            int rightx = sensor.x + diffx;
            beginend.push_back({ leftx, rightx });
        }
        sort(beginend.begin(), beginend.end());

        int prevx1 = beginend[0].first;
        int prevx2 = beginend[0].second;
        for (int i = 1; i < beginend.size(); i++) {
            auto [x1, x2] = beginend[i-1];
            if (prevx2+1 < x1) {
                cout << "found " << y << " " << prevx2 << " " << x1 << "\n";
                cout << (long long) (x1-1) * 4000000 + y << "\n";
            }
            if (x2 > prevx2) {
                prevx2 = x2;
            }
        }
    }
}
