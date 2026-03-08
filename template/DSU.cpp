#include <bits/stdc++.h>
using namespace std;

struct DSU {
    private:
        int _n;
        vector<int> parent_or_size;

    public:
        DSU(int n) : _n(n), parent_or_size(n, -1) {}

        int leader(int a) {
            if (parent_or_size[a] < 0) return a;
            return parent_or_size[a] = leader(parent_or_size[a]);
        }

        bool merge(int a, int b) {
            a = leader(a);
            b = leader(b);

            if (a == b) return false;

            if (-parent_or_size[a] < -parent_or_size[b])
                swap(a, b);

            parent_or_size[a] += parent_or_size[b];
            parent_or_size[b] = a;

            return true;
        }

        bool same(int a, int b) {
            return leader(a) == leader(b);
        }

        int size(int a) {
            return -parent_or_size[leader(a)];
        }

        vector<vector<int>> groups() {
            vector<int> leader_buf(_n), group_size(_n);
            for (int i = 0; i < _n; i++) {
                leader_buf[i] = leader(i);
                group_size[leader_buf[i]]++;
            }

            vector<vector<int>> result(_n);
            for (int i = 0; i < _n; i++) {
                result[i].reserve(group_size[i]);
            }

            for (int i = 0; i < _n; i++) {
                result[leader_buf[i]].push_back(i);
            }

            result.erase(
                remove_if(result.begin(), result.end(),
                        [](const vector<int>& v) { return v.empty(); }),
                result.end());

            return result;
        }
};

int main() {
    DSU dsu(5);

    dsu.merge(0,1);
    dsu.merge(1,2);

    cout << dsu.same(0,2) << endl;
    cout << dsu.same(0,3) << endl;

    cout << dsu.size(0) << endl;
}