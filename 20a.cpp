#include <bits/stdc++.h>
using namespace std;

list<int> nums;

void cycle(list<int>::iterator& it, int index) {
    index %= (int) nums.size();
    if (index < -nums.size()/2) index += nums.size();

    if (index < 0) {
        while (index++) {
            if (it == nums.begin()) it = nums.end();
            it--;
        }
    } else {
        while (index--) {
            it++;
            if (it == nums.end()) it = nums.begin();
        }
    }
}

int main() {
    int x;
    while (scanf(" %d", &x) > 0) {
        nums.push_back(x);
    }

    vector<list<int>::iterator> origOrder;
    list<int>::iterator zero;
    for (auto it = nums.begin(); it != nums.end(); it++) {
        if (*it == 0) zero = it;
        origOrder.push_back(it);
    }

    for (auto it : origOrder) {
        int val = *it;
        it = nums.erase(it);
        cycle(it, val);
        nums.insert(it, val);
    }

    cycle(zero, 1000);
    int res = *zero;
    cycle(zero, 1000);
    res += *zero;
    cycle(zero, 1000);
    res += *zero;

    cout << res << endl;
}
