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
const int Y = 10000;

int main() {
    array<vector<bool>, X> r = {};
    for (auto& inner : r) {
        inner.resize(Y);
    }

    string jet;
    cin >> jet;
    int jetindex = 0;

    int highest = -1;
    for (int i = 0; i < 2022; i++) {
        Tetris cur = (Tetris) (i % N);
        int x = 2;
        int y = highest + 4;
        // simulate
        while (1) {
            // jet
            char c = jet[jetindex++ % jet.size()];
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
    // for (int j = highest; j >= 0; j--) {
    //     for (int i = 0; i < 7; i++) {
    //         cout << (r[i][j] ? '#' : '.');
    //     }
    //     cout << "\n";
    // }
    // cout << "\n";
    cout << highest+1 << endl;
}
