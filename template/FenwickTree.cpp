#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit, a;

    Fenwick(int n) : n(n), bit(n + 1, 0), a(n, 0) {}

    void add(int idx, int val) {
        a[idx] += val;

        for (++idx; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    }

    void set(int idx, int val) {
        add(idx, val - a[idx]);
    }

    int sum(int idx) {
        int res = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            res += bit[idx];
        return res;
    }
};

int main() {
    Fenwick fw(7);

    // Add values
    fw.add(0, 2);
    fw.add(1, 7);
    fw.add(2, 1);
    fw.add(3, 9);
    fw.add(4, 4);
    fw.add(5, 6);
    fw.add(6, 3);

    // Prefix sum [0..3]
    cout << fw.sum(3) << '\n';
    // 19

    // Set a[2] = 10
    fw.set(2, 10);

    // Prefix sum [0..3]
    cout << fw.sum(3) << '\n';
    // 28

    // Set a[0] = 5
    fw.set(0, 5);

    cout << fw.sum(3) << '\n';
    // 31
}
