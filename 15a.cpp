#include <bits/stdc++.h>
using namespace std;

// const int Y = 10;
const int Y = 2000000;

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
    long long res = 0;
    while (scanf(" Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", &x, &y, &bx, &by) > 0) {
        sensors.push_back({ x, y, abs(bx-x) + abs(by-y), bx, by });
    }

    vector<pair<int, int>> beginend;
    for (auto& sensor : sensors) {
        int diffy = abs(sensor.y - Y);
        if (diffy > sensor.radius) continue;
        int diffx = sensor.radius - diffy;
        int leftx = sensor.x - diffx;
        int rightx = sensor.x + diffx;
        beginend.push_back({ leftx, rightx });
    }
    sort(beginend.begin(), beginend.end());

    int prevx = INT_MIN;
    for (auto [x1, x2] : beginend) {
        if (x2 <= prevx) continue;
        if (x1 <= prevx) {
            res -= prevx - x1 + 1;
        }
        res += x2 - x1 + 1;
        prevx = max(prevx, x2);
    }

    set<pair<int, int>> beacons;
    for (auto& sensor : sensors) {
        if (sensor.by != Y) continue;
        beacons.insert({ sensor.bx, sensor.by });
    }

    for (auto& [bx, by] : beacons) {
        for (auto [x1, x2] : beginend) {
            if (x1 <= bx && bx <= x2) {
                res--;
                break;
            }
        }
    }
    cout << res << "\n";
}
