#include <bits/stdc++.h>
using namespace std;

list<long long> nums;

void cycle(list<long long>::iterator& it, long long index) {
    index %= (long long) nums.size();
    if (index < 0) index += nums.size();
    if (index > nums.size()/2) index -= nums.size();

    if (index < 0) {
        if (it == nums.begin()) it = nums.end();
        while (index++) {
            it--;
            if (it == nums.begin()) it = nums.end();
        }
    } else {
        while (index--) {
            if (it == nums.end()) it = nums.begin();
            it++;
        }
    }
}

int main() {
    int x;
    while (scanf(" %d", &x) > 0) {
        nums.push_back(x*811589153LL);
    }

    vector<list<long long>::iterator> origOrder;
    list<long long>::iterator zero;
    for (auto it = nums.begin(); it != nums.end(); it++) {
        if (*it == 0) zero = it;
        origOrder.push_back(it);
    }

    for (int i = 0; i < 10; i++) {
        for (auto& it : origOrder) {
            long long val = *it;
            it = nums.erase(it);
            cycle(it, val);
            it = nums.insert(it, val);
        }
    }

    cycle(zero, 1000);
    long long res = *zero;
    cycle(zero, 1000);
    res += *zero;
    cycle(zero, 1000);
    res += *zero;

    cout << res << endl;
}
