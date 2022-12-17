#include <bits/stdc++.h>
using namespace std;

const int N = 5;

enum Tetris {
    viiva,
    risti,
    jii,
    ii,
    nelio
};

const int X = 7;
const int Y = 30000000;
const int MAGIC1 = 100910;
const int MAGIC2 = 17154700;
const int MAGIC_DIFF = MAGIC2 - MAGIC1;
const int MAGIC_VALUE = 26868916 - 158039;

int main() {
    array<vector<bool>, X> r = {};
    for (auto& inner : r) {
        inner.resize(Y);
    }

    string jet;
    cin >> jet;
    int jetindex = 0;

    // Differences repeat on MAGIC1, MAGIC1+MAGIC_DIFF, MAGIC1+2*MAGIC_DIFF, ...
    const long long cycles = (1000000000000LL - MAGIC1) / MAGIC_DIFF;
    const long long left = 1000000000000 % MAGIC_DIFF;
    long long result = cycles * MAGIC_VALUE;

    // vector<int> highs;
    int highest = -1;
    for (int i = 0; i < left+1; i++) {
        Tetris cur = (Tetris) (i % N);
        // if (i % (N*jet.size()) == 0) {
        //     cout << "i: " << i << " highest: " << highest << endl;
        //     highs.push_back(highest);
        // }
        int x = 2;
        int y = highest + 4;
        // simulate
        while (1) {
            // jet
            char c = jet[jetindex];
            jetindex = (jetindex + 1) % jet.size();
            if (c == '<') {
                bool possible = false;
                try {
                    switch (cur) {
                    case viiva:
                        if (!r.at(x-1).at(y)) possible = true;
                        break;
                    case risti:
                        if (!r.at(x).at(y) && !r.at(x-1).at(y+1) && !r.at(x).at(y+2)) possible = true;
                        break;
                    case jii:
                        if (!r.at(x-1).at(y) && !r.at(x+1).at(y+1) && !r.at(x+1).at(y+2)) possible = true;
                        break;
                    case ii:
                        if (!r.at(x-1).at(y) && !r.at(x-1).at(y+1) && !r.at(x-1).at(y+2) && !r.at(x-1).at(y+3)) possible = true;
                        break;
                    case nelio:
                        if (!r.at(x-1).at(y) && !r.at(x-1).at(y+1)) possible = true;
                        break;
                    }
                } catch(const std::out_of_range& e) {}
                if (possible) x--;
            } else {
                bool possible = false;
                try {
                    switch (cur) {
                    case viiva:
                        if (!r.at(x+4).at(y)) possible = true;
                        break;
                    case risti:
                        if (!r.at(x+2).at(y) && !r.at(x+3).at(y+1) && !r.at(x+2).at(y+2)) possible = true;
                        break;
                    case jii:
                        if (!r.at(x+3).at(y) && !r.at(x+3).at(y+1) && !r.at(x+3).at(y+2)) possible = true;
                        break;
                    case ii:
                        if (!r.at(x+1).at(y) && !r.at(x+1).at(y+1) && !r.at(x+1).at(y+2) && !r.at(x+1).at(y+3)) possible = true;
                        break;
                    case nelio:
                        if (!r.at(x+2).at(y) && !r.at(x+2).at(y+1)) possible = true;
                        break;
                    }
                } catch(const std::out_of_range& e) {}
                if (possible) x++;
            }

            // fall
            bool landed = false;
            try {
                switch (cur) {
                case viiva:
                    if (r.at(x+0).at(y-1) ||
                        r.at(x+1).at(y-1) ||
                        r.at(x+2).at(y-1) ||
                        r.at(x+3).at(y-1)) landed = true;
                    break;
                case risti:
                    if (r.at(x+0).at(y) ||
                        r.at(x+1).at(y-1) ||
                        r.at(x+2).at(y)) landed = true;
                    break;
                case jii:
                    if (r.at(x+0).at(y-1) ||
                        r.at(x+1).at(y-1) ||
                        r.at(x+2).at(y-1)) landed = true;
                    break;
                case ii:
                    if (r.at(x).at(y-1)) landed = true;
                    break;
                case nelio:
                    if (r.at(x+0).at(y-1) ||
                        r.at(x+1).at(y-1)) landed = true;
                    break;
                }
            } catch(const std::out_of_range& e) {
                landed = true;
            }

            if (!landed) {
                y--;
            } else {
                switch (cur) {
                case viiva:
                    r.at(x+0).at(y) = true;
                    r.at(x+1).at(y) = true;
                    r.at(x+2).at(y) = true;
                    r.at(x+3).at(y) = true;
                    highest = max(highest, y);
                    break;
                case risti:
                    r.at(x+0).at(y+1) = true;
                    r.at(x+1).at(y) = true;
                    r.at(x+1).at(y+1) = true;
                    r.at(x+1).at(y+2) = true;
                    r.at(x+2).at(y+1) = true;
                    highest = max(highest, y+2);
                    break;
                case jii:
                    r.at(x+0).at(y) = true;
                    r.at(x+1).at(y) = true;
                    r.at(x+2).at(y) = true;
                    r.at(x+2).at(y+1) = true;
                    r.at(x+2).at(y+2) = true;
                    highest = max(highest, y+2);
                    break;
                case ii:
                    r.at(x).at(y) = true;
                    r.at(x).at(y+1) = true;
                    r.at(x).at(y+2) = true;
                    r.at(x).at(y+3) = true;
                    highest = max(highest, y+3);
                    break;
                case nelio:
                    r.at(x+0).at(y) = true;
                    r.at(x+0).at(y+1) = true;
                    r.at(x+1).at(y) = true;
                    r.at(x+1).at(y+1) = true;
                    highest = max(highest, y+1);
                    break;
                }
                break;
            }
        }
    }
    // // Calculate diffs
    // for (int i = 1; i < highs.size(); i++) {
    //     cout << highs[i] - highs[i-1] << ", ";
    // }
    cout << result + highest << endl;
}
