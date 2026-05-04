#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
using i128 = __int128_t;

static map<tuple<int, int, int>, vector<int>> roots_cache;
static map<int, vector<int>> rev_cache;

vector<int>& get_roots(int mod, int root, int n) {
    auto key = make_tuple(mod, root, n);
    if (roots_cache.count(key)) return roots_cache[key];
    auto& roots = roots_cache[key];
    roots.resize(n);
    int wlen = 1, pw = root;
    int exp = (mod - 1) / n;
    while (exp) {
        if (exp & 1) wlen = (i128)wlen * pw % mod;
        pw = (i128)pw * pw % mod;
        exp >>= 1;
    }
    roots[0] = 1;
    for (int i = 1; i < n; ++i)
        roots[i] = (i128)roots[i-1] * wlen % mod;
    return roots;
}

vector<int>& get_rev(int n) {
    if (rev_cache.count(n)) return rev_cache[n];
    auto& rev = rev_cache[n];
    rev.resize(n);
    for (int i = 1; i < n; ++i)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    return rev;
}

void ntt(vector<int>& a, bool invert, int mod, int root) {
    int n = a.size();
    const auto& rev = get_rev(n);
    for (int i = 0; i < n; ++i)
        if (i < rev[i]) swap(a[i], a[rev[i]]);

    const auto& roots = get_roots(mod, root, n);
    for (int len = 2; len <= n; len <<= 1) {
        int half = len >> 1;
        int step = n / len;
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < half; ++j) {
                int u = a[i + j];
                int v = (i128)a[i + j + half] * roots[j * step] % mod;
                a[i + j] = (u + v) % mod;
                a[i + j + half] = (u - v + mod) % mod;
            }
        }
    }

    if (invert) {
        int inv_n = 1, b = n, e = mod - 2;
        while (e) {
            if (e & 1) inv_n = (i128)inv_n * b % mod;
            b = (i128)b * b % mod;
            e >>= 1;
        }
        for (int& x : a) x = (i128)x * inv_n % mod;
        reverse(a.begin() + 1, a.end());
    }
}

vector<int> convolution_direct(const vector<int>& a, const vector<int>& b, int mod, int root) {
    int need = a.size() + b.size() - 1;
    int n = 1;
    while (n < need) n <<= 1;
    vector<int> fa(n, 0), fb(n, 0);
    copy(a.begin(), a.end(), fa.begin());
    copy(b.begin(), b.end(), fb.begin());

    ntt(fa, false, mod, root);
    ntt(fb, false, mod, root);
    for (int i = 0; i < n; ++i) fa[i] = (i128)fa[i] * fb[i] % mod;
    ntt(fa, true, mod, root);
    fa.resize(need);
    return fa;
}

vector<int> convolution_mod_1e9_7(const vector<int>& a, const vector<int>& b) {
    const int P1 = 998244353,  R1 = 3;
    const int P2 = 1004535809, R2 = 3;
    const int P3 = 469762049,  R3 = 3;
    const int TARGET = 1000000007;

    auto c1 = convolution_direct(a, b, P1, R1);
    auto c2 = convolution_direct(a, b, P2, R2);
    auto c3 = convolution_direct(a, b, P3, R3);

    static const int inv_m1_mod_m2 = [] {
        int res = 1, b = P1, exp = P2 - 2;
        while (exp) {
            if (exp & 1) res = (i128)res * b % P2;
            b = (i128)b * b % P2;
            exp >>= 1;
        }
        return res;
    }();
    static const int inv_m12_mod_m3 = [] {
        int m12 = (i128)P1 * P2 % P3;
        int res = 1, b = m12, exp = P3 - 2;
        while (exp) {
            if (exp & 1) res = (i128)res * b % P3;
            b = (i128)b * b % P3;
            exp >>= 1;
        }
        return res;
    }();

    int sz = c1.size();
    vector<int> result(sz);
    for (int i = 0; i < sz; ++i) {
        int x12 = c1[i] + P1 * ((c2[i] - c1[i] + P2) % P2 * inv_m1_mod_m2 % P2);
        int t = (c3[i] - (x12 % P3) + P3) % P3;
        t = (i128)t * inv_m12_mod_m3 % P3;
        i128 x = (i128)x12 + (i128)P1 * P2 * t;
        result[i] = (int)(x % TARGET);
    }
    return result;
}


void solve(){
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m), c; 
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < m; i++) cin >> b[i];
    c = convolution_mod_1e9_7(a,b);
    c.resize(n+m-1);
    for(int x:c) cout << x << ' ';
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t = 1;
	//cin >> t;
	while(t--) solve();
}