#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 p = 998244353, g = 3, gi = 332748118;

inline i64 power(i64 a, i64 b) {
    i64 res = 1;
    for (a %= p; b; a = a * a % p, b >>= 1) {
        if (b & 1) res = res * a % p;
    }
    return res;
}

vector<i64> Conv(vector<i64> a, vector<i64> b, int lim) {
    int n = a.size(), m = b.size();
    int N = 1, t = 0;
    while(N < n + m) {
        N <<= 1, ++t;
    }

    a.resize(N), b.resize(N);
    vector<int> rev(N);
    for(int i = 0; i < N; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (t - 1));
    }
    
    auto ntt = [&](vector<i64>& f, int op) {
        for(int i = 0; i < N; ++i) {
            if(i < rev[i]) swap(f[i], f[rev[i]]);
        }

        for(int i = 1; i < N; i <<= 1) {
            i64 wn = power(op == 1 ? g : gi, (p - 1) / (i << 1));
            for(int j = 0; j < N; j += (i << 1)) {
                for(i64 k = 0, w = 1; k < i; ++k, w = w * wn % p) {
                    i64 fx = f[j + k], fy = w * f[i + j + k] % p;
                    f[j + k] = (fx + fy) % p;
                    f[i + j + k] = (fx - fy + p) % p;
                }
            }
        }
    };
    
    ntt(a, 1), ntt(b, 1);
    for(int i = 0; i < N; ++i) {
        a[i] *= b[i];
    }
    ntt(a, -1);
    
    const i64 inv = power(N, p - 2);
    vector<i64> ans(n + m - 1);
    for(int i = 0; i < n + m - 1; ++i) {
        ans[i] = a[i] * inv;
    }

    if ((int) ans.size() > lim) {
        ans.resize(lim);
    }
    return ans;
}

constexpr vector<i64> power(vector<i64> a, i64 b, int lim) {
    vector<i64> res(lim);
    res[0] = 1;
    for(; b; b >>= 1, a = Conv(a, a, lim)) {
        if(b & 1) res = Conv(res, a, lim);
    }
    return res;
}

void Thephix() {
    int n, m;
    cin >> n >> m;
    vector<i64> fac(m + 1), invfac(m + 1), inv(m + 1);
    fac[0] = 1;
    for (int i = 1; i <= m; ++i) {
        fac[i] = fac[i - 1] * i % p;
    }
    invfac[m] = power(fac[m], p - 2);
    for (int i = m; i >= 1; --i) {
        inv[i] = invfac[i] * fac[i - 1] % p;
        invfac[i - 1] = invfac[i] * i % p;
    }
    
    vector<i64> f(m + 1);
    f[0] = 1;
    for (int i = 1; i <= m; ++i) {
        f[i] = (f[i - 1] * (n + i - 1) % p) * inv[i] % p;
    }
    f = power(f, n - 1, m + 1);

    i64 ans = 0;
    for (int i = 0; i <= m; ++i) {
        ans = (ans + f[i]) % p;
    }
    cout << ans << "\n";
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}