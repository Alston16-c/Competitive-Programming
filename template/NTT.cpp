#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
const int MOD = 998244353;
const int G = 3;

int modpow(int a, int e) {
    int r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

void ntt(vector<int> &a, bool inv) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j |= bit;
        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        int wlen = modpow(G, (MOD - 1) / len);
        if (inv) wlen = modpow(wlen, MOD - 2);

        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i + j];
                int v = a[i + j + len/2] * w % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + len/2] = (u - v + MOD) % MOD;
                w = w * wlen % MOD;
            }
        }
    }

    if (inv) {
        int inv_n = modpow(n, MOD - 2);
        for (int &x : a) x = x * inv_n % MOD;
    }
}

vector<int> multiply(vector<int> a, vector<int> b) {
    int n = 1;
    while (n < (int)a.size() + (int)b.size()) n <<= 1;
    a.resize(n);
    b.resize(n);

    ntt(a, false);
    ntt(b, false);
    for (int i = 0; i < n; i++)
        a[i] = a[i] * b[i] % MOD;
    ntt(a, true);

    a.resize((int)a.size() + (int)b.size() - n - 1);
    return a;
}

void solve(){
    vector<int> a = {1, 2, 3};
    vector<int> b = {4, 5};
    
    auto c1 = multiply(a,b);

    for(int x:c1) cout << x << ' ';
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t = 1;
	//cin >> t;
	while(t--) solve();
}