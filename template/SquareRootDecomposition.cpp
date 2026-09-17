#include <bits/stdc++.h>
using namespace std;

struct Sqrt {
    int n, B;
    vector<int> a, block;
    
    Sqrt(int n): n(n), B(sqrt(n) + 1), a(n), block((n + B - 1) / B) {}

    Sqrt(const vector<int>& a) : n(a.size()), a(a) {
        B = sqrt(n) + 1;
        block.resize((n + B - 1) / B);

        for (int i = 0; i < n; i++)
            block[i / B] += a[i];
    }

    void update(int idx, int val) {
        block[idx / B] += val - a[idx];
        a[idx] = val;
    }

    int query(int l, int r) {
        int ans = 0;

        while (l <= r && l % B != 0){
            ans += a[l];
            l++;
        }

        while (l + B - 1 <= r) {
            ans += block[l / B];
            l += B;
        }

        while (l <= r){
            ans += a[l];
            l++;
        }

        return ans;
    }
};

int main() {
    vector<int> a = {2, 7, 1, 9, 4, 6, 3};

    Sqrt sq(a);

    // Sum on [1, 4]
    cout << sq.query(1, 4) << '\n';
    // 21

    // Set a[2] = 10
    sq.update(2, 10);

    // a = {2, 7, 10, 9, 4, 6, 3}

    cout << sq.query(1, 4) << '\n';
    // 30

    // Sum of entire array
    cout << sq.query(0, 6) << '\n';
    // 41
}
